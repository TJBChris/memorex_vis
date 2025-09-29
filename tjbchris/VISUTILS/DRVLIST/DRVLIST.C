/* 
   DRVLIST.C - List "available" drive letters onthe VIS (or any MS-DOS-ish system)
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
	int i=0;
	int driveNumber;	
	char driveLetter[3] = "A ";
	
	printString("DRVLIST - List available drive letters.  By TJBChris.\r\n");
	printString("Drives found: ");
	
	for (i=1; i<27; i++){
		
		driveNumber = 64 + i;
		
		// Function 0x44 (IOCTL), subfunction 0x08 (device removable query)	
		regs.x.ax = 0x4409;
	    regs.h.bl = i;
	    
		// Call INT 21
		int86(0x21, &regs, &regs);
		
		if (regs.x.cflag == 0) {  
			driveLetter[0]=(char)driveNumber;
			printString(driveLetter);
		}
	}
	printString("\r\nDone.\r\n");
	
	return 0;
}