// COPYRIGHT AND LICENSE SEE FILE: LICENSE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#ifdef __MWERKS__
# define FL_DLL
#endif

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Tree.H>

#include <Flute_Config.hh>
#include <Flute_Controller.hh>
#include <Flute_DEFINES.hh>


Flute_Config     *config;
Flute_Controller *cont;
Fl_Text_Buffer   *textBuff = new Fl_Text_Buffer();

void contTreeCallback(Fl_Widget *w, void *data);

int main(int argc, char *argv[]) {
	config = new Flute_Config();
	
	cont = new Flute_Controller(config);
	
	textBuff->text("Hello World!");
	
	cont->init();
	cont->setBuffer(1,textBuff);
	cont->setTreeCallback(contTreeCallback);
	cont->show();
	
	return(Fl::run());
}

void contTreeCallback(Fl_Widget *w, void *data) {
	cont->onTreeEvent(w,data);
}

