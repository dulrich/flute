#include <FL/Fl_Native_File_Chooser.H>
#include <FL/names.h>

#include <Flute_Window.hh>


Flute_Window :: Flute_Window(int w, int h, const char* title,Flute_Config* config)
							 : Fl_Double_Window(w,h,title) {
	m_config = config;
	m_bufman = new Flute_Buffer_Manager(m_config->getOpt("default_buffer_count"));
}


void Flute_Window :: addTreePath(int which, const char* path) {
	Fl_Tree_Item* newItem = m_tree->add(path);
	m_tree->set_item_focus(newItem);
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
		
// 		printf("Event %s\n",fl_eventnames[event]);
		
		if (event == FL_SHORTCUT) {
			printf("Key: '%c' \n",Fl::event_key());
			switch(Fl::event_key()) {
				case 'o':
					getFile(1);
					break;
					
				case 's':
					saveBuffer(1);
					break;
					
				case 'w':
					closeBuffer(1);
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
	int offsetX = m_config->getOpt("tree_w");
	int offsetY = 0;
	int sizeX = w() - offsetX;
	int sizeY = h();
	
	m_editor = new Flute_Editor(offsetX,offsetY,sizeX,sizeY);
	add_resizable(*(m_editor));
}


void Flute_Window :: initTabs(int which) {
	
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
}


void Flute_Window :: saveBuffer(int which) {
	const char* path = m_editor->getBuffer()->getPath();
	m_editor->buffer()->savefile(path);
}


void Flute_Window :: setBuffer(int which, const char* path) {
	int buffID = m_bufman->getBufferID(path);
// 	printf("SETTING BUFFER TO %s (%d)\n",path,buffID);
//	m_bufman->printAll();
	if (buffID == -1) {
		buffID = m_bufman->setBuffer(path);
	}
	Flute_Buffer* buff = m_bufman->getBuffer(buffID);
	m_editor->buffer(buff);
	
	m_tree->add(path);
}


void Flute_Window :: setBuffer(int which, Flute_Buffer* buff) {
	int buffID = m_bufman->getBufferID(buff);
	
	if (buffID == -1) {
		buffID = m_bufman->setBuffer(buff);
	}
	
	m_editor->buffer(buff);
	
	m_tree->add(buff->getPath());
}

