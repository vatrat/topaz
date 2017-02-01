//
//		HidIoIF.h
//



class HidIoIF
	{
	public:

	virtual					~HidIoIF()
									{
									}


	int						HidReportSize;

	virtual bool			InitTablet() = 0;
	virtual bool			CloseTablet() = 0;
	virtual bool			WriteTablet( unsigned char* Buffer, int Size ) = 0;
	virtual void			WriteHidLEDCommand( bool Value ) = 0;
	virtual bool			IsHidTabletConn() = 0;
	} ;

