//
//		CaptureSig.h
//

class CaptureSig
	{
	public:

		virtual						~CaptureSig()
											{
											}


		virtual bool				StartCapture() = 0;
		virtual bool				StopCapture() = 0;
		virtual void				GrabPenStateLock() = 0;
		virtual void				ReleasePenStateLock() = 0;
	} ;
