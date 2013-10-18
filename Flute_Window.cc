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
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Tree.H>
#include <FL/names.h>

#include <Flute_Config.hh>
#include <Flute_Editor.hh>
#include <Flute_Window.hh>
#include <Flute_DEFINES.hh>


Flute_Window :: Flute_Window(int w, int h, const char* title,
							 Flute_Config* config) : Fl_Double_Window(w,h,title) {
	this->xt_config = config;
}


void Flute_Window :: addTreePath(int which, const char* path) {
	Fl_Tree_Item* newItem = this->w_tree->add(path);
	this->w_tree->set_item_focus(newItem);
};


void Flute_Window :: removeTreePath(int which, const char* path) {
	Fl_Tree_Item* pathItem = this->w_tree->find_item(path);
	this->w_tree->remove(pathItem);
	this->w_tree->redraw();
};


void Flute_Window :: getFile(int which) {
	 Fl_Native_File_Chooser fnfc;
	 fnfc.title("Pick a file");
	 fnfc.type(Fl_Native_File_Chooser::BROWSE_FILE);
	 fnfc.filter("Text\t*.txt\n"
		         "C Files\t*.{c,cc,cpp,cxx,h,hh,hpp}");
	 fnfc.directory("/code/flute");
	 // Show native chooser
	 switch ( fnfc.show() ) {
		case -1: // ERROR
			printf("ERROR: %s\n", fnfc.errmsg());
			break;
		case  1:  // CANCEL
			printf("CANCEL\n");
			break;
		default: // FILE CHOSEN
			printf("PICKED: %s\n", fnfc.filename());
			this->setBuffer(which,fnfc.filename());
			this->addTreePath(1,fnfc.filename());
			break;
	 }
}


int Flute_Window :: handle(int event) {
	if (Fl_Group::handle(event)) return 1;
	else {
		
		printf("Event %s\n",fl_eventnames[event]);
		
		if (event == FL_SHORTCUT) {
			printf("Key: '%c' \n",Fl::event_key());
			switch(Fl::event_key()) {
				case 'o':
					this->getFile(1);
					break;
					
				case 's':
					this->saveBuffer(1);
					break;
					
				case 'w':
					this->closeBuffer(1);
					break;
			}
		}
		return 0;
	}
}


int Flute_Window :: init() {
	if (!this->xt_config) {
		return 1;
	}
	else {
		this->initEditor(1);
		this->initTree(1);
	}
	
	return 0;
}


void Flute_Window :: initEditor(int which) {
	int offsetX = this->xt_config->getOpt("tree_w");
	int offsetY = 0;
	int sizeX = this->w() - offsetX;
	int sizeY = this->h();
	
	this->w_editor = new Flute_Editor(offsetX,offsetY,sizeX,sizeY);
	this->add_resizable(*(this->w_editor));
}


void Flute_Window :: initTabs(int which) {
	
}


void Flute_Window :: initTree(int which) {
	int offsetX = 0;
	int offsetY = 0;
	int sizeX = this->xt_config->getOpt("tree_w");
	int sizeY = this->h();
	
	this->w_tree = new Fl_Tree(offsetX,offsetY,sizeX,sizeY);
	this->w_tree->showroot(0);
	
	this->w_tree->add("Untitled");
}


void Flute_Window :: closeBuffer(int which) {
	const char* path = this->w_editor->getPath();
	
	this->removeTreePath(which,path);
}


void Flute_Window :: saveBuffer(int which) {
	const char* path = this->w_editor->getPath();
	this->w_editor->buffer()->savefile(path);
}


void Flute_Window :: setBuffer(int which, const char* path) {
	this->w_editor->setPath(path);
	this->w_editor->buffer()->loadfile(path);
	this->w_tree->add(path);
}


void Flute_Window :: setBuffer(int which, Fl_Text_Buffer* buffer) {
	this->w_editor->buffer(buffer);
}
	
