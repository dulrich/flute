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


Flute_Controller :: Flute_Controller(Flute_Config *config) {
	this->xt_config = config;
}


int Flute_Controller :: init() {
	if (!this->xt_config) {
		return 1;
	}
	else {
		this->initWindow();
		this->initEditor();
		this->initTree();
	}
	
	return 0;
}


void Flute_Controller :: initEditor() {
	int offsetX = this->xt_config->getOpt("tree_w");
	int offsetY = 0;
	int sizeX = this->fc_window->w() - offsetX;
	int sizeY = this->fc_window->h();
	
	this->fc_editor = new Fl_Text_Editor(offsetX,offsetY,sizeX,sizeY);
	this->fc_window->resizable(*(this->fc_editor));
}


void Flute_Controller :: initTree() {
	int offsetX = 0;
	int offsetY = 0;
	int sizeX = this->xt_config->getOpt("tree_w");
	int sizeY = this->fc_window->h();
	
	this->fc_tree_open = new Fl_Tree(offsetX,offsetY,sizeX,sizeY);
	this->fc_tree_open->showroot(0);
	
	this->fc_tree_open->add("/code/file.cc");
	this->fc_tree_open->add("/code/file.hh");
	this->fc_tree_open->add("/code/flute/file_x.cc");
}


void Flute_Controller :: initWindow() {
	int sizeX = this->xt_config->getOpt("win_w");
	int sizeY = this->xt_config->getOpt("win_h");
	
	this->fc_window = new Fl_Double_Window(sizeX,sizeY,"FLUTE");
}


/* method copied from fltk/examples/tree */
void Flute_Controller :: onTreeEvent(Fl_Widget *w,void *data) {
	Fl_Tree *tree = (Fl_Tree*)w;
	Fl_Tree_Item *item = (Fl_Tree_Item*)tree->callback_item();
	if ( ! item ) return;
	switch ( tree->callback_reason() ) {
		case FL_TREE_REASON_SELECTED: {
			char pathname[256];
			tree->item_pathname(pathname, sizeof(pathname), item);
			fprintf(stderr, "TreeCallback: Item selected='%s', Full pathname='%s'\n", item->label(), pathname);
			break;
		}
		case FL_TREE_REASON_DESELECTED:
			// fprintf(stderr, "TreeCallback: Item '%s' deselected\n", item->label());
			break;
		case FL_TREE_REASON_OPENED:
			// fprintf(stderr, "TreeCallback: Item '%s' opened\n", item->label());
			break;
		case FL_TREE_REASON_CLOSED:
			// fprintf(stderr, "TreeCallback: Item '%s' closed\n", item->label());
		default:
			break;
	}
}


void Flute_Controller :: pathClose(char *path) {
	if (this->xt_config->getOpt("gui_tree")) {
		Fl_Tree_Item *item = this->fc_tree_open->find_item(path);
		if (item) {
			this->fc_tree_open->remove(item);
		}
		else {
			// probably should send a notice that path was not open
		}
	}
	
	if (this->xt_config->getOpt("gui_tabs")) {
		// STUB
	}
}


void Flute_Controller :: pathOpen(char *path) {
	
}


void Flute_Controller :: setBuffer(int editPane, Fl_Text_Buffer *buff) {
	this->fc_editor->buffer(buff);
}


void Flute_Controller :: setTreeCallback(Fl_Callback *fn) {
	this->fc_tree_open->callback(fn);
}


void Flute_Controller :: show() {
	this->fc_window->show();
}