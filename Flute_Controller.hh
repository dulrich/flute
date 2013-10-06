#ifdef __MWERKS__
# define FL_DLL
#endif

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Tree.H>

#include <Flute_Config.hh>
#include <Flute_DEFINES.hh>

#ifndef Flute_Controller_HH
#define Flute_Controller_HH

class Flute_Controller {
	
	Flute_Config     *xt_config;
	
	Fl_Double_Window *fc_window;
	Fl_Text_Editor   *fc_editor;
	Fl_Tree          *fc_tree_open;
	
	void initEditor();
	void initTree();
	void initWindow();
	
	
	
	public:
		~Flute_Controller ();
		Flute_Controller (Flute_Config *config);
		
		int  init();
		
		void onTreeEvent(Fl_Widget *w, void *data);
		void pathClose(char *path);
		void pathOpen(char *path);
		void setBuffer(int editPane,Fl_Text_Buffer *buff);
		void setTreeCallback(Fl_Callback *fn);
		void show();
};



#endif // Flute_Controller_HH