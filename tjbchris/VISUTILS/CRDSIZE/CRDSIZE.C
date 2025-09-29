/* Save-It Card Size Utility: Get the size of the insterted Save-It card.
   Just for learnding.	(C) 2025 TJBChris (Christopher Hyzer)
   See LICENSE.TXT for license info.
*/

#define VERSION "01.00.00"
#define BLDDATE "29-Sep-2025"    
#define DOS 1      

// Boilerplate...
#include <stdio.h>
#include <dos.h>
#include <windows.h>
#include <string.h>
#include "MC.H"

// Prototypes...
int main();
void printString(char *text);
/* Prints a string on the display using INT 10H BIOS calls */

// Where the real money from the movie is made...
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

int main () {
    
 
	DWORD status;
	char romsize[32],ramsize[32],freeram[32], cardId[16];

	MCSTATUS cardStatus;  
	MCSTATUS far* statusPtr = &cardStatus;
	
	cardStatus.wHdrSize = sizeof(cardStatus);
	
    // Init the card.
    // These constants brought to you by MC.H.
    status = mcInit(MCINIT_START);
    if (status) {
		printString("Failed to init card.\r\n");
		return 1;
    }
    
    // Populate the cardStatus struct with facts about the card.
    status = mcStatus(statusPtr);
    if (status) {
		printString("Failed to get status from card.\r\n");
		return 1;
    }
    
    // Close out.
    status = mcInit(MCINIT_END);
    if (status) {
		printString("Failed to de-init card.\r\n");
		return 1;
    }
       
    sprintf(romsize,"%d",(cardStatus.dwTotalROM/1024));
    sprintf(ramsize,"%d",(cardStatus.dwTotalRAM/1024));
    sprintf(freeram,"%d",(cardStatus.dwFreeRAM/1024));
    sprintf(cardId,"%d",cardStatus.mcid);
    
    // "Show me what you're working with..." (Name that tune!)
    printString("\r\nSave-It Card Info by TJBChris.\r\n------------------------------\r\nROM size: ");
    printString(romsize);
    printString("K\r\nRAM size: ");
    printString(ramsize);
    printString("K\r\nRAM free: ");
    printString(freeram);
    printString("K\r\nCard ID: ");
    printString(cardId);
    printString("\r\n\r\n");
    
    return 0;

}
