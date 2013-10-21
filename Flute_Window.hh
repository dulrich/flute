#include <FL/Fl_Double_Window.H>

#include <Flute_Buffer_Manager.hh>
#include <Flute_Config.hh>
#include <Flute_Editor.hh>
#include <Flute_Tree.hh>
#include <Flute_DEFINES.hh>

#ifndef Flute_Window_HH
#define Flute_Window_HH

class Flute_Window : public Fl_Double_Window {
public:
	Flute_Buffer_Manager* bufman;
	Flute_Config*         xt_config;
	
	Flute_Editor*         w_editor;
	Flute_Tree*           w_tree;
	
	int handle(int event);
	int init();
	void getFile(int which);
	void initEditor(int which);
	void initTabs(int which);
	void initTree(int which);
	
	void addTreePath(int which,const char* path);
	void removeTreePath(int which,const char* path);
	
	void closeBuffer(int which);
	void saveBuffer(int which);
	void setBuffer(int which,const char* path);
	void setBuffer(int which,Flute_Buffer* buff);
	
	Flute_Window(int w,int h,const char* title,Flute_Config* config);
};

#endif // Flute_Window_HH
