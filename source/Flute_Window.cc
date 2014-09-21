#include <FL/Fl_Native_File_Chooser.H>
#include <FL/names.h>

#include <Flute_Window.hh>


Flute_Window :: Flute_Window(int w, int h, const char* title,Flute_Config* config)
							 : Fl_Double_Window(w,h,title) {
	m_config = config;
	m_bufman = new Flute_Buffer_Manager(m_config->getOpt("default_buffer_count"));
}


void Flute_Window :: addTreePath(int which, const char* path) {
	Fl_Tree_Item* item = m_tree->find_item(path);
	
	if (!item) {
		printf("ADDING TREE PATH %s\n",path);
		item = m_tree->add(path);
	}
	
	m_tree->select_only(item,0);
	m_tree->set_item_focus(item);
	
	m_tree->redraw();
};


void Flute_Window :: removeTreePath(int which, const char* path) {
	Fl_Tree_Item* item = m_tree->find_item(path);
	Fl_Tree_Item* parent;
	
	while (!item->is_root() && !item->has_children()) {
		parent = item->parent();
		m_tree->remove(item);
		item = parent;
	}
	
	m_tree->redraw();
};


void Flute_Window :: getFile(int which) {
	 Fl_Native_File_Chooser fnfc;
	 fnfc.title("Pick a file");
	 fnfc.type(Fl_Native_File_Chooser::BROWSE_FILE);
	 fnfc.filter("Text\t*.txt\n"
		         "C Files\t*.{c,cc,cpp,cxx,h,hh,hpp}");
	 fnfc.filter_value(2);
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
			setBuffer(which,fnfc.filename());
			break;
	 }
}


int Flute_Window :: handle(int event) {
	if (Fl_Group::handle(event)) return 1;
	else {
		
//  		printf("Event %s\n",fl_eventnames[event]);
		
		if (event == FL_SHORTCUT) {
// 			printf("Key: '%c' \n",Fl::event_key());
			switch(Fl::event_key()) {
				case 'b':
					setPrevBuffer(1);
					break;
				
				case 'k':
					clearLine(1,1);
					break;
				
				case 'l':
					clearLine(0,0);
					break;
				
				case 'o':
					getFile(1);
					break;
				
				case 'q':
					hide();
					break;
				
				case 's':
					saveBuffer(1);
					break;
					
				case 'w':
					closeBuffer(1);
					break;
			}
		}
		else if (event == FL_KEYBOARD) {
// 			printf("Key: '%c' \n",Fl::event_key());
			switch(Fl::event_key()) {
				case FL_Escape:
					return 1;
					break;
			}
		}
		return 0;
	}
}


int Flute_Window :: init() {
	if (!m_config) {
		return 1;
	}
	else {
		initEditor(1);
		initTree(1);
	}
	
	return 0;
}


void Flute_Window :: initEditor(int which) {
	int usingFileTree = m_config->getOpt("file_tree");
	int treeWidth = usingFileTree
		? m_config->getOpt("tree_w")
		: 0;
	
	int usingLineNums = m_config->getOpt("line_nums");
	int sizeXLn = 30;
	int sizeYLn = h();
	int lineNumWidth = usingLineNums
		? sizeXLn
		: 0;
	
	int offsetXLn = treeWidth;
	int offsetYLn = 0;
	
	int offsetXEd = treeWidth + lineNumWidth;
	int offsetYEd = 0;
	
	int sizeXEd = w() - offsetXEd;
	int sizeYEd = h();
	
	if (usingLineNums) {
		m_linenum = new Fl_Text_Display(offsetXLn,offsetYLn,sizeXLn,sizeYLn);
		m_linenum->textfont(FL_COURIER);
		m_linebuf = new Fl_Text_Buffer(1024);
		m_linebuf->text(" 1\n10\n ~");
		m_linenum->buffer(m_linebuf);
	}
	m_editor  = new Flute_Editor(offsetXEd,offsetYEd,sizeXEd,sizeYEd);
	add_resizable(*(m_editor));
}


void Flute_Window :: initTree(int which) {
	int offsetX = 0;
	int offsetY = 0;
	int sizeX = m_config->getOpt("tree_w");
	int sizeY = h();
	
	m_tree = new Flute_Tree(offsetX,offsetY,sizeX,sizeY);
	m_tree->root_label("");
// 	m_tree->showroot(0);
}


void Flute_Window :: closeBuffer(int which) {
	const char* path = m_editor->getBuffer()->getPath();
	
	int buffID = m_bufman->getBufferID(path);
	
	if (buffID != -1) m_bufman->closeBuffer(buffID);
	
	if (m_config->getOpt("file_tree")) {
		removeTreePath(which,path);
	}
	
	const char *newPath = m_bufman->getLastBuffer()->getPath();
	
	setBuffer(which,newPath);
}


void Flute_Window :: clearLine(int leading_space, int newline) {
	m_editor->clear_line(leading_space,newline);
}


Flute_Buffer* Flute_Window :: getBuffer(int which) {
	return m_editor->getBuffer();
}


void on_buffer_modified(int pos, int nInserted, int nDeleted, int nRestyled, const char* deletedText, void* cbArg) {
	Flute_Window* w = (Flute_Window*)cbArg;
	const char* path = w->m_editor->getBuffer()->getPath();

	w->m_tree->find_item(path)->labelfont(FL_COURIER | FL_ITALIC);
	w->m_tree->redraw();
}


void Flute_Window :: saveBuffer(int which) {
	const char* path = m_editor->getBuffer()->getPath();
	m_editor->buffer()->savefile(path);

	m_tree->find_item(path)->labelfont(FL_COURIER);
	m_tree->redraw();
}


void Flute_Window :: setBuffer(int which, const char* path) {
	if (path == NULL) return;

	int buffID = m_bufman->getBufferID(path);
// 	printf("SETTING BUFFER TO %s (%d)\n",path,buffID);
//	m_bufman->printAll();
	if (buffID == -1) {
		buffID = m_bufman->setBuffer(path);
	}
	Flute_Buffer* buff = m_bufman->getBuffer(buffID);

	if (!buff->m_modify_callback_set) {
		buff->add_modify_callback(&on_buffer_modified,this);
		buff->m_modify_callback_set = true;
	}
	m_editor->buffer(buff);

	addTreePath(-1,path);
//	m_tree->add(path);
}


void Flute_Window :: setBuffer(int which, Flute_Buffer* buff) {
	int buffID = m_bufman->getBufferID(buff);

	if (buffID == -1) {
		buffID = m_bufman->setBuffer(buff);
	}

	if (!buff->m_modify_callback_set) {
		buff->add_modify_callback(&on_buffer_modified,this);
		buff->m_modify_callback_set = true;
	}
	m_editor->buffer(buff);

	addTreePath(-1,buff->getPath());
}


void Flute_Window :: setPrevBuffer(int which) {
	const char *newPath = m_bufman->getLastBuffer(1)->getPath();

	setBuffer(which,newPath);
}