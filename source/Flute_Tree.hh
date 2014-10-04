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

#ifdef __MWERKS__
# define FL_DLL
#endif

#include <FL/Fl.H>
#include <FL/Fl_Tree.H>

#include <Flute_DEFINES.hh>

#ifndef Flute_Tree_HH
#define Flute_Tree_HH

class Flute_Tree : public Fl_Tree {
public:
	Flute_Tree(int x,int y,int w,int h);

	int handle(int e);
};

#endif // Flute_Tree_HH
