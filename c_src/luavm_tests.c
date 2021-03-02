#include <stdlib.h>
#include <stdint.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#define TEXT_STRING "TEST STRING"

/*
* NOTICE: https://www.lua.org/pil/26.1.html
 */

static int l_return_string(lua_State *L) {
    const char *string = lua_tostring(L, 1);  /* get argument */
    lua_pushstring(L, string);  /* push result */
    return 1;  /* number of results */
}

static int test_c_fn() {
    int ret;
    size_t len = 0;
    FILE *output;
    lua_State *lua;

    lua = luaL_newstate();
    luaL_openlibs(lua);

    lua_pushcfunction(lua, l_return_string);
    lua_setglobal(lua, "return_string");

    ret = luaL_dostring(lua, "return return_string(\""TEXT_STRING"\")");
    const char *value = lua_tolstring(lua, lua_gettop(lua), &len);
    if (ret == 0) {
        output = stdout;
        ret = EXIT_SUCCESS;
    } else {
        output = stderr;
        ret = EXIT_FAILURE;
    }
    fprintf(output, "Test name  : c_fn\n");
    fprintf(output, "Lua version: %llu\n", (uint64_t) lua_version(lua));
    fprintf(output, "Lua result : %s\n", value);
    lua_close(lua);
    return ret == EXIT_SUCCESS;
}

static int test_simple_script() {
    int ret;
    size_t len = 0;
    FILE *output;
    lua_State *lua;

    lua = luaL_newstate();
    luaL_openlibs(lua);
    ret = luaL_dostring(lua, "return \""TEXT_STRING"\"");
    const char *value = lua_tolstring(lua, lua_gettop(lua), &len);
    if (ret == 0) {
        output = stdout;
        ret = EXIT_SUCCESS;
    } else {
        output = stderr;
        ret = EXIT_FAILURE;
    }
    fprintf(output, "Test name  : simple_script\n");
    fprintf(output, "Lua version: %llu\n", (uint64_t) lua_version(lua));
    fprintf(output, "Lua result : %s\n", value);
    lua_close(lua);
    return ret == EXIT_SUCCESS;
}

int main() {
    return (test_simple_script() &&
            test_c_fn()) ? EXIT_SUCCESS : EXIT_FAILURE;
}
