/* Save-It Card Dump Utility: Get the size of the insterted Save-It card, 
   then attempt to read that many bytes from it and dump to a disk file.
   
   Uses undocumented VIS INT 15H AL=02 calls found in BIOS source.  Use on PC, not VIS!
   Requires Unobtanium Save-It PC Expansion Card from Tandy.  Run GBIOS.COM 
   before using!
   
   This must be compiled with the Large memory model or larger.  Otherwise fwrite will
   strip the segment off of the buffer pointer and read the wrong area of RAM.
   
   Just for learnding.	(C) 2025 TJBChris (Christopher Hyzer)
   See LICENSE.TXT for license info.
*/

#define VERSION "01.00.00"
#define BLDDATE "19-Dec-2025"    
#define DOS 1      
#define BLOCK_SIZE 512

// Boilerplate...
#include <stdio.h>
#include <dos.h>
#include <windows.h>
#include <string.h> 
#include <malloc.h>
#include "MC.H"

/* Direct Save-It IO requires a specific structure (derived from equates below) from BIOS source (CYBER.INC); 
   orig. written by Russell H. at Tandy in 1992.  Thanks, Russell!

	  	DESTINATION     equ     BP + 0
		SOURCE          equ     BP + 4
		COUNT           equ     BP + 8
		FLAGS           equ     BP + 10

*/       

// Avoid compiler data structure performance optimizations; this needs to be
// contiguous.
#pragma pack(1)
typedef struct xferStruct {
		void far *pBuffer;
		unsigned long SOURCE;
		unsigned short COUNT;
		unsigned long FLAGS;
} xferStruct;
#pragma pack()

typedef char _size_check[(sizeof(xferStruct) == 14) ? 1 : -1];

// Prototypes...
int main(int argc, char *argv[]);
static int dumpCard(long cardSize); // cardSize is in bytes.
static int saveItInt15(unsigned char bh_func, xferStruct far *pkt);
static int saveItRead(void far *dst, DWORD start, WORD count);

// Read from the Save-It card. This could probably be consolidated...
static int saveItRead(void far *dst, DWORD start, WORD count)
{
    xferStruct packet;

    packet.pBuffer = dst;
    packet.SOURCE  = start;
    packet.COUNT   = count;
    packet.FLAGS	= 0UL;

    return saveItInt15(0x02, (xferStruct far *)&packet);
}

// saveIt INT 15H call.
static int saveItInt15(unsigned char bh_func, xferStruct far *packet)
{

	// Adatped from BIOS source (CYBER.INC); orig. written by Russell H. at Tandy in 1992.
	// Thanks, Russell!

    union REGS r;
    struct SREGS s;

    memset(&r, 0, sizeof(r));
    memset(&s, 0, sizeof(s));

    r.h.ah = 0x71;
    r.h.al = 0x02;        /* Save-It device */
    r.h.bh = bh_func;     /* 0x02=READ, 0x03=WRITE */
    r.h.bl = 0x00;        /* BL != 0 returns error. */

    r.x.dx	= FP_SEG(packet);
    r.x.si	= FP_OFF(packet);

    int86x(0x15, &r, &r, &s);

    // 0x71 is returned in AX if successful.
    return (r.x.ax == 0x0071) ? 0 : -1;
}

// Loop through CARD_SIZE / BLOCK_SIZE blocks and write the contents to the file.
static int dumpCard(long cardSize) {   

	int blockNum = 0, i = 0;
	void far *buffer = _fmalloc(BLOCK_SIZE);
	
	FILE *outFile;
	
	// Allocate the buffer.
    if (!buffer) {
        fprintf(stderr, "Couldn't allocate buffer (%u bytes).\n", (unsigned)BLOCK_SIZE);
        return 1;
    }
        
	// Set buffer to zero for testing.        
    _fmemset(buffer, 0, BLOCK_SIZE);
    
    outFile = fopen("saveit.bin","wb");      
    if (outFile == NULL) {
    	printf("Error opening file.  Exiting.\n");
    	return 1;
    }
	
	printf("Dumping %u-byte blocks of %u bytes.\nBlock: ", BLOCK_SIZE, cardSize);            
    for (blockNum; blockNum < (cardSize/BLOCK_SIZE); blockNum++) {

      printf("%u ", blockNum);   
      if(saveItRead(buffer, (blockNum * BLOCK_SIZE), BLOCK_SIZE)) {
      	  _ffree(buffer);  
	  	  fclose(outFile);
	  	  printf("Failed to read from Save-It card.\n");
	  	  return 2;
	  }

	  // Write it (this line here is why we use a Large memory model).
      if ((fwrite(buffer, sizeof(unsigned char), BLOCK_SIZE, outFile)) != BLOCK_SIZE) {
		  printf("Failed to write to output file.\n");
	  	  _ffree(buffer);  
	  	  fclose(outFile);
	  	  return 1;
	  }
         
	}   

	// Un-allocate the buffer.	               
	_ffree(buffer);
	fclose(outFile);	
	
	printf("\n\nDone reading from card.\n");
	return 0;

}

int main (int argc, char *argv[]) {

	DWORD status;
	int errCode;

	MCSTATUS cardStatus;  
	MCSTATUS far* statusPtr = &cardStatus;   
	
	cardStatus.wHdrSize = sizeof(cardStatus);   
	
	// Raw cards lack the MS TOC, which trips up mcInit and mcStatus.
	// This arg allows one to bypass that.
	if (argc < 2) {
	
	    // Init the card.
	    // These constants brought to you by MC.H.
	    status = mcInit(MCINIT_START);
	    if (status) {
			printf("Failed to init card.\n");
			return 1;
    	}
    
	    // Populate the cardStatus struct with facts about the card.
	    status = mcStatus(statusPtr);
	    if (status) {
			printf("Failed to get status from card.\n");
			return 1;
    	}
    
	    // Close out.
	    status = mcInit(MCINIT_END);
	    if (status) {
			printf("Failed to de-init card.\n");
			return 1;
    	}

	}
    // "Show me what you're working with..." (Name that tune!)
    printf("\nSave-It Card Dump Utility by TJBChris.\n--------------------------------------\n");
    
    if (argc > 1) {
    	printf("RAW mode.  Skipping MS' mcInit and mcStatus checks.\n\n");
    } else { 
    	printf("Reported RAM size: %uK\n", (cardStatus.dwTotalRAM/1024));
    	printf("Card ID: %u\n\n", cardStatus.mcid);
    }
    
	printf("Dumping card data to SAVEIT.BIN...\n");  

	// Dump the detected card size to the file.
	// Hard-coded to 32K for now...all cards were 32K and bootable cards F with things.
    errCode = dumpCard(32768);         
	printf("Error code: %d\n", errCode);
	
    return errCode;

}
