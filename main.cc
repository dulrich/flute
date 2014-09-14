// COPYRIGHT AND LICENSE SEE FILE: LICENSE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#ifdef __MWERKS__
# define FL_DLL
#endif

#include <Flute_Buffer.hh>
#include <Flute_Buffer_Manager.hh>
#include <Flute_Config.hh>
#include <Flute_Window.hh>
#include <Flute_DEFINES.hh>

int test_buffer_manager();

Flute_Buffer*         buffer;
Flute_Config*         config;
Flute_Window*         window;

int main(int argc, char* argv[]) {
	config = new Flute_Config();
	
	buffer = new Flute_Buffer(-1,"~/Untitled");
	buffer->text("one\ntwo\nthree");
	
	int winH,winW;
	
	winH = config->getOpt("win_h");
	winW = config->getOpt("win_w");
	
	window = new Flute_Window(winW,winH,"FLUTE",config);
	
	window->init();
	
	window->setBuffer(1,buffer);
	Fl::visual(FL_DOUBLE|FL_INDEX);
	window->show();
	
// 	test_buffer_manager();
	
	return (Fl::run());
}


int test_buffer_manager() {
	Flute_Buffer_Manager* bm = new Flute_Buffer_Manager(1);
	
	bm->printAll();
	
	const char* cPath = "/code/flute/Config.hh~";
	int cID,ID;
	cID = bm->setBuffer(cPath);
	bm->printAll();
	
	ID = bm->getBufferID(cPath);
	printf("GOT IDS: [%d] AND [%d]\n",cID,ID);
	printf("TEXT: %s\n",bm->getBuffer(ID)->text());
	
	const char* cPath1 = "/code/flute/Makefile~";
	int cID1,ID1;
	cID1 = bm->setBuffer(cPath1);
	bm->printAll();
	
	ID1 = bm->getBufferID(cPath1);
	printf("GOT IDS: [%d] AND [%d]\n",cID1,ID1);
	bm->getBuffer(ID)->append("\n ur a buffer");
	printf("TEXT: %s\n",bm->getBuffer(ID)->text());
	printf("TEXT: %s\n",bm->getBuffer(ID1)->text());
	
	int IDX = bm->getBufferID(cPath);
	printf("GOT IDS: [%d] AND [%d]\n",IDX,ID);
	
	bm->closeBuffer(bm->getBufferID(cPath));
	bm->printAll();
	
	const char* cPath2 = "/code/flute/README.md";
	int cID2,ID2;
	cID2 = bm->setBuffer(cPath2);
	bm->printAll();
	ID2 = bm->getBufferID(cPath2);
	printf("GOT IDS: [%d] AND [%d]\n",cID2,ID2);
	
	const char* cPath3 = "/code/flute/Flute_DEFINES.hh";
	int cID3,ID3;
	cID3 = bm->setBuffer(cPath3);
	bm->printAll();
	ID3 = bm->getBufferID(cPath3);
	printf("GOT IDS: [%d] AND [%d]\n",cID3,ID3);
}