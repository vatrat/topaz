/*
 *	SigSock.h
 */


#define	SigSocketPort				47289

#define	MaxSigSocketMessageSize	0x8000

#define	SigSocketBufferSize		MaxSigSocketMessageSize + sizeof( long )

#define	SigSockTabletData			0
#define	SigSockLCDStream			1
#define	SigSockConnect				2


struct SigSocketData
	{
	long					Type;
	long					DataSize;
	unsigned char		Data[ 4 ];
	} ;

