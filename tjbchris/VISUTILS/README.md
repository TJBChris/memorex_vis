# tjbchris

This folder contains resources (doc, code, utilities) I wrote during my time exploring the VIS platform.  

**IMPORTANT:** Most of the utilities and programs in this folder are designed to be run from the BROWSE.COM mini-shell that runs on the VIS player. They will not work on the VIS in a standalone mode.  Additionally, **CRDDUMP** runs on a PC only and requires GBIOS.COM (found in the tandy/GBIOS area of this repo).

## Compiler Info
All of the utilities in this folder were compiled using Microsoft Visual C++ 1.5 for Windows 3.1.  Those utilities with a .MAK file in the directory should be opened as a **Project** from within Visual C++.  The remainder can be opened as a standalone .C file.  Each should be compiled as an MS-DOS Application, targeting the 80286 processor.  All utilities except CRDDUMP using a *medium* memory model. *CRDDUMP uses the large memory model.*

## Table of Contents
Each folder contains source code which can be compiled for use on the VIS (except CRDDUMP).  To use the executables, simply add them to your VIS disc containing BROWSE.COM (and related files).  All of these executables should also work on a standard MS-DOS PC with DOS version 3.20 or later. 

* **CRDDUMP** - Runs on a PC only.  This utility allows you to dump the contents of a 32K Save-It card to a file named SAVEIT.BIN.  With no command line options, it will attempt to query the card info.  With any parameter as the first argument, it will skip the MS structure/status check and go straight to the card dump.  **This utility requires the very rare Tandy VIS Developer card set with the CyberCard interface.**  Compile with the Large memory model, run GBIOS.COM before using this utility.
* **CRDSIZE** - Returns information about the Save-It Cartridge installed in the VIS.  Returns RAM and ROM size, free RAM, and the Card ID.  To use this on a PC, you'll need the rare Tandy VIS Developer card set installed and GBIOS.COM installed.
* **DRVLIST** - Lists the available (attached) drive letters.  In the VIS, this will liekly return no drives.  Run on a standard MS-DOS PC will list all (or most) drives known to MS-DOS.
* **VISDIR** - Lists files matching a given search string.  For example, VISDIR A:\*.* or VISDIR B:*.  Not very smart (it wasn't meant to be).
* **VISVER** - Displays the MS-DOS version as-reported by Haiku DOS.  Note that the version number returned is a *rough approximation* as to how Haiku DOS aligns with the mainline MS-DOS version families, not an absolute.
* **LICENSE.TXT** - The GPLv3 license that applies to all of these utilities.

## What's With the PrintString function?
Because the VIS doesn't have a character mode screen, standard printf(...)-style calls usually don't work.  The BROWSE.COM utility (and its companion GOROM.COM) sets up a graphics mode and simple character set to mimic a text screen.  Characters are "printed" on this simulated text screen via INT 10H TeleType Output calls.  

There may be a better way, but this is how I set it up the first time I wanted to print text.  Because I'm lazy, I simply reused it in subsequent utilities.

## Support
There isn't really any support.  These were quick-and-dirty utilities created while I was experimenting or trying to answer a specific question.  Feel free to use them as an outline for something else or to make them better.  

## License

All of these utilities are licensed under the GPLv3 license.  See LICENSE.TXT.
