//
//		ProcessSerialData.h
//



class ProcessSerialData
	{
	public:


		virtual					~ProcessSerialData()
										{
										}



		virtual void			StartSerialInputHandler() = 0;
		virtual void			StopSerialInputHandler() = 0;
		virtual void			ResetSerialInputHandler() = 0;
		virtual void			SyncSerialInputHandler() = 0;
		virtual void			ClearSerialInputHandler() = 0;
	};
