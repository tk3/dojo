#include <stdio.h>
#include <stdlib.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

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

    lua_close(L);

    return 0;
}

