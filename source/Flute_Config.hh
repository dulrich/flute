#include <string>
#include <vector>

#include <Flute_DEFINES.hh>

#ifndef Flute_Config_HH
#define Flute_Config_HH


class Flute_Config {
	class Flute_Config_Opt {
		public:
			Flute_Config_Opt() : Flute_Config_Opt("",0) {
				// nothing
			};

			Flute_Config_Opt(const char *name, int val) {;
				m_name.assign(name);
				m_val = val;
			};

			Flute_Config_Opt(std::string name, int val) {;
				m_name.assign(name);
				m_val = val;
			};
			
			std::string m_name;
			int m_val;
	};
	
	public:
		Flute_Config ();
		Flute_Config (const char *path);
		
		int getOptID(const char *opt);
		int getOpt(const char *opt);
		void printAll();

	protected:
		std::vector<Flute_Config_Opt*> m_settings;
};

#endif // Flute_Config_HH
