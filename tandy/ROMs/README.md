# tandy/ROMs

This folder contains ROM dumps for various pieces of VIS hardware.  These are unmodified ROMs as-found in the Tandy hardware.  For any patched ROMs, look in this repository under /tjbchris/ROMs.  

## Table of Contents

* **serial_debug_card.bin** - This is the Hakiu Remote Filesystem ROM that is found on the Serial Loader card.  This ROM allows the VIS to redirect file requests to a connected PC running RFSERVER (See Modular Windows documentation) instead of to files on the CD-ROM in drive A:.  This is useful for debugging applications and testing without mastering new application discs.
* **gryphon_video_dev_bios** - This is the Gryphon (VIS) video BIOS as-shipped on the Tandy-provided development cards used to emulate a VIS environment using a PC.  The video card is one of four development cards.  This BIOS was taken from that card.