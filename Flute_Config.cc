#include <stdio.h>
#include <string.h>

#include <Flute_Config.hh>
#include <Flute_DEFINES.hh>


Flute_Config :: Flute_Config() {
	// nothing
}

Flute_Config :: Flute_Config(const char* path) {
	// nothing
	lua_State* L;
	L = luaL_newstate();
	luaL_openlibs(L);
	
	luaL_dofile(L,path);
	
	lua_close(L);
}

int Flute_Config :: getOpt(const char *opt) {
	if (!strcmp(opt,"tree_w")) return 200;
	else if (!strcmp(opt,"win_h")) return 600;
	else if (!strcmp(opt,"win_w")) return 800;
	else if (!strcmp(opt,"file_tree")) return 1;
	else if (!strcmp(opt,"line_nums")) return 1;
	else if (!strcmp(opt,"default_buffer_count")) return 16;
	else return 0;
}