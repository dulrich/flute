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
#include <Flute_Buffer.hh>

#ifndef Flute_Editor_HH
#define Flute_Editor_HH

class Flute_Editor : public Fl_Text_Editor {
public:

	void add_flute_keybindings();
	void init();
	void clear_line(int leading_space, int newline);
	static int kf_enter(int c,Fl_Text_Editor* e);
	static int kf_home(int c,Fl_Text_Editor* e);
	static int kf_shift_home(int c,Fl_Text_Editor* e);
	static int kf_tab(int c,Fl_Text_Editor* e);
	static int kf_shift_tab(int c,Fl_Text_Editor* e);

	Flute_Buffer* getBuffer();

	Flute_Editor(int x,int y,int w,int h);
	Flute_Editor(int x,int y,int w,int h,const char* title);
};

#endif // Flute_Editor_HH
