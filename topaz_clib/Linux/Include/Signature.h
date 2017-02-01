//
//		Signature.h
//

#define			MaxSigKeySize					64
#define			Md5HashSize						16
#define			SHA2HashSize					32

#define			TopazDataTag					0xFFFF
#define			TopazPressureTag				0
#define			TopazTimeTag					1

#define			TopazEncryptionTag			0xFFFFFFFF

#define			MaxPointsPerStroke			32000

enum	JustifyModes
						{ 
						NoJustify, 
						JustifyUpperLeft, 
						JustifyUpperRight, 
						JustifyLowerRight, 
						JustifyLowerLeft,
						AutoJustify,
						JustifyUpperLeftScale,
						JustifyUpperRightScale, 
						JustifyLowerRightScale, 
						JustifyLowerLeftScale,
						NoJustifyScale
						} ;


enum	PenStates	{ 
						WaitingForNear, 
						NearWaitingForPenDown,
						PenDownState, 
						PenUpState 
						} ;


enum	EncryptionModes
						{
						None,
						Des40,
						Safer40,
						Safer40W,
						Des40SHA2
						} ;
	 

enum	ImageFileFormats
						{
						ImageBmpComp,							//	0
						ImageBmp,								//	1
						ImageBmpMono,							//	2
						ImageJpeg20,							// 3
						ImageJpeg100,							// 4
						ImageTiffOld,							//	5
						ImageTiffNew,							//	6
						ImageWmf,								//	7
						ImageEmf,								//	8
						ImageTiffOneBit,						// 9
						ImageTiffOneBitInvert				// 10
						} ;


class SIGAPI Signature
	{
	public:

										Signature();
										Signature( TabletInterface* Tablet );
										~Signature();

		
		CaptureSig*					CaptureIF;
		SigStroke*					StrokeList;
		bool							KillCapture;
		bool							CaptureActive;
		TabletInterface*			CurrentTablet;
		
		volatile enum PenStates	PenState;
		TabletSampleList			SavedSamples;
		short							SamplesToSave;
		TabletSample				LastSample;
		SigWindowType				SigWindow;
		int							MaxPointDelta;
		int							BadPointCounter;
		
		TabletSample				Filter[ 16 ];
		int							NumFilterPoints;
		int							NextPoint;

		char							TimeStamp[ 512 ];
		SigPoint						DisplayTimeStampPos;
		short							DisplayTimeStampSize;
		bool							DisplayTimeStamp;
		SigPoint						ImageTimeStampPos;
		short							ImageTimeStampSize;
		bool							ImageTimeStamp;

		int							CompressionMode;
	private:
		EncryptionModes			EncryptionMode;
	public:

		char							Annotate[ 512 ];
		SigPoint						DisplayAnnotatePos;
		short							DisplayAnnotateSize;
		bool							DisplayAnnotate;
		SigPoint						ImageAnnotatePos;
		short							ImageAnnotateSize;
		bool							ImageAnnotate;

		bool							SaveSigInfo;
		bool							SavePressureData;
		bool							SaveTimeData;

		unsigned char				SigKeyData[ MaxSigKeySize ];
		short							SigKeyDataLen;

		unsigned char				AutoKeyHash[ Md5HashSize ];
		xMD5Context					AutoKeyContext;
		bool							AutoKeyStarted;


		HotSpotList					HotSpots;
		SigStroke*					HotSpotPoints;

		short							JustifyX;
		short							JustifyY;
		JustifyModes				JustifyMode;
		long							AutoJustifyGain;
		long							AutoJustifyX0;
		long							AutoJustifyY0;
		long							AutoJustifyXOff;
		long							AutoJustifyYOff;

		unsigned char*				ImageDrawBuff;
		int							ImageDrawBuffXSize;
		int							ImageDrawBuffYSize;
		enum ImageFileFormats	ImageFileFormat;
		long							ImageXResolution;
		long							ImageYResolution;

		float							AntiAliasLineScale;
		float							AntiAliasSpotSize;
	
		int							SpecialPenEvent;
		volatile unsigned int	LastXPos;
		volatile unsigned int	LastYPos;
		volatile unsigned int	LastStatus;

		int							LastHotSpotIndex;
		bool							DebounceHotSpotEnable;

		void							CaptureThread();

		void							NewStroke();
		void							AddPointToStroke( int XValue, int YValue, unsigned long Time, unsigned long Pressure );

		int							NumberOfStrokes();
		int							NumberOfPointsInStroke( int Stroke );
		int							TotalPoints();
		
		int							GetPointXValue( int StrokeIdx, int PointIdx );
		int							GetPointYValue( int StrokeIdx, int PointIdx );
		int							GetPointPValue( int StrokeIdx, int PointIdx );
		int							GetPointTValue( int StrokeIdx, int PointIdx );

		bool							IsValidPoint( short StrokeNumber, short PointNumber );
		SigPoint						GetPointForStroke( short StrokeNumber, short PointNumber );
		void							ClearSignature();
		void							ClearHotSpotPoints();

		bool							StartCapture( TabletInterface* Tablet );
		void							StopCapture();
		void							ProcessTabletSample( int XPos, int YPos, int Status,  unsigned long Time, unsigned long Pressure );
		bool							IsPenNear( int Status );
		bool							IsPenDown( int Status );
		bool							SamplesAreDifferent( TabletSample* A, TabletSample* B );
		bool							OnPenDown( TabletSample* Sample );
		void							OnPenUp( TabletSample* Sample );
		void							OnPenMove( TabletSample* Sample );
		void							InitializeFilter( TabletSample* Sample );
		void							FilterPoint( TabletSample* Sample );
		void							SetSigWindow( short Coords, short NewXPos, short NewYPos, short NewXSize, short NewYSize );
		void							ClearSigWindow( short Inside );  
		TabletSample				FindWindowIntersect( TabletSample* FromSample, TabletSample* ToSample );
		bool							FindLineIntercept( int* LineY, int LineX, int X1, int X2, int Y1, int Y2 );

		bool							ExportSigFile( char* FileName ); 
		bool							WriteSigFile( SigFile& DestFile );
		bool							ExportSigFileComp0( SigFile& DestFile ); 
		bool							ExportSigFileComp2( SigFile& DestFile ); 
		bool							ImportSigFile( char* FileName ); 
		bool							ReadSigFile( SigFile& SourceFile ); 
		bool							ImportSigFileComp0( SigFile& SourceFile );
		bool							ImportSigFileComp2( SigFile& SourceFile ); 
		void							LoadSigInfoBinary( SigFile& SourceFile );
		void							LoadAnnotationString( SigFile& SourceFile, char* Buffer, int Length );
		void							LoadPressureDataFromFile( SigFile& SourceFile );
		void							LoadTimeDataFromFile( SigFile& SourceFile );
		void							SaveSigInfoBinary( SigFile& DestFile );
		void							SavePressureDataToFile( SigFile& DestFile, int* PData, int NumPoints );
		void							SaveTimeDataToFile( SigFile& DestFile, int* PData, int NumPoints );
		void							FileReadError( char* ErrMsg );
		int							GetTextNextInteger( SigFile& Source );
		void							InitSigInfo( void );
		bool							SetSigString( char* SigString );
		char*							GetSigString( );

		bool							EnCryptFile( SigFile* FromFile, SigFile* ToFile );
		bool							DeCryptFile( SigFile* FromFile, SigFile* ToFile );
		void							SetKey( unsigned char* KeyData, int Length );
		void							GetKey( unsigned char* KeyData, int Length ); 
		void							GetKeyString( char* Result, int Length ); 
		void							SetKeyString( char* KeyString ); 
		void							SetAutoKeyData( unsigned char* NewValue ); 
		void							AutoKeyStart(); 
		void							AutoKeyAddData( unsigned char* Buffer, int Len ); 
		void							AutoKeyFromFile( const char* FileName ); 
		void							AutoKeyFinish(); 
		long							GetKeyReceipt(); 
		void							GetKeyReceiptAscii( char* Result ); 
		long							GetSigReceipt(); 
		void							GetSigReceiptAscii( char* Result); 
		void							Make40BitKey( unsigned char *Src, unsigned char *Dst );
		void							SetEncryptionMode( EncryptionModes Mode );
		EncryptionModes			GetEncryptionMode( void );
		bool							ChangeKeyAllowed( void );
		bool							ChangeDataAllowed( void );
		char							ToAsciiHex( int V );
		int							FromAsciiHex( char Ch );
		void							LogKeyData( char* Label );

		void							KeyPadAddHotSpot(short KeyCode, short CoordToUse, short XPos, short YPos, short XSize, short YSize); 
		short							KeyPadQueryHotSpot(short KeyCode); 
		void							KeyPadClearHotSpotList(); 
		short							KeyPadConvertToLogical( short LCDPos, short LCDSize, short LCDStart, short LCDStop );
		short							KeyPadConvertFromLogical( short LogPos, short LCDSize, short LCDStart, short LCDStop );
		short							KeyPadGetLastXPos( );
		short							KeyPadGetLastYPos();

		bool							DrawSignature( int DrawJustifyX, int DrawJustifyY, int Width, int Height, JustifyModes DrawMode, int PenWidth );
		bool							DrawSignature( int PenWidth );
		void							ScalePoint( SigWindowType* Source, SigWindowType* Dest, SigPoint& P );
		void							InitAutoJustify( SigWindowType* Source, SigWindowType* Dest );
		int							FindMean( int* Hist, int TotalPoints );
		int							FindMedian( int* Hist, int TotalPoints );
		int							FindMode( int* Hist );
		void							DumpHistogramData( int* Hist, int TotalPoints );
		int							ScalePenWidth(  SigWindowType* DRect, int RawWidth );
		void							DumpImage( char* FileName );

		void							DrawSignatureAntiAlias(  SigWindowType* TRect, SigWindowType* DRect, int PenWidth );
		bool							WriteImageFile( char* FileName );
		bool							WriteImageFile( ImageFileFormats Format, char* FileName );
		void							InitSignature();

	} ;
