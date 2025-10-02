# memorex_vis

This repository contains miscellaneous tools, utilities, and other resources for the Memorex MD-2500 Video Information System (VIS).  

## About the VIS

VIS is a CD-ROM-based set-top multimedia player that was targeted at the "edutainment" market with a MSRP of $699.95 (catalog number 16-376).  It was manufactured by Tandy Corp. and sold through their Radio Shack stores.  Development began in mid-late 1991, with VIS being released during the 1992 holiday shopping season.  The VIS was not a sales success.  After drastic price reductions, it was quickly discontinued.  Licensees quickly abandoned the platform; many planned titles were never released.  Tandy sold much of the remaining inventory to Tiger Direct, which resold these systems with a collection of 20 titles for a combined price of $99.  Tandy lost an estimated $75 million on the VIS project.  

In my mind, it was one of three events to unfold during 1992 that caused Tandy to exit the PC business.

## In This Repository

This repository contains the following folders.  See README.md within each folder for a listing of what's there.

* **tandy** - Contains utilities, documents, and the like that were written by Tandy Corp.
* **tjbhris** - Contains documentation, examples, and code that I've put together in my exploration of the platform.  Keep your expectations low.

## Basic hardware specs
From a hardware standpoint the VIS was molded after the standard IBM PC architecture, though it is not a vanilla IBM PC implementation.  It was thought a PC-like architecture would make porting titles easier than competing products such as the Philips CD-I.  For a multimedia machine, VIS was underpowered.  Titles were fairly sluggish, leading to returns.  The VIS shares some hardware with the original Tandy Sensation! (25-1650).  Shared hardware is marked with a (!).

The basic hardware consists of:

* 12 MHz 80286 processor.
* 1 MB of RAM (640K conventional + 384K XMS via HIMEM.SYS-like drivers).
* AdLib Gold-compatible sound (!)
* Custom Tandy Video DAC, supporting NTSC and PAL features, up to 16 million colors, allowing limited VGA and EGA mode support on television displays. (!)
* Mitsumi CD-ROM with a proprietary interface.  Whether that interface is the then-common Mitsumi CD-ROM interface is as-yet unknown.  The drive spins at 4x, but has VERY slow seek times, with the maximum seek time landing just north of one second.
* Proprietary local bus expansion slot.  VIS did not have an ISA bus and thus did not have ISA overhead common in older PC systems.  This was a factor in Tandy's choice of processor.  The pinout of this slot is currently unknown.  This may have been for expandable video capabilities, as noted by some former Tandy employees.
* Expansion connection for a modem.  The modem was never available at retail, and none of the ~75 titles for the VIS supported it.  The modem is the same one that was used in the original Tandy Sensation! (25-1650).
* RF, Composite, and S-Video outputs.  Stereo audio output was also available.
* PS/2 compatible port on the rear, which allowed users to attach a wired hand controller, keyboard, or mouse.
* Slot for Dallas Semiconductor-designed memory cartridges marketed as "Save-It" cartridges.  The slot supports cards up to 512K, though only 32K cards were ever available.  
* Infrared port for wireless infrared hand controllers (the standard mechanism for interacting with VIS).

VIS does not have support for character mode applications, CGA, or some EGA video modes.  Supported modes include a subset of VGA modes as well as OEM-specific YUV and planar video modes.  The standard modes are accessible via their standard identifiers (0x0D, for example), while the custom modes are found in the 0x50-range.  The supported EGA modes do not support customizable palettes; instead VIS will handle calls to customize the palettte by attempting to match the requested customization with one of four pre-defined palettes.  Custom VGA palettes are supported.

## Operating System / Software Specs

### DOS/Windows

VIS runs a highly customized version of MS-DOS and Windows 3.1 collectively branded as Modular Windows.  Within Microsoft, Modular Windows was assigned the code name **Haiku**.  Though VIS uses the same basic DOS and Windows architecture as the IBM PC, the DOS and Windows implementations are **highly** customized.  

From a DOS standpoint, many common INT 21H calls are modified, redirected, or unimplemnted.  There is no command interpreter.  A file named COMMAND exists in ROM, but references VIS BIOS extensions rather than being a command interpreter.  Additionally, there is no writable file system in VIS.  As a result, many common MS-DOS calls for file handling are absent or behave differently than expected.  There are two available drive letters in VIS:

* **A:** - The CD-ROM drive.
* **B:** - A redirector for executable code stored on the Save-It cartridge.  This was used during development of the VIS hardware.  The B: drive redirector presented one file (**CARD.EXE**) to MS-DOS if an executable Save-It cartridge was inserted.  The ability to boot from Save-It cartridges was removed from tbe BIOS in retail units.

Like DOS, Modular Windows is a highly-customized version of Windows 3.1 for set-top use.  The Kernel, GDI, and USER portions have significant changes.  Many common calls and functions available in Windows 3.1 are modified or removed.  For example:

* Menu bars are not supported.
* Common Dialog functions are not supported.
* Controls (buttons, radio buttons, etc.) are implemented differently via additional DLLs (TVUI.DLL).
* Additions were made to support the VIS' hand control, video modes, and Save-It functionality. 

The underlying DOS/Windows combination is stored in ROM, but their files are not accessible via a standard file system.  Detailed information can be found in the Modular Windows documentation.

### BIOS

Like MS-DOS and Windows, the VIS BIOS is heavily customized.  Calls for drives are missing or redirected.  Many of the VIS' distinct features, such as the hand controller, audio, and the like, are accessible via new custom BIOS INT handlers.  These can be access via INT 15H.  Some differences:

* VIS does not support keyboard scancode capturing via INT 09H redirects.  Instead, there are custom INT 15H calls that can be made.  This breaks many (many) DOS titles from the era, as many redirect INT 09H.
* Most calls regarding drive IO are missing or modified.  Querying the number of floppy drives returns no drives.
* The option ROM scan at boot had its scan range reduced dramatically.

The Modular Windows CD-ROM comtains a document, **VISBIOS.DOC**, which details changes to standard BIOS calls.  It also documents the new INT 15H calls in detail.  That document can also be found in this repository.

## Trivia / Other Facts / Misc.

Some other interesting trivia:

* Within Tandy, the VIS was codenamed "Gryphon" and was assigned project number 513.  
* Zenith was planning to sell VIS units under their brand; some Zenith-branded hand controllers were made.  Boxes and manuals were also printed for this unit, but it's believed that no actual Zenith VIS players were manufactured.  A cache of unused Zenith VIS boxes were found at Computer Reset.
* Businesses (such as Prudential insurance) used modified VIS players for traning.  These often had additional RAM, modems, and other hardware not made available through Radio Shack (though the modem was planned, as noted above).
* VIS could also function as an Audio CD player using a built-in Modular Windows application.  This would launch automaticaly if an Audio CD was loaded.  The application is sluggish, but it is workable and can save information about discs on Save-It cartridges.

## Links

You can find a lot more information about VIS on https://tandyvis.com.  This site was created by Tandy Showcase and is THE resouce for documentation and other infomation about VIS as it is uncovered.