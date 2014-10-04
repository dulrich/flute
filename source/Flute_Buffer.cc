// FLUTE: Fast Light Ultimate Text Editor
// Copyright 2013 - 2014 David Ulrich
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

#include <Flute_Buffer.hh>

Flute_Buffer :: Flute_Buffer(int id,const char* path) : Fl_Text_Buffer() {
	init(id,path);
}

Flute_Buffer :: Flute_Buffer(int requestedSize,int preferredGapSize,int id,const char* path)
							 : Fl_Text_Buffer(requestedSize,preferredGapSize) {
	init(id,path);
}

void Flute_Buffer :: init(int id,const char* path) {
	this->loadfile(path);
	this->setID(id);
	this->setPath(path);
	this->tab_distance(4);
	this->m_modify_callback_set = false;
}


int Flute_Buffer :: getID() {
	return m_id;
}


const char* Flute_Buffer :: getPath() {
	return m_path.c_str();
};


void Flute_Buffer :: setID(int id) {
	m_id = id;
}


void Flute_Buffer :: setPath(const char* path) {
	m_path.assign(path);
};



