#ifndef Flute_DEFINES_HH
#define Flute_DEFINES_HH

// the currently activated editor pane
const int FLUTE_ACTIVE_PANE = -1;

enum Flute_Buffer_State {	
	FLUTE_BUFFER_ACTIVE = 1,
	FLUTE_BUFFER_EDITED = 2
};

extern "C" {
#include <lua5.2/lua.h>
#include <lua5.2/lualib.h>
#include <lua5.2/lauxlib.h>
}

#endif // Flute_DEFINES_HH