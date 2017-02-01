//
//		SocketIoIFWin.h
//




class NewSocketIoIFLinux: public NewSocketIoIF
	{
	public:

								NewSocketIoIFLinux( TabletInterface* TabIF );
								~NewSocketIoIFLinux();

	TabletInterface*		Tab;
	//	volatile HANDLE		UsbTab;
	//	volatile HANDLE		UsbEvent;
	volatile bool			UsbRunning;
	volatile bool			UsbKill;

	//	SOCKET					Socket;

	unsigned char			SynchronousXmitBuffer[ MaxSigSocketMessageSize ];
	volatile int			SynchronousXmitSize;
	volatile bool			SynchronousXmitDataReady;

	
	bool						InitTablet();
	bool						CloseTablet();
	bool						WriteTablet( unsigned char* Buffer, int Size );
	bool						InitSockets();
	} ;

