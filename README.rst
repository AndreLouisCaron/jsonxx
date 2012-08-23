=====================================
  `jsonxx`: C++ interface for cJSON
=====================================
:authors:
   André Caron
:contact: andre.l.caron@gmail.com

Description
===========

This library provides a simple API for consuming JSON_ objects from C++.  The
intent of this library is to be a small, lightweight wrapper on the `cJSON`_
library.

.. _JSON: http://www.json.org/
.. _cJSON: http://docs.python.org/c-api/

Requirements
============

#. A C++ compiler toolchain:

   * Microsoft Visual Studio (for Microsoft Windows).  The code base has not
     been tested on versions prior to 2008.  Should work on both the Express
     and Professional versions.
   * GCC (for UNIX-like systems)

#. CMake_
#. Git_ (unless you download the sources as an archive)
#. Doxygen_ (to build the API documentation)

.. _CMake: http://www.cmake.org/
.. _Git: http://git-scm.com/
.. _Doxygen: http://www.stack.nl/~dimitri/doxygen/

Compiling
=========

#. Open up a terminal (command prompt).
#. Get the source code.

   ::

      git clone git://github.com/AndreLouisCaron:jsonxx.git
      cd jsonxx

#. Have CMake_ generate build scripts.

   ::

      mkdir work
      cd work
      cmake -G "NMake Makefiles" ..

#. Build using your favorite toolchain.

   ::

      nmake

#. Enjoy!
