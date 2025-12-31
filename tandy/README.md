# tandy

This folder contains utilities, documentation, and the like authored by Tandy Corp.  

## Table of Contents

* **doc** - Contains documents and reference materials.
* **register** - Contains utilities and data files needed to create VIS license keys and generate the CONTROL.TAT file needed to run software on the VIS. 
* **NTSCDISC** - NTSCDISC is Tandy's tutorial and reference disc for developers which covers the VIS menu system as well as covering video and image considerations when writing applications for VIS.  It covers common issues such as pincushoning, image bleed, flicker, and the like as well as offering remedies for some of these issues.  To use, burn the contents of this folder to the root of a CD-R and run it on your VIS.  It also includes some software utilities.
* **GBIOS** - Contains the GBIOS.COM TSR version 1.10.  This utility is used on a PC in combination with the (very rare) Tandy Developer Card set to allow the PC to respond to VIS INT 15H AH=71H calls using the developer card set.  Without these developer cards, this utility is of little use.