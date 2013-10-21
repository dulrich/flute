#include <Flute_Buffer.hh>

Flute_Buffer :: Flute_Buffer(int id,const char* path) : Fl_Text_Buffer() {
	this->_init(id,path);
}

Flute_Buffer :: Flute_Buffer(int requestedSize,int preferredGapSize,int id,const char* path)
							 : Fl_Text_Buffer(requestedSize,preferredGapSize) {
	this->_init(id,path);
}


void Flute_Buffer :: _init(int id,const char* path) {
	this->loadfile(path);
	this->setID(id);
	this->setPath(path);
	this->tab_distance(4);
}


int Flute_Buffer :: getID() {
	return this->w_id;
}


const char* Flute_Buffer :: getPath() {
	return this->w_path.c_str();
};


void Flute_Buffer :: setID(int id) {
	this->w_id = id;
}


void Flute_Buffer :: setPath(const char* path) {
	this->w_path.assign(path);
};



