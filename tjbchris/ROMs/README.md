# tjbchris/ROMs

This folder contains VIS ROMs that were patched by TJBChris for some reason or another.   

## Table of Contents

* **patched_serial_debug_card_com2.bin** - This is a patched ROM for the Serial Loader / Debug card which allows the Haiku Remote File System to work when the card is configured as COM2:.  The Tandy version I have (dated 9143) is hard-coded to COM1:.  To configure the card for COM2:
	1. Install a jumper to bridge JP1 (E8-E9) to switch card from COM1: to COM2:.
	1. Remove the jumper bridging E2-E4 and install it onto E1-E3 to set the card to IRQ6.
	1. Ensure JP2 (E15-E17) is bridged and jumpers JP3 thorugh JP5 are un-bridged.  JP2 enables the boot ROM.
	1. Ensure E6-E7 is bridged, leaving E5 unconnected.  I'm not sure what this does.
	1. Flash this image to a 27256 (32K-bit) EPROM and install into socket U8.