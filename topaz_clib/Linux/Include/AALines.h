/*  FILENAME:  AALines.h  [revised 17 AUG 90]

    AUTHOR:  Kelvin Thompson

    DESCRIPTION:  Symbols and globals for the anti-aliased line
      renderer.

    #INCLUDED IN:
      AAMain.c -- Calling routine for renderer.
      AATables.c -- Initialization routines for lookup tables.
      AALines.c -- Rendering code.
*/

/* frame buffer to hold the anti-aliased line */
extern int		xpix;
extern int		ypix;
extern unsigned char	*fbuff;
extern int		pbsize;

#define	IS_VALID_PIXEL(baddr) (((baddr>=fbuff)&&(baddr<(fbuff+pbsize)))?1:0)

/* macros to access the frame buffer */
#define PIXADDR(xx,yy) (fbuff+(yy)*xpix+(xx))
#define PIXINC(dx,dy)  ((dy)*xpix+(dx))

/* fixed-point data types and macros */
typedef int FX;
typedef unsigned int UFX;
#define FX_FRACBITS 16  /* bits of fraction in FX format */
#define FX_0        0   /* zero in fixed-point format */
#define FLOAT_TO_FX(flt)  ((FX)((flt)*(1<<FX_FRACBITS)+0.5))

/* some important constants */
#define PI      3.1415926535897932384626433832795028841971693993751
#define SQRT_2  1.4142135623730950488016887242096980785696718753769

/* square-root function globals */
extern UFX*		sqrtfunc;
extern int		sqrtcells;
extern int		sqrtshift;
#define			SQRTFUNC(fxval)  (sqrtfunc[ (fxval) >> sqrtshift ])

/* AA globals */
extern float	line_r;  /* line radius */
extern float	pix_r;   /* pixel radius */
extern FX*		coverage;
extern int		covercells;
extern int		covershift;
extern FX**		SpotTable;
extern int		SpotTableSpan;


#define COVERAGE(fxval) (coverage[ (fxval) >> covershift ])


/* pixel increment values 
   -- assume PIXINC(dx,dy) is a macro such that:
   PIXADDR(x0,y0) + PIXINC(dx,dy) = PIXADDR(x0+dx,y0+dy)  */
extern int adj_pixinc[4]; 
extern int diag_pixinc[4]; 
extern int orth_pixinc[4]; 

#ifdef __cplusplus
extern "C" {
#endif

void					InitAAData( int XSize, int YSize );
void					FreeAAData();
unsigned char*		InitPixelBuffer( int XSize, int YSize );
void					FreePixelBuffer( unsigned char* pbuff );
void					Anti_Init ( float LineWidth, float SpotSize );
void					Anti_Line ( unsigned char* PixelBuffer, int X1, int Y1, int X2, int Y2 );
void					InitSpotTable();
void					FreeSpotTable();

#ifdef __cplusplus
}
#endif
