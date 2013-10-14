#ifdef __MWERKS__
# define FL_DLL
#endif

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Tree.H>

#include <Flute_Config.hh>
#include <Flute_Editor.hh>
#include <Flute_DEFINES.hh>

#ifndef Flute_Window_HH
#define Flute_Window_HH

class Flute_Window : public Fl_Double_Window {
public:
	Flute_Config* xt_config;
	
	Flute_Editor* w_editor;
	Fl_Tree*        w_tree;
	
	int handle(int event);
	int init();
	void getFile();
	void initEditor(int which);
	void initTabs(int which);
	void initTree(int which);
	
	void setBuffer(int which,const char* path);
	void setBuffer(int which,Fl_Text_Buffer* buffer);
	
	Flute_Window(int w,int h,const char* title,Flute_Config* config);
};

#endif // Flute_Window_HH
