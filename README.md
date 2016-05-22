# FLUTE

Fast Light Ultimate Text Editor.

Uses FLTK: `sudo apt-get install libfltk1.3-dev`

You need some other libraries too, libpng, libjpeg, libxinerama

`sudo apt-get install libpng++-dev libxinerama-dev libjpeg-dev libfontconfig1-dev libxft-dev`

Lua is required:

`sudo apt-get install liblua5.2-dev`

g++ 4.7 or higher is required for compilation.
```
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-get update
sudo apt-get install gcc-4.7 g++-4.7
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.7 20
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.7 20
```

Default Keyboard Shortcuts:
*	C-b		Previous Buffer
*	C-o		Open File
*	C-q		Quit
*	C-s		Save File
*	C-w		Close File


# license

Copyright 2013 - 2015  David Ulrich (http://github.com/dulrich)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
