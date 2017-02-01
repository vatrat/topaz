//
//		LCDGraphicBitmap.h
//

enum  LCDPixelDepth
						{
						LCD_1_Bit,
						LCD_2_Bit,
						LCD_4_Bit,
						LCD_8_Bit
						} ;



class SIGAPI LCDGraphicBitmap
	{
	public:
							LCDGraphicBitmap( short XPos, short YPos, short XSize, short YSize, LCDPixelDepth Depth = LCD_1_Bit, unsigned TextThreshold = 128 );
							LCDGraphicBitmap( short XPos, short YPos, char* FileName, LCDPixelDepth Depth = LCD_1_Bit, unsigned TextThreshold = 128 );
							~LCDGraphicBitmap();

	bool					Init( short XPos, short YPos, short XSize, short YSize, LCDPixelDepth Depth = LCD_1_Bit );
	void					SetPixel( short X, short Y, COLORREF V = 0x00000000 );
	
	
//	private:

	LCDPixelDepth		PixelDepth;

	void					SetPixel_1_Bit( short X, short Y, COLORREF V );
	void					SetPixel_2_Bit( short X, short Y, COLORREF V );
	void					SetPixel_4_Bit( short X, short Y, COLORREF V );
	void					SetPixel_8_Bit( short X, short Y, COLORREF V );


	unsigned char*		Buffer;
	long					BufferSize;
	long		 			BytesWide;
	unsigned 			XSizeNew;
	unsigned 			XPosNew;
	unsigned 			XOffset;

	int					RealXSize;
	int					RealYSize;

	short					TabXPos;
	short					TabYPos;
	short					TabXSize;
	short					TabYSize;

	unsigned				Threshold;

//	friend class LCDInterface;

	};
