#include <stdio.h>
#include <stdlib.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

int lua_formatter(lua_State* L);

int main(int argc, char **argv)
{
    lua_State *L;

    if (argc < 2) {
        fprintf(stderr, "usage: %s filename\n", argv[0]);
        return -1;
    }

    L = luaL_newstate();

    luaL_openlibs(L);
    lua_register(L, "formatter", lua_formatter);

    if (luaL_dofile(L, argv[1])) {
        fprintf(stderr, "Error: %s\n", lua_tostring(L, -1));
        lua_close(L);
        return -1;
    }

    lua_close(L);

    return 0;
}

int lua_formatter(lua_State* L)
{
    int   argc;
    const char *result = NULL;

    argc = lua_gettop(L);

    lua_getglobal(L, "string");
    lua_pushliteral(L, "format");
    lua_gettable(L, -2);
    lua_insert(L, 1);
    lua_pop(L, 1);

    if (lua_pcall(L, argc, 1, 0) != 0) {
        fprintf(stderr, "Error: failed to call function. [%s]\n", lua_tostring(L, -1));
        lua_pushstring(L, "");
        return 1;
    }

    result = lua_tostring(L, 1);
    lua_pop(L, 1);

    lua_pushstring(L, result);
    return 1;
}

