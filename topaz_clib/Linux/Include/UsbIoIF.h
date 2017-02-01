//
//		UsbIoIF.h
//




class UsbIoIF
	{
	public:

	virtual					~UsbIoIF()
									{
									}


	virtual bool			InitTablet() = 0;
	virtual bool			CloseTablet() = 0;
	} ;

