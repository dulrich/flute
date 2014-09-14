#include <Flute_Buffer.hh>

Flute_Buffer :: Flute_Buffer(int id,const char* path) : Fl_Text_Buffer() {
	init(id,path);
}

Flute_Buffer :: Flute_Buffer(int requestedSize,int preferredGapSize,int id,const char* path)
							 : Fl_Text_Buffer(requestedSize,preferredGapSize) {
	init(id,path);
}

void Flute_Buffer :: init(int id,const char* path) {
	this->loadfile(path);
	this->setID(id);
	this->setPath(path);
	this->tab_distance(4);
}


int Flute_Buffer :: getID() {
	return m_id;
}


const char* Flute_Buffer :: getPath() {
	return m_path.c_str();
};


void Flute_Buffer :: setID(int id) {
	m_id = id;
}


void Flute_Buffer :: setPath(const char* path) {
	m_path.assign(path);
};



