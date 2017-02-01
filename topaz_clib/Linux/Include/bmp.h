
#define MAXCOLORS       256
#define Image				long

#define BitSet(byte, bit)  (((byte) & (bit)) == (bit))

//extern gint32 ToL(guchar *);
extern void FromL( int, unsigned char *);
//extern sint16 ToS(guchar *);
extern void FromS( short, unsigned char *);
//extern gint32 ReadBMP (char *);
extern bool	WriteBMP ( char* FileName, Signature* Sig );
extern bool	WriteBMP ( char* FileName, Signature* Sig, COLORREF ForeColor );


//extern gint ReadColorMap(FILE *, unsigned char[256][3], int, int, int *);
//extern Image ReadImage(FILE *, int, int, unsigned char[256][3], int, int, int, int, int);
extern void WriteColorMap( FILE*, int *, int *, int *, int);
extern void WriteImage( FILE*, unsigned char *,int,int,int,int,int,int,int, unsigned long);


struct Bitmap_File_Head_Type
  {
    unsigned long bfSize;		/* 02 */
    unsigned long reserverd;		/* 06 */
    unsigned long bfOffs;		/* 0A */
    unsigned long biSize;		/* 0E */
  }Bitmap_File_Head;

struct Bitmap_Head_Type
  {   
    unsigned long biWidth;		/* 12 */
    unsigned long biHeight;		/* 16 */
    unsigned short biPlanes;            /* 1A */
    unsigned short biBitCnt;	        /* 1C */
    unsigned long biCompr;		/* 1E */
    unsigned long biSizeIm;		/* 22 */
    unsigned long biXPels;		/* 26 */
    unsigned long biYPels;		/* 2A */
    unsigned long biClrUsed;		/* 2E */
    unsigned long biClrImp;		/* 32 */
    					/* 36 */
  }Bitmap_Head;
  
struct Bitmap_OS2_Head_Type
  {   
    unsigned short bcWidth;             /* 12 */
    unsigned short bcHeight;	        /* 14 */
    unsigned short bcPlanes;            /* 16 */
    unsigned short bcBitCnt;	        /* 18 */
  }Bitmap_OS2_Head;                

