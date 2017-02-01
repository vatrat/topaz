//
//		SerialIoIF.h
//



class SerialIoIF
	{
	public:

	virtual					~SerialIoIF()
									{
									}


	virtual bool			InitTablet() = 0;
	virtual bool			CloseTablet() = 0;
	virtual bool			WriteTablet( unsigned char* Buffer, int Size ) = 0;
	virtual void			SetPortNumber( int PortNumber ) = 0;
	virtual int				GetPortNumber( ) = 0;
	virtual void			SetBaudRate( int BaudRate ) = 0;
	virtual bool			TabletConnected() = 0;
	virtual void			SetPortPath( char* Path ) = 0;
	} ;

