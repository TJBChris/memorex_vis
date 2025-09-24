# register

This folder contains MS-DOS-based utilities that can be used register and run your application on the VIS.  

## Table Of Contents

The files are as follows:

* **REGISTER.EXE** - Uses data in REGISTER.DAT to generate license keys for VIS titles.  
* **REGISTER.DAT** - The VIS title registration database.  This is a human-managed text file containing vendor, title, and license classification information for VIS titles.
* **JOBD** - A template title definition that is used by MAKETAT.EXE to generate the CONTROL.TAT file needed to run titles on VIS. 
* **MAKETAT.EXE** - Creates CONTROL.TAT using the settings and license key contained within the JOB file.

## Process

To create a title for VIS, your disc must have a file named **CONTROL.TAT** in the root directory of the disc.  This file describes the title and tells VIS what to execute when the title starts.  In addition, CONTROL.TAT contains licensing information that tells tells the VIS player which functionality to make available and whether the title is a "fully authorized" VIS title.  See the **Licensing** section below.  CONTROL.TAT is protected from tampering, so exiting files cannot be hand-edited.

The REGISTER.DAT and REGISTER.EXE files were used within Tandy Corp. to manage vendors and titles; it was never available/used by anyone outside of Tandy.  JOBD and MAKETAT.EXE were provided to vendors along with the license key for a given title.  

The **JOBD** file contains verbose descriptions of the fields with examples, making it easy to get started.  In addition, the sample license key found in JOBD is valid and can be used to create a Class C title for the VIS.

**REGISTER.DAT** contains some example titles and is formatted as follows:

VENDOR "TANDY CORPORATION, R&D" "KEN STEELE" 80  
PRODUCT "FACTORY DIAGNOSTIC DISC" 1  
LICENSE A DATE "23-JUL-92"  

Most of the file is self-explanatory.  See **Licensing** below for information on the license classes.  The first field in the VENDOR line is the vendor's company name.  The second field is the name of the person representing the title at that vendor.  The number in the first line (80) is the Vendor ID number.  All titles by the same vendor used the same Vendor ID.  The number on the second line (1) is the title number, starting at 1.  A vendor was required to get a separate key for *each* title they were developing.  It was against the license agreement to reuse keys.  Both REGISTER.DAT and REGISTER.EXE muust be in the same directory to work correctly.

The process for registering your title and getting a valid CONTROL.TAT is as follows:

1.  Edit REGISTER.DAT, copying an existing title to use as a template for your new title.  See the description above.
1.  Run REGISTER.EXE.  You will be asked for a vendor ID and title ID number, as well as the license class.  You'll then be provided with a license key.
1.  Make a *copy* of the JOBD file with a descriptive name for your title.  For example: **AWESOME.JOB**
1.  Edit **AWESOME.JOB** and enter your license key.  Then, update the remaining fields documenting the title's name, and the executables to be run. 
1.  Generate CONTROL.TAT by running **MAKETAT AWESOME.JOB**

If your JOB file was correct, MAKETAT will produce a CONTROL.TAT file.  Place that file in the root of your VIS CD-ROM along with your application.

## Licensing

VIS titles were classified to signify both the vendor's rights to use the VIS logo as well as tell the player which functionality to make available.  There were only two classes that were implemented for the VIS:

* **A** - A fully-licensed title.  This vendor had the right to use the VIS logo in their title, on packaging, and in advertisements.  Class A titles can make use of the VIS' built-in menu system.  These titles also cause the VIS to display the text "Authorized Video Information System Title" during startup.
* **C** - Titles that were not granted the right to use the VIS logo.  Often used for development/testing (I know of no retail class C titles).  These titles could not use the VIS' built-in menu system and did not display the "Authorized" text during startup.