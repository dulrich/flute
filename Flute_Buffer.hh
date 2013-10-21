#ifdef __MWERKS__
# define FL_DLL
#endif

#include <string>

#include <FL/Fl.H>
#include <FL/Fl_Text_Editor.H>

#include <Flute_DEFINES.hh>

#ifndef Flute_Buffer_HH
#define Flute_Buffer_HH

class Flute_Buffer : public Fl_Text_Buffer {
public:
	Flute_Buffer(int id,const char* path);
	Flute_Buffer(int requestedSize=0,int preferredGapSize=1024,int id=-1,const char* path="");
	
	int getID();
	const char* getPath();
	void setID(int id);
	void setPath(const char* path);
	
protected:
	int w_id;
	std::string w_path;
	
	void _init(int id,const char* path);
};

#endif // Flute_Buffer_HH