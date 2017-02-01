//
//		UsbIoIFLinux.h
//




class UsbIoIFLinux : public UsbIoIF
	{
	public:

				UsbIoIFLinux( TabletInterface* TabIF );
				~UsbIoIFLinux();


	TabletInterface*	Tab;
	pthread_t		ThreadID;
	struct usb_dev_handle*	udev;

	bool			InitTablet();
	bool			CloseTablet();
	bool			OpenUsbTablet();
	} ;


