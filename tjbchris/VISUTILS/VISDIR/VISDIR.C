/*
	VISDIR.C - Try to get a directory listing from the drive
			   specified.  For sussing out suspected ROM drives
			   on the Memorex (Tandy) VIS.

	See LICENSE.TXT for license details.
	TJBChris - 9/12/2025
*/
#include <dos.h>
#include <stdio.h>

// Function prototypes
int main(int argc, char *argv[]);
void printString(char *text); 
void listDir(char* path);     

/* Prints a string on the display using INT 10H BIOS calls */
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

void listDir(char* path) {

	struct find_t dirent;
		
	if (_dos_findfirst(path, _A_NORMAL | _A_SUBDIR, &dirent) == 0) {
		printString("Listing directory of: ");
		printString(path);
		printString("\r\n");
		
		do {
			if(dirent.attrib & _A_SUBDIR) {
				printString(dirent.name);
				printString(" <DIR>\r\n");
			}
			else {
				printString(dirent.name);
				printString("\r\n");
			}
		} while(_dos_findnext(&dirent) == 0);
	} else {
		printString("Error reading ");
		printString(path);
		printString("\r\n");
	}
}

int main(int argc, char *argv[]) {

	// Basic error conditions.
	if (argc != 2) {
		printString("Usage: VISDIR path\r\n\tEx: VISDIR C:\\\r\n");
		return 1;
	}

	listDir(argv[1]);
	
	return 0;
}