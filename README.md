Mellu-proto

2D Platformer with dynamic storytelling and awesome graphics.

Developed on Linux but Windows is target platform so cross platform compile has
been maintained and primary priority across the development cycle.

Command line options
    --fps [unsigned integer]
        Framelimit is controlled through this option(Default : 60).
        Stability cannot be promised when going over 60.
    --edit [boolean]
        Map editor has been programmed into the software(Default : 0).
	Through this option you can switch between Game and Edit mode.
	True 1, False 0.
    --map [string]
        Map can be changed when runned from command line(Default : PROTO).
	There are currently only one map included. TODO When maps are added list them here.

Deps 
    boost(1.54 or greater) static
    sfml(2.1 or greater) dynamic
    sqlite3

Sqlite (On windows)
    Sqlite is distributed as .def and .dll. Move the DLL into
    binary folder and create .lib with the following command for linkage.

    lib /DEF:"C:\SQLite\sqlite3.def" /OUT:"C:\SQLite\sqlite3.lib"

Boost
    Boost is linked as static library but it requires following as compiled libraries
    system, program_options, filesystem. Tested with boost version 1.55, 1.56 and 1.57.

SFML
    SFML is linked as dynamic library and manages all the rendering.
    Developed against SFML 2.1, newer versions hasnt been tested.

Screenshot!
![alt tag](https://raw.githubusercontent.com/Velho/mellu-proto/master/screenshot.png)
