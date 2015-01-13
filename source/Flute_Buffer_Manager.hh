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

#include <list>
#include <vector>

#include <Flute_DEFINES.hh>
#include <Flute_Buffer.hh>

#ifndef Flute_Buffer_Manager_HH
#define Flute_Buffer_Manager_HH

class Flute_Buffer_Manager {
public:
	Flute_Buffer_Manager(int len=16);

	void printAll();

	void closeBuffer(int buffID);

	Flute_Buffer* getLastBuffer(); // get the most recently used buffer
	Flute_Buffer* getLastBuffer(int from_back); // get the most recently used buffer

	Flute_Buffer* getBuffer(int buffID);
	Flute_Buffer* getBuffer(const char* path);

	int getBufferID(const char* path);
	int getBufferID(Flute_Buffer* buff);

	int setBuffer(const char* path);
	int setBuffer(Flute_Buffer* buff);

protected:
	std::vector<Flute_Buffer*> m_vec;
	std::list<int> m_history;

	int _getFreeID();
	void _setLastBuffer(int buffID);
};

#endif // Flute_Buffer_Manager_HH
