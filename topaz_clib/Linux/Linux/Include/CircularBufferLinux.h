//
//		CircularBufferLinux.h
//
#include <pthread.h>

class	CircularBufferLinux : public CircularBuffer
	{
	public:

				CircularBufferLinux();
				~CircularBufferLinux();

		char		CircularBufferData[ MaxBufferSize ];
		volatile char*	CircularHead;
		volatile char*	CircularTail;

		pthread_cond_t	CircularDataReady;
		pthread_mutex_t	CircularDataReadyLock;
		pthread_mutex_t	CircularBufferLock;

		void		ResetBuffer();
		void		AddToCircularBuffer( char* Buffer, int Count );
		void		PutInCircularBuffer( char Byte );
		char		GetFromCircularBuffer( );
		int		BytesInCircularBuffer( );
		int		WaitForCircularBuffer( );
		void		SetDataReady();
	} ;
