#include <vector>

#include <Flute_DEFINES.hh>
#include <Flute_Buffer.hh>

#ifndef Flute_Buffer_Manager_HH
#define Flute_Buffer_Manager_HH

class Flute_Buffer_Manager {
public:
	Flute_Buffer_Manager(int len=16);
	
	void printAll();
	
	void closeBuffer(int buffID);
	
	Flute_Buffer* getBuffer(int buffID);
	
	int getBufferID(const char* path);
	int getBufferID(Flute_Buffer* buff);
	
	int setBuffer(const char* path);
	int setBuffer(Flute_Buffer* buff);

protected:
	std::vector<Flute_Buffer*> b_vec;
	
	int _getFreeID();
};

#endif // Flute_Buffer_Manager_HH
