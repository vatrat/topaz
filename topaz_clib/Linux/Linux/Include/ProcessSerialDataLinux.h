//
//		ProcessSerialDataLinux.h
//



class ProcessSerialDataLinux : public ProcessSerialData
	{
	public:
			ProcessSerialDataLinux( TabletInterface* TabPtr );
			~ProcessSerialDataLinux();

		TabletInterface*		Tab;
		pthread_mutex_t			ResetSerialLock;
		pthread_t			ThreadID;

		void				StartSerialInputHandler();
		void				StopSerialInputHandler();
		void				ResetSerialInputHandler();
		void				SyncSerialInputHandler();
		void				ClearSerialInputHandler();
	};
