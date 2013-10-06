#include <Flute_DEFINES.hh>

#ifndef Flute_Config_HH
#define Flute_Config_HH

class Flute_Config {
	public:
		Flute_Config ();
		Flute_Config (char *path);
		
		int getOpt(char *opt);
};

#endif // Flute_Config_HH