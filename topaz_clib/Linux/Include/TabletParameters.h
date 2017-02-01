//
//		TabletParameters.h
//
//
//		TabletMode bits
//
#define			TabletTypeMask					0x000F
#define			TestTabletCommMask			0x0080
#define			TabletInvisibleMask			0x0040
#define			TabletMappingMask				0x0020
#define			TabletClippingMask			0x0010
#define			TabletDisplayRotateMask		0x0100
#define			TabletSaveRotateMask			0x0200
#define			TabletAsciiModeMask        0x0400


struct SIGAPI TabletParameters
	{
							TabletParameters()
								{
								ParameterVersion = 0;
								LocalIniFilePath[ 0 ] = '\0';
								IniFile[ 0 ] = '\0';
								}
	
	short					ParameterVersion;
	short					PortNumber;
	long					BaudRate;
	short					TabletMode;
	short					TabletX1;
	short					TabletY1;
	short					TabletX2;
	short					TabletY2;
	short					TabletLogicalXSize;
	short					TabletLogicalYSize;
	long					TabletResolution;
	int					TabletRotation;
	int					UsbMode;
	bool					UseMultiUsb;
	bool					EnableLogging;
	bool					TestIfConnected;
	unsigned long		TabletIpAddress;
	int					SamplesToSave;
	int					NumFilterPoints;

	short					LCDType;
	short					LCDXSize;
	short					LCDYSize;
	short					LCDXStart;
	short					LCDYStart;
	short					LCDXStop;
	short					LCDYStop;
	long					LCDWriteDelay;
	unsigned int		LCDRetryCount;
	bool					LCDCompressMode;
	int					LCDFastCompressionFactor;
	int					LCDSlowCompressionFactor;
	bool					LCDZCompression;
	bool					TranslateBitmapEnable;
	long					SocketTimeout;
	unsigned				TextThreshold;
	unsigned				SigSockPort;

	char					TabletPortPath[ 128 ];
	char              LocalIniFilePath[ 256 ];
	char					IniFile[ 256 ];

	} ;

