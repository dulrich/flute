#ifdef __MWERKS__
# define FL_DLL
#endif

#include <FL/Fl.H>
#include <FL/Fl_Tree.H>

#include <Flute_DEFINES.hh>

#ifndef Flute_Tree_HH
#define Flute_Tree_HH

class Flute_Tree : public Fl_Tree {
public:
	Flute_Tree(int x,int y,int w,int h);
	
	int handle(int e);
};

#endif // Flute_Tree_HH
