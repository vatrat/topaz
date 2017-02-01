//
//		CaptureSigLinux.h
//

#include <pthread.h>

class CaptureSigLinux : public CaptureSig
	{
	public:

				CaptureSigLinux( Signature* Sig );
				~CaptureSigLinux();

		pthread_t	ThreadID;
		pthread_mutex_t	PenStateLock;
		Signature*	Sig;

		bool		StartCapture();
		bool		StopCapture();
		void		GrabPenStateLock();
		void		ReleasePenStateLock();
	} ;
