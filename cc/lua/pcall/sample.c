#include <stdio.h>
#include <stdlib.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

int call_lua_function(lua_State *L);

int main(int argc, char **argv)
{
    lua_State *L;

    if (argc < 2) {
        fprintf(stderr, "usage: %s filename\n", argv[0]);
        return -1;
    }

    L = luaL_newstate();

    luaL_openlibs(L);

    if (luaL_dofile(L, argv[1])) {
        fprintf(stderr, "Error: %s\n", lua_tostring(L, -1));
        lua_close(L);
        return -1;
    }

    call_lua_function(L);

    lua_close(L);

    return 0;
}

int call_lua_function(lua_State *L)
{
    lua_Integer retvalue;

    lua_getglobal(L, "foo");

    lua_pushnumber(L, 11);     // argv #1
    lua_pushstring(L, "bar");  // argv #2

    // arg = 2, return = 1
    if (lua_pcall(L, 2, 1, 0) != 0) {
        fprintf(stderr, "Error: failed to call function. [%s]\n", lua_tostring(L, -1));
        return -1;
    }

    if (!lua_isnumber(L, -1)) {
        fprintf(stderr, "Error: Wrong return value. [%s]\n", lua_tostring(L, -1));
        lua_pop(L, 1);
        return -1;
    }

    retvalue = lua_tointeger(L, 1);
    lua_pop(L, 1);

    printf("result = [%ld]\n", retvalue);

    return 0;
}

