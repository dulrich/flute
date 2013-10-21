#include <Flute_DEFINES.hh>

#ifndef Flute_Config_HH
#define Flute_Config_HH

class Flute_Config {
	public:
		Flute_Config ();
		Flute_Config (const char *path);
		
		int getOpt(const char *opt);
};

#endif // Flute_Config_HH