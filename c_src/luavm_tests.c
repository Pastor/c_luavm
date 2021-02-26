#include <stdlib.h>
#include <stdint.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

int main() {
    int ret;
    size_t len = 0;
    FILE *output;
    lua_State *lua;

    lua = luaL_newstate();
    luaL_openlibs(lua);
    ret = luaL_dostring(lua, "return \"Simple return script\"");
    const char *value = lua_tolstring(lua, lua_gettop(lua), &len);
    if (ret == 0) {
        output = stdout;
        ret = EXIT_SUCCESS;
    } else {
        output = stderr;
        ret = EXIT_FAILURE;
    }
    fprintf(output, "Lua version: %llu\n", (uint64_t)lua_version(lua));
    fprintf(output, "Lua result : %s", value);
    lua_close(lua);
    return ret;
}
