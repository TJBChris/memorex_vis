# microsoft

This folder contains libraries, headers, etc. necessary to compile my VIS utilities using period-correct Microsoft compilers.

## Table of Contents

* **MC.H** - C header file for Save-It libraries.  Used for either set of libraries below.
* **MCD.LIB** - C library file for **Haiku DOS** applications.  Be sure to **#DEFINE DOS 1** in your C source to enable the mcInit function.
* **MC.LIB** - C library file for **Modular Windows** applications.