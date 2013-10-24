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
	static int kf_tab(int c,Fl_Text_Editor* e);
	static int kf_shift_tab(int c,Fl_Text_Editor* e);
	
	Flute_Buffer* getBuffer();
	
	Flute_Editor(int x,int y,int w,int h);
	Flute_Editor(int x,int y,int w,int h,const char* title);
};

#endif // Flute_Editor_HH
