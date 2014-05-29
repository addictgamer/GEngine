Generic engine intended for games.

Compiling
=========

Dependencies
------------

* A C++11-compatible compiler
* GLEW
* GLM
* SFML
* Boost
* SQLite (will be optional eventually)
* CEGUI
* FMOD

Windows users
-------------
One of us developers is able to compile this with MinGW in Windows. Use ./cm after having edited it to reflect the paths to various libraries.
Requires, in its current state, MinGW.

Linux and Mac users
-------------------
CD to directory in a terminal and type `./lm`. This will install to the source directory, creating bin/ and include/ directories. If you want to install it elsewhere, use cmake directly:
```
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/wherever/you/want/to/install/it/to
make install
```
Use sudo for make install if you want to install it in /usr/local or similar.

Credits
=======
Check the Credits file.


Bugs
====
If you find any bugs, please report them to the dev team. Either by opening up an issue in the repos...or posting in the forums...or emailing us...

Devs
====
Read the file: dev
