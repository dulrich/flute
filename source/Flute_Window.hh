#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Text_Display.H>

#include <Flute_Buffer_Manager.hh>
#include <Flute_Config.hh>
#include <Flute_Editor.hh>
#include <Flute_Tree.hh>
#include <Flute_DEFINES.hh>

#ifndef Flute_Window_HH
#define Flute_Window_HH

class Flute_Window : public Fl_Double_Window {
public:
	Flute_Buffer_Manager* m_bufman;
	Flute_Config*         m_config;

	Flute_Editor*         m_editor;
	Flute_Tree*           m_tree;
	Fl_Text_Display*      m_linenum;
	Fl_Text_Buffer*       m_linebuf;

	int handle(int event);
	int init();
	void getFile(int which);
	void initEditor(int which);
	void initTree(int which);

	void addTreePath(int which,const char* path);
	void removeTreePath(int which,const char* path);

	void closeBuffer(int which);
	void clearLine(int leading_space, int newline);
	Flute_Buffer* getBuffer(int which);
	static void on_buffer_modified(int pos, int nInserted, int nDeleted, int nRestyled, const char* deletedText, void* cbArg);
	void saveBuffer(int which);
	void setBuffer(int which,const char* path);
	void setBuffer(int which,Flute_Buffer* buff);
	void setPrevBuffer(int which);

	Flute_Window(int w,int h,const char* title,Flute_Config* config);
};

#endif // Flute_Window_HH
