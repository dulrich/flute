//
// "$Id: texteditor-simple.cxx 8864 2011-07-19 04:49:30Z greg.ercolano $"
//
//	A simple example of Fl_Text_Editor
//
//	Fl_Text_Editor is unlike other FLTK widgets in that
//	to work correctly, it must be assigned to an instance of an
//	Fl_Text_Buffer.  The below shows using buffer() to connect
//	the two classes together.
//
//	Note that the example can also be used to demonstrate
//	Fl_Text_Display; just replace all instances of
//	Fl_Text_Editor with Fl_Text_Display and rebuild.
//
// Copyright 2010 Greg Ercolano.
// Copyright 1998-2010 by Bill Spitzak and others.
//
// This library is free software. Distribution and use rights are outlined in
// the file "COPYING" which should have been included with this file.  If this
// file is missing or damaged, see the license at:
//
//     http://www.fltk.org/COPYING.php
//
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//

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


void InitEdit(Fl_Text_Editor **edit);
void InitTree(Fl_Tree **tree);
void InitWindow();
void TreeCallback(Fl_Widget *w, void *data);


Fl_Double_Window *win;

int main(int argc, char *argv[]) {
	InitWindow();
	
	Fl_Text_Buffer		*textBuff = new Fl_Text_Buffer();
	Fl_Text_Editor		*editPane;
	Fl_Tree				*treePane;
	
	InitTree(&treePane);
	InitEdit(&editPane);
	
	editPane->buffer(textBuff);		// attach the text buffer to our editor widget
	win->resizable(*editPane);
	win->show();
	textBuff->text("line 0\nline 1\nline 2\n"
					"line 3\nline 4\nline 5\n"
					"line 6\nline 7\nline 8\n"
					"line 9\nline 10\nline 11\n"
					"line 12\nline 13\nline 14\n"
					"line 15\nline 16\nline 17\n"
					"line 18\nline 19\nline 20\n"
					"line 21\nline 22\nline 23\n");
	return(Fl::run());
}


void InitEdit(Fl_Text_Editor **edit) {
	*edit = new Fl_Text_Editor(200+20,10,win->w()-200-30,win->h()-20);
}


void InitTree(Fl_Tree **tree) {
	// Create the tree
	*tree = new Fl_Tree(10, 10, 200, win->h()-20);
	(*tree)->showroot(0);				// don't show root of tree
	(*tree)->callback(TreeCallback);		// setup a callback for the tree
	
	// Add some items
	(*tree)->add("Flintstones/Fred");
	(*tree)->add("Flintstones/Wilma");
	(*tree)->add("Flintstones/Pebbles");
	(*tree)->add("Simpsons/Homer");
	(*tree)->add("Simpsons/Marge");
	(*tree)->add("Simpsons/Bart");
	(*tree)->add("Simpsons/Lisa");
	(*tree)->add("Pathnames/\\/bin");		// front slashes
	(*tree)->add("Pathnames/\\/usr\\/sbin");
	(*tree)->add("Pathnames/C:\\\\Program Files");	// backslashes
	(*tree)->add("Pathnames/C:\\\\Documents and Settings");
	
	// Start with some items closed
	(*tree)->close("Simpsons");
	(*tree)->close("Pathnames");
}


void InitWindow() {
	win  = new Fl_Double_Window(640, 480, "FLUTE");
}


void TreeCallback(Fl_Widget *w, void *data) {
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
