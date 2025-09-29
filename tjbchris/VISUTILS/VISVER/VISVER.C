/* 
   VISVER.C - Get the MS-DOS version reported by the VIS.
   See LICENSE.TXT for license details.
   TJBChris - 9/12/2025            
*/

#include <stdio.h>
#include <dos.h>   
#include <string.h>
           
// Function prototypes.           
int main();
void printString(char *text);

// String print for VIS.
void printString(char *text) {

	union REGS regs;
	int i=0;

	for (i = 0; text[i] != '\0'; i++) {
	    // Set AH=0Eh (Teletype Output), AL=character, BH=page number (0), BL=color
	    regs.h.ah = 0x0E; // Teletype Output function for BIOS INT 10h
	    regs.h.al = text[i]; // Character to print
	    regs.h.bh = 0;	     // Display page 0
	    regs.h.bl = 0x07;	     // White on black color
	    int86(0x10, &regs, &regs); // Call BIOS INT 10h to display the character
    }

}

// Just go.
int main(void) {

	// Processor registers.
	union REGS regs;
	char mv[2];
	char miv[4];
	
	printString("TJBChris' VIS Haiku DOS version extractor.\r\n");
	
	regs.h.ah = 0x30;
	
	// INT 21 AH=0x30 - Get DOS Version.
	printString("DOS Version: ");
	int86(0x21, &regs, &regs);
	
	sprintf(mv, "%02d", regs.h.al);
	sprintf(miv, "%02d", regs.h.ah);
	
	printString(mv);
	printString(".");
	printString(miv);
	printString("\r\n\r\n");
	
	return 0;
}