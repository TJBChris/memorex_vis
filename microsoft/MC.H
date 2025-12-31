/*
 * MC.H  Header for memory card.                   
 * 
 * Copyright 1991,1992 Microsoft Corp.
 *
 */


typedef	BYTE _huge *HPBYTE;
typedef WORD	MCID;

typedef struct {
	
	WORD		wHdrSize;
	WORD		wStatus;
	DWORD		dwTotalROM;
	DWORD		dwTotalRAM;
	DWORD		dwFreeRAM;
	DWORD		dwUsedRAM;
	MCID		mcid;
	MCID		mcidReg;
	WORD		wCardVersion;
	BYTE		abReserved[8];

} MCSTATUS, FAR *LPMCSTATUS;

/*****************************************************************/

#define		CB_MAXSECTIONNAME	63

#ifdef DOS	// mcInit flags
#define		MCINIT_START	1
#define		MCINIT_END	2
#endif

// mcStatus return flags
#define		MC_CARDCHANGED		0x0001
#define		MC_CARDPRESENT		0x0002

// mcRegister flags
#define		MC_AUTOFORMAT		0x0001

#define	MC_NOERROR			0x0000
#define	MCERR_OK			0x0000

#define	MCERR_NOCARD			0x0002
#define	MCERR_CARDFULL			0x0003
#define	MCERR_NOTREGISTERED		0x0004
#define	MCERR_BADCARD			0x0005
#define	MCERR_CARDCHANGED		0x0006
#define	MCERR_CARDUNFORMATTED		0x0007
#define	MCERR_NOCORE			0x0008
#define	MCERR_OUTOFRANGE		0x0009
#define	MCERR_BADSECTIONNAME		0x000A
#define	MCERR_INTERNAL			0x000B
#define	MCERR_READONLY			0x000C
#define	MCERR_BADPARAMETER		0x000D
#define	MCERR_BADDATA			0x000E
#define MCERR_UNSUPPORTEDCARDVERSION	0x000F

/*****************************************************************/


DWORD FAR PASCAL mcRegister ( LPSTR lpszSection, WORD wFlags );
DWORD FAR PASCAL mcAlloc ( DWORD dwSize );
DWORD FAR PASCAL mcRead ( DWORD dwStart, DWORD dwLen, HPBYTE lpData);
DWORD FAR PASCAL mcWrite ( DWORD dwStart, DWORD dwLen, HPBYTE lpData);
DWORD FAR PASCAL mcStatus ( LPMCSTATUS lpMCS );

#ifdef DOS
BOOL FAR PASCAL mcInit ( WORD wFlags );
#endif
