#include <string.h>

#include <Flute_Buffer_Manager.hh>


Flute_Buffer_Manager :: Flute_Buffer_Manager(int len) : b_vec(len) {
// 	printf("length:%d\n",this->b_vec.size());
}


void Flute_Buffer_Manager :: closeBuffer(int buffID) {
	this->b_vec[buffID] = NULL;
}


Flute_Buffer* Flute_Buffer_Manager :: getBuffer(int buffID) {
	return this->b_vec[buffID];
}


int Flute_Buffer_Manager :: getBufferID(const char* path) {
	int i,id,len;
	
	id = -1;
	len = this->b_vec.capacity();
	
	for(i=0;i<len;i++) {
		if (this->b_vec[i]) printf("%s == %s\n",path,this->b_vec[i]->getPath());
		if (this->b_vec[i]
			&& !strcmp(this->b_vec[i]->getPath(),path)) id = i;
	}
	
	return id;
}


int Flute_Buffer_Manager :: getBufferID(Flute_Buffer* buff) {
	int i,id,len;
	
	id = -1;
	len = this->b_vec.capacity();
	
	for(i=0;i<len;i++) {
		if (this->b_vec[i] == buff) break;
	}
	
	return id;
}


void Flute_Buffer_Manager :: printAll() {
	int len = this->b_vec.capacity();
	Flute_Buffer* buff;
	
	printf("===== TOTAL [%d] =====\n",len);
	
	for(int i=0;i<len;i++) {
		buff = this->b_vec[i];
		if (buff) {	
			printf("[%d] BUFFER %s (%d)\n",i,buff->getPath(),buff->getID());
		}
		else {
			printf("[%d] EMPTY\n",i);
		}
	}
	
	printf("=====  END  =====\n");
}


int Flute_Buffer_Manager :: setBuffer(const char* path) {
	int buffID;
	
	buffID = this->getBufferID(path);
	
	if (buffID == -1) {
		buffID = this->_getFreeID();
		
		this->b_vec[buffID] = new Flute_Buffer(buffID,path);
// 		this->b_vec[buffID]->loadfile(path);
	}
	
	return buffID;
}


int Flute_Buffer_Manager :: setBuffer(Flute_Buffer* buff) {
	int buffID;
	
	buffID = this->_getFreeID();
	
	this->b_vec[buffID] = buff;
	this->b_vec[buffID]->setID(buffID);
	
	return buffID;
}


int Flute_Buffer_Manager :: _getFreeID() {
	int i,id,len;
	
	id = -1;
	len = this->b_vec.capacity();
	
	for(i=0;i<len;i++) {
		if (!this->b_vec[i]) {
			id = i;
			break;
		}
	}
	
	if (id == -1) {
		id = len;
		
		this->b_vec.resize(len*2);
	}
	
	return id;
}


