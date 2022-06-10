#####################
#                   #
#  mrangeui ReadMe  #
#                   #
#####################

##
# About
##

The mrangeui project provides a simple animated interface to display 
both the current time and date.


##
# Requirements
##

Compilation:
------------
This project is built using CMake. You can find CMake here:

https://cmake.org/

Library Dependencies:
---------------------
This project requires other libraries and headers to function:

Dependency List:
libmrhbf: https://github.com/jbroerken/libmrhbf/
sdl2: https://www.libsdl.org/download-2.0.php
sdl2_image: https://www.libsdl.org/projects/SDL_image/
sdl2_ttf: https://www.libsdl.org/projects/SDL_ttf/

For more information about the requirements, check the "Building" section found in the documentation.


##
# Documentation
##

All documentation is build with sphinx-doc using the Read The Docs theme.
To build the documentation, grab the requirements for it:

sphinx-doc:
-----------
https://www.sphinx-doc.org/en/master/

Read The Docs Theme:
--------------------
https://sphinx-rtd-theme.readthedocs.io/en/stable/

##
# Licence
##

This project is licenced under the Apache 2.0 licence. 
Please read the included LICENCE.txt for the exact terms.


##
# Directories
##

This project supplies multiple directories for the development of said project. 
Their names and descriptions are as follows:

Directory List:
bin: Contains the built project executables.
build: CMake build directory.
doc: Documentation files.
res: Ressource Files (.png, .ttf)
src: Project source code.