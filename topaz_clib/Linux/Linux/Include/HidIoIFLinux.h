//
//		HidIoIFLinux.h
//




class HidIoIFLinux : public HidIoIF
	{
	public:
				HidIoIFLinux( TabletInterface* TabIF );
				~HidIoIFLinux();


	TabletInterface*	Tab;
	pthread_t			ThreadID;
	pthread_t			ReadThreadID;
        volatile bool                    KillThread;
        volatile bool                    KillReadThread;

	int					ReadFile;
	int					WriteFile;
	int					HSBPacketSize;
        int                             ThreadCount;


	bool			InitTablet();
	bool			CloseTablet();
	bool			WriteTablet( unsigned char* Buffer, int Size );
	void			WriteHidLEDCommand( bool TrueForOn );
	bool			IsHidTabletConn();
	} ;


