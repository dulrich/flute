#include <Flute_Editor.hh>


Flute_Editor :: Flute_Editor(int x, int y, int w, int h)
							 : Fl_Text_Editor(x,y,w,h) {
	init();
}


Flute_Editor :: Flute_Editor(int x, int y, int w, int h, const char* title)
							 : Fl_Text_Editor(x,y,w,h,title) {
	init();
}


void Flute_Editor :: add_flute_keybindings() {
	add_key_binding(FL_Enter,0,Flute_Editor::kf_enter);

	add_key_binding(FL_Home,0,Flute_Editor::kf_home);
	add_key_binding(FL_Home,FL_SHIFT,Flute_Editor::kf_shift_home);

	add_key_binding(FL_Tab,0,Flute_Editor::kf_tab);
	add_key_binding(FL_Tab,FL_SHIFT,Flute_Editor::kf_shift_tab);
}


void Flute_Editor :: init() {
	add_flute_keybindings();

	textfont(FL_COURIER);
}


void Flute_Editor :: clear_line(int leading_space, int newline) {
	Fl_Text_Buffer* b = this->buffer();
	int pos_start,pos_end,pos_insert;
	b->selection_position(&pos_start,&pos_end);
	pos_insert = insert_position();

	if (pos_start <= 0 || pos_end <= 0) {
		pos_start = pos_insert;
		pos_end   = pos_insert;
	}

	int startLine = b->line_start(pos_start);
	int endLine   = b->line_end(pos_end);
	int length    = b->length();

	if (newline && endLine == length) startLine--;
	else if (newline) endLine++;

	int character = b->char_at(startLine);

	if (!leading_space) {
		while(character == '\t' || character == ' ') {
			pos_insert = startLine;
			startLine = b->next_char(pos_insert);
			character = b->char_at(startLine);
		}
	}

	b->remove(startLine,endLine);
}


int Flute_Editor :: kf_enter(int c,Fl_Text_Editor* e) {
	Fl_Text_Buffer* b = e->buffer();
	bool selection = false;
	int pos_insert,pos_start,pos_end;

	const char* newline = "\n";
	char* line_text;
	int line_len,i;

	if (b->selected()) {
		selection = true;
		b->selection_position(&pos_start,&pos_end);
		pos_insert = pos_start < pos_end ? pos_start : pos_end;
	}
	else {
		pos_insert = e->insert_position();
	}

	pos_start = b->line_start(pos_insert);
	pos_end   = b->line_end(pos_insert);

	line_text = b->line_text(pos_insert);
	line_len = strlen(line_text);

	for(i=0;i<line_len;i++) {
		if (line_text[i] != '\t' && line_text[i] != ' ') {
			i--;
			break;
		}
	}

	line_text[i+1] = '\0';

	b->insert(pos_insert,newline);
	pos_insert += strlen(newline);

	if (selection) {
		b->replace_selection(line_text);
	}
	else {
		b->insert(pos_insert,line_text);
	}
	free(line_text);

	e->insert_position(pos_insert+i+1);

	e->show_insert_position();
	e->set_changed();
	if (e->when()&FL_WHEN_CHANGED) e->do_callback();
	return 1;
}


int Flute_Editor :: kf_home(int c,Fl_Text_Editor* e) {
	Fl_Text_Buffer* b = e->buffer();
	int pos_start,pos_end,pos_insert,pos_space,pos_swap;

	b->selection_position(&pos_start,&pos_end);
	pos_insert = e->insert_position();

	if (b->selected()) {
		b->unselect();
		pos_insert = pos_start < pos_end ? pos_start : pos_end;
	}

	int startLine = b->line_start(pos_insert);
	int character = b->char_at(startLine);
	pos_space = startLine;

	while(character == '\t' || character == ' ') {
		pos_swap = pos_space;
		pos_space = b->next_char(pos_swap);
		character = b->char_at(pos_space);
	}

	int pos_new = (pos_insert == pos_space)
		? startLine
		: pos_space;

	e->insert_position(pos_new);

	e->show_insert_position();
	e->set_changed();
	if (e->when()&FL_WHEN_CHANGED) e->do_callback();
	return 1;
}


int Flute_Editor :: kf_shift_home(int c,Fl_Text_Editor* e) {
	Fl_Text_Buffer* b = e->buffer();
	int pos_start,pos_end,pos_insert,pos_insend,pos_space,pos_swap;

	b->selection_position(&pos_start,&pos_end);
	pos_insert = e->insert_position();
	pos_insend = pos_insert;

	if (b->selected()) {
		pos_insert = pos_start < pos_end ? pos_start : pos_end;
		pos_insend = pos_start > pos_end ? pos_start : pos_end;
	}

	int startLine = b->line_start(pos_insert);
	int character = b->char_at(startLine);
	pos_space = startLine;

	while(character == '\t' || character == ' ') {
		pos_swap = pos_space;
		pos_space = b->next_char(pos_swap);
		character = b->char_at(pos_space);
	}

	int pos_new = (pos_insert == pos_space)
		? startLine
		: pos_space;

	if (pos_new == pos_insend) {
		b->unselect();
	}
	else {
		b->select(pos_new,pos_insend);
	}
	e->insert_position(pos_new);

	e->show_insert_position();
	e->set_changed();
	if (e->when()&FL_WHEN_CHANGED) e->do_callback();
	return 1;
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

Flute_Buffer* Flute_Editor :: getBuffer() {
	return (Flute_Buffer*)buffer();
}
