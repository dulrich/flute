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
#include <FL/Fl_Button.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Tree.H>

#include <Flute_Config.hh>
#include <Flute_Window.hh>
#include <Flute_DEFINES.hh>


Flute_Config*     config;
Flute_Window*     window;
Fl_Text_Buffer*   buffer;
// Fl_Button*        button;

int main(int argc, char* argv[]) {
	config = new Flute_Config();
	
	buffer = new Fl_Text_Buffer();
	buffer->tab_distance(4);
	buffer->text("one\ntwo\nthree");
	
	window = new Flute_Window(config->getOpt("win_w"),config->getOpt("win_h"),"FLUTE",config);
	
// 	button = new Fl_Button(0,0,100,50,"Hello?");
// 	window->add(button);
	
	window->init();
	
	window->setBuffer(1,buffer);
	Fl::visual(FL_DOUBLE|FL_INDEX);
	window->show();
	
	return (Fl::run());
}

