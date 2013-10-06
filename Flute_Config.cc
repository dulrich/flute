#include <stdio.h>
#include <string.h>

#include <Flute_Config.hh>
#include <Flute_DEFINES.hh>

Flute_Config :: Flute_Config() {
	// nothing
}

int Flute_Config :: getOpt(char *opt) {
	if (!strcmp(opt,"tree_w")) return 200;
	else if (!strcmp(opt,"win_h")) return 600;
	else if (!strcmp(opt,"win_w")) return 800;
	else return 0;
}