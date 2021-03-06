// FLUTE: Fast Light Ultimate Text Editor
// Copyright 2013 - 2015  David Ulrich
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <stdio.h>
#include <string.h>

#include <Flute_Config.hh>
#include <Flute_DEFINES.hh>


Flute_Config :: Flute_Config() : Flute_Config("config/config.lua") {
	// nothing
}

Flute_Config :: Flute_Config(const char* path) {
	// nothing
	lua_State* L;
	L = luaL_newstate();
	luaL_openlibs(L);

	luaL_dofile(L,path);
	printf("===== %s loaded =====\n",path);

	lua_getglobal(L, "settings");
	lua_pushnil(L);

	while(lua_next(L, -2)) {
		if(lua_isnumber(L,-1) && lua_isstring(L,-2)) {
			int val = (int)lua_tonumber(L,-1);
			const char* name = lua_tostring(L,-2);

			Flute_Config_Opt* opt = new Flute_Config_Opt(name,val);

			m_settings.push_back(opt);
		}
		lua_pop(L, 1);
	}
	lua_pop(L, 1);

	lua_close(L);
}

int Flute_Config :: getOpt(const char *opt) {
	int id = getOptID(opt);

	if (id == -1) return 0;

	return m_settings[id]->m_val;
}


int Flute_Config :: getOptID(const char *opt) {
	int i,id,len;

	id = -1;
	len = m_settings.size();

	for(i=0;i<len;i++) {
		if (!m_settings[i]->m_name.compare(opt)) id = i;
	}

	return id;
}


void Flute_Config :: printAll() {
	int len = m_settings.capacity();
	int cnt = m_settings.size();
	Flute_Config_Opt* opt;

	printf("===== TOTAL SETTINGS [%d/%d] =====\n",cnt,len);

	for(int i=0;i<cnt;i++) {
		opt = m_settings[i];
		if (opt) {
			printf("[%d] NAME: %s, VALUE: %d\n",i,opt->m_name.c_str(),opt->m_val);
		}
		else {
			printf("[%d] EMPTY\n",i);
		}
	}

	printf("=====  END  =====\n");
}
