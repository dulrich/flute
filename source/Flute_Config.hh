// FLUTE: Fast Light Ultimate Text Editor
// Copyright 2013 - 2014 David Ulrich
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

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
