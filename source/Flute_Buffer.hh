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

#ifdef __MWERKS__
# define FL_DLL
#endif

#include <string>

#include <FL/Fl.H>
#include <FL/Fl_Text_Editor.H>

#include <Flute_DEFINES.hh>

#ifndef Flute_Buffer_HH
#define Flute_Buffer_HH

class Flute_Buffer : public Fl_Text_Buffer {
public:
	Flute_Buffer(int id,const char* path);
	Flute_Buffer(int requestedSize=0,int preferredGapSize=1024,int id=-1,const char* path="");

	int getID();
	const char* getPath();
	void setID(int id);
	void setPath(const char* path);

	bool m_modify_callback_set;
protected:
	int m_id;
	std::string m_path;

private:
	void init(int id,const char* path);
};

#endif // Flute_Buffer_HH
