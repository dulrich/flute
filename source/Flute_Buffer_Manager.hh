#include <list>
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

	Flute_Buffer* getLastBuffer(); // get the most recently used buffer
	Flute_Buffer* getLastBuffer(int from_back); // get the most recently used buffer

	Flute_Buffer* getBuffer(int buffID);
	Flute_Buffer* getBuffer(const char* path);

	int getBufferID(const char* path);
	int getBufferID(Flute_Buffer* buff);

	int setBuffer(const char* path);
	int setBuffer(Flute_Buffer* buff);

protected:
	std::vector<Flute_Buffer*> m_vec;
	std::list<int> m_history;

	int _getFreeID();
	void _setLastBuffer(int buffID);
};

#endif // Flute_Buffer_Manager_HH
