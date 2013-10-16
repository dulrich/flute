#ifdef __MWERKS__
# define FL_DLL
#endif

#include <FL/Fl.H>
#include <FL/Fl_Text_Editor.H>

#include <Flute_DEFINES.hh>
#include <Flute_Editor.hh>


Flute_Editor :: Flute_Editor(int x, int y, int w, int h)
							 : Fl_Text_Editor(x,y,w,h) {
	this->add_flute_keybindings();
}


Flute_Editor :: Flute_Editor(int x, int y, int w, int h, const char* title)
							 : Fl_Text_Editor(x,y,w,h,title) {
	this->add_flute_keybindings();
}


void Flute_Editor :: add_flute_keybindings() {
	this->add_key_binding(FL_Tab,0,Flute_Editor::kf_tab);
	this->add_key_binding(FL_Tab,FL_SHIFT,Flute_Editor::kf_shift_tab);
}


int Flute_Editor :: kf_tab(int c,Fl_Text_Editor* e) {
	const char* tab = "\t\0";
	Fl_Text_Buffer* b = e->buffer();
	int numLines,oldPos,startPos,endPos;
	
	if (b->selected()) {
		b->selection_position(&startPos,&endPos);
		
		numLines = b->count_lines(startPos,endPos);
		oldPos = e->insert_position();
		
		e->insert_position(b->line_start(startPos));
		e->insert(tab);
		
		for(int i=0;i<numLines;i++) {
			e->insert_position(b->skip_lines(e->insert_position(),1));
			e->insert(tab);
		}
		
		e->insert_position(oldPos+1+((oldPos == endPos) ? numLines : 0));
	}
	else {
		if (e->insert_mode()) e->insert(tab);
		else e->overstrike(tab);
	}
	
	e->show_insert_position();
	e->set_changed();
	if (e->when()&FL_WHEN_CHANGED) e->do_callback();
	return 1;
}


int Flute_Editor :: kf_shift_tab(int c,Fl_Text_Editor* e) {
	Fl_Text_Buffer* b = e->buffer();
	int numLines,startPos,endPos,oldPos,hadSelection;
	
	oldPos = e->insert_position();
	
	if (b->selected()) {
		hadSelection = 1;
		b->selection_position(&startPos,&endPos);
		
		e->insert_position(b->line_start(startPos));
		numLines = b->count_lines(startPos,endPos);
	}
	else {
		hadSelection = 0;
		e->insert_position(b->line_start(e->insert_position()));
		numLines = 0;
	}
	
	
	int i,p1,p2,startRemoved,totalRemoved;
	startRemoved = 0;
	totalRemoved = 0;
	for(i=0;i<=numLines;i++) {
		if (i != 0) {
			e->insert_position(b->skip_lines(e->insert_position(),1));
		}
		p1 = e->insert_position();
		
		if (b->char_at(p1) == '\t') {
			p2 = b->next_char(p1);
			b->select(p1,p2);
			b->remove_selection();
			if (i==0) startRemoved = 1;
			totalRemoved++;
		}
	}
	
	// restore the editor state
	if (hadSelection) {
		int newPos = (oldPos == endPos)
			? oldPos-totalRemoved
			: oldPos-startRemoved;
		
		b->select(startPos-startRemoved,endPos-totalRemoved);
		e->insert_position(newPos);
	}
	else {
		e->insert_position(oldPos-startRemoved);
	}
	
	e->show_insert_position();
	e->set_changed();
	if (e->when()&FL_WHEN_CHANGED) e->do_callback();
	return 1;
}


	const char* Flute_Editor :: getPath() {
		return "/code/flute/test.txt";
	};
	void Flute_Editor :: setPath(const char* path) {
		
	};
	
	
	


