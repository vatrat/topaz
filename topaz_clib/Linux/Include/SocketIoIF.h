//
//		SocketIoIF.h
//




class SocketIoIF
	{
	public:

	virtual					~SocketIoIF()
									{
									}


	virtual bool			InitTablet() = 0;
	virtual bool			CloseTablet() = 0;
	virtual bool			WriteTablet( unsigned char* Buffer, int Size ) = 0;
	} ;

