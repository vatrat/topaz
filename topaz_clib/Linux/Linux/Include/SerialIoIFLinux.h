//
//		SerialIoIFLinux.h	
//

#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <termio.h>
#include <signal.h>
#include <time.h>
#include <pthread.h>

/* ----------------- COMMUNICATION --------------------- */

#define  PTERMIO struct termio *

#define  ALLOWEDTIME 3
#define  FATAL_ERROR 7
#define  OK          0
#define  NOK        -1
#define  FLUSH       0
#define  NOFLUSH     1


class SerialIoIFLinux : public SerialIoIF
	{
	public:
			SerialIoIFLinux( TabletInterface* TabIF );
			~SerialIoIFLinux();


	TabletInterface*	Tab;
	int			BaudRate;
	int			PortNumber;
	char			PortPath[ 128 ];
	PTERMIO			TTYOriginalConf;
	PTERMIO			TTYKeyCompatibleConf;
	int			ReadFD;
	int			WriteFD;
	pthread_t		ThreadID;

	bool			InitTablet();
	bool			CloseTablet();
	bool			WriteTablet( unsigned char* Buffer, int Size );
	void			SetPortNumber( int PortNumber );
	int			GetPortNumber( );
	void			SetBaudRate( int BaudRate );
	void			SetPortPath( char* Path );
	bool			TabletConnected();

	int			OpenTTY(char *);
	void			GetTTYConf(PTERMIO);
	void			SetTTYConf(PTERMIO,int,int);
	void			CloseTTY(void);
	bool			OpenSerialPort( );
	void			CloseSerialPort();
	} ;

