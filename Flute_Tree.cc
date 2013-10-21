#include <FL/names.h>

#include <Flute_Tree.hh>
#include <Flute_Window.hh>


Flute_Tree :: Flute_Tree(int x,int y,int w,int h) : Fl_Tree(x,y,w,h) {
	
}

int Flute_Tree :: handle(int event)  {
// 	printf("HIT TREE CALLBACK (%d)\n",event);
	printf("Event %s\n",fl_eventnames[event]);
	
	int used = Fl_Tree::handle(event);
	
	Fl_Tree_Item* item = this->first_selected_item();
// 	if (item) printf("CHILDREN: %d\n",item->has_children());
	if (item && !item->has_children()) {
	
		char path[1024];
		Flute_Window* win = (Flute_Window*)this->parent();
		
		this->item_pathname(path,sizeof(path),item);
		printf("TREE PATH: %s\n",path);
		
		if (event == FL_RELEASE) {
			printf("REASON %d\n",this->callback_reason());
			switch(this->callback_reason()) {
				case FL_TREE_REASON_SELECTED:
					win->setBuffer(-1,path);
					used = 1;
					break;
			}
		}
	}
	else {
		// maybe do something with folders later
	}
	
	return used;
}