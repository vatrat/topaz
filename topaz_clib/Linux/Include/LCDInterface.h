//
//		LCDInterface.h
//

const unsigned char		LCDDefaultCmd				= 0x04;
const unsigned char		LCDInkCmd					= 0x14;
const unsigned char		LCDInkInvertCmd			= 0x09;
const unsigned char		LCDKeyPadCmd				= 0x0B;
const unsigned char		LCDWriteDisplayCmd		= 0x07;
const unsigned char		LCDWriteHiddenCmd			= 0x17;
const unsigned char		LCDRefreshCmd				= 0x12;
const unsigned char     LCDQuietCmd             = 0x11;
const unsigned char		LCDWriteDisplayZCmd		= 0x1a;
const unsigned char		LCDWriteHiddenZCmd		= 0x19;
const unsigned char		LCDSetEncryptionModeCmd = 0x0D;
const unsigned char		LCDKeyExchangeCmd			= 0x05;

const short					LCDDestFore					= 0;
const short					LCDDestBack					= 1;



enum  LCDCaptureModes
						{
						LCDCapNone,
						LCDCapDefault,
						LCDCapInk,
						LCDCapInkInvert
						} ;

typedef	enum LCDCaptureModes	LCDCaptureModeType;

struct LCDWindowedCmdType
	{
	unsigned char			CmdCode;
	unsigned char        ModeByte;
	unsigned short       PosX;
	unsigned short			PosY;
	unsigned short			SizeX;
	unsigned short			SizeY;

	
	unsigned short			
	FixUpShort( unsigned short V )
								
		{
		unsigned short Rv;

		Rv = 0;
		Rv |= (V >> 8) & 0xFF;
		Rv |= (V & 0xFF) << 8;
		return Rv;
		}
	
	
	void
	FixUpCmd()
	
		{
		PosX = FixUpShort( PosX );
		PosY = FixUpShort( PosY );
		SizeX = FixUpShort( SizeX );
		SizeY = FixUpShort( SizeY );
		}
	
	} ;


class SIGAPI LCDInterface
	{
	public:


									LCDInterface( TabletInterface* TabIF );
									~LCDInterface();

		TabletInterface*		Tab;
		LCDCaptureModeType	LCDCaptureMode;
		LCDGraphicBitmap*		LCDBmp;


		LCDCaptureModeType	GetLCDCaptureMode();
		void						SetLCDCaptureMode( LCDCaptureModeType newMode ); 
		bool						LCDSetWindow(short XPos, short YPos, short XSize, short YSize);
		bool						LCDWriteString(short Dest, short Mode, short XPos, short YPos, CharacterMap* Font, unsigned char* Str);
		int						LCDStringWidth( CharacterMap* Font, unsigned char* Str );
		int						LCDStringHeight( CharacterMap* Font, unsigned char* Str );

		bool						LCDRefresh(short Mode, short XPos, short YPos, short XSize, short YSize);
		int						LCDSendCmdString( char* CmdString, short ReturnCount, char* Result, long TimeOut );
		void						LCDSetupTablet();
		bool						LCDSendCommand( LCDWindowedCmdType* Cmd, int DataSize );
		bool						LCDWaitForCommandResponse( unsigned char CSum, int Timeout );

		bool						LCDSendGraphic( short Dest, short Mode, LCDGraphicBitmap* BitmapData );
		
		bool						LCDAllocateGraphic( short XPos, short YPos, short XSize, short YSize );
		bool						LCDSendGraphic( short Dest, short Mode );
		void						LCDFreeGraphic();
		void						LCDSetPixel( short XPos, short YPos, COLORREF PixVal );

		long						GetLCDSize();
		long						GetLCDStringSize( char* Str );
		void						LCDClear();
		unsigned char*			CompressLCDGraphics( bool ZComp, int CompressionFactor, unsigned char* BitmapData, unsigned Size, unsigned* CompDataSize );
		unsigned					CompressLCDData( int CompressionFactor, unsigned char* RawData, unsigned RawSize, unsigned char* CompData );
		unsigned char*			EncryptLCDData(  unsigned char* RawData, unsigned RawSize, int* CryptSize  );
	};
