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

#include <string.h>

#include <Flute_Buffer_Manager.hh>


Flute_Buffer_Manager :: Flute_Buffer_Manager(int len) : m_vec(len) {
// 	printf("length:%d\n",this->b_vec.size());
// 	printf("history length: %d\n",m_history.size());
}


void Flute_Buffer_Manager :: closeBuffer(int buffID) {
	m_vec[buffID] = NULL;

	m_history.remove(buffID);
}


Flute_Buffer* Flute_Buffer_Manager :: getLastBuffer() {
	return getLastBuffer(0);
}


// get the buffer `back` elements from the end, or the nearest to that position
// depending on the length of the buffer history
Flute_Buffer* Flute_Buffer_Manager :: getLastBuffer(int from_back) {
	if (m_history.empty()) return m_vec[0];

	// oh no, reverse iterator alert
	int i = 0;
	std::list<int>::reverse_iterator rit=m_history.rbegin();
	while(i < from_back && rit != m_history.rend()) {
		i++;
		rit++;
	}
	return m_vec[*rit];
}


Flute_Buffer* Flute_Buffer_Manager :: getBuffer(int buffID) {
	_setLastBuffer(buffID);

	return m_vec[buffID];
}

Flute_Buffer* Flute_Buffer_Manager :: getBuffer(const char* path) {
	int buffID = getBufferID(path);

	_setLastBuffer(buffID);

	return m_vec[buffID];
}


int Flute_Buffer_Manager :: getBufferID(const char* path) {
	int i,id,len;

	id = -1;
	len = m_vec.capacity();

	for(i=0;i<len;i++) {
		if (m_vec[i]) printf("%s == %s\n",path,m_vec[i]->getPath());
		if (m_vec[i]
			&& !strcmp(m_vec[i]->getPath(),path)) id = i;
	}

	return id;
}


int Flute_Buffer_Manager :: getBufferID(Flute_Buffer* buff) {
	int i,id,len;

	id = -1;
	len = m_vec.capacity();

	for(i=0;i<len;i++) {
		if (m_vec[i] == buff) id = i;
	}

	return id;
}


void Flute_Buffer_Manager :: printAll() {
	int len = m_vec.capacity();
	Flute_Buffer* buff;

	printf("===== TOTAL [%d] =====\n",len);

	for(int i=0;i<len;i++) {
		buff = m_vec[i];
		if (buff) {
			printf("[%d] BUFFER %s (%d)\n",i,buff->getPath(),buff->getID());
		}
		else {
			printf("[%d] EMPTY\n",i);
		}
	}

	printf("=====  END  =====\n");
}


int Flute_Buffer_Manager :: setBuffer(const char* path) {
	int buffID;

	buffID = getBufferID(path);

	if (buffID == -1) {
		buffID = _getFreeID();

		m_vec[buffID] = new Flute_Buffer(buffID,path);
// 		m_vec[buffID]->loadfile(path);
	}

	return buffID;
}


int Flute_Buffer_Manager :: setBuffer(Flute_Buffer* buff) {
	int buffID;

	buffID = _getFreeID();

	m_vec[buffID] = buff;
	m_vec[buffID]->setID(buffID);

	return buffID;
}


int Flute_Buffer_Manager :: _getFreeID() {
	int i,id,len;

	id = -1;
	len = m_vec.capacity();

	for(i=0;i<len;i++) {
		if (!m_vec[i]) {
			id = i;
			break;
		}
	}

	if (id == -1) {
		id = len;

		m_vec.resize(len*2);
	}

	return id;
}


void Flute_Buffer_Manager :: _setLastBuffer(int buffID) {
	m_history.remove(buffID);
	m_history.push_back(buffID);
}
