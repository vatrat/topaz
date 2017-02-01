//
//		SimIoIF.h
//


struct SimDataPacket
	{
	unsigned char			XMsb;
	unsigned char			XLsb;
	unsigned char			YMsb;
	unsigned char			YLsb;
	unsigned char			PMsb;
	unsigned char			PLsb;
	unsigned char			Status;
	unsigned char			CSum;
	} ;

#define		Status_PenA			0x00
#define		Status_PenB			0x02
#define		Status_SN			0x04
#define		Status_Cmd			0x06
#define		Status_PenC			0x08
#define		Status_Spare0		0x0A
#define		Status_Spare1		0x0B
#define		Status_Spare2		0x0C

#define		Status_Mask			0x0F

#define		Pen_Down				0x80
#define		Pen_Near				0x40
#define		Pen_Barrel			0x20
#define		Pen_Spare			0x10

#define		Pen_Mask				0xF0

class SimIoIF
	{
	public:

	virtual					~SimIoIF()
									{
									}


	virtual bool			InitTablet() = 0;
	virtual bool			CloseTablet() = 0;
	virtual bool			WriteTablet( unsigned char* Buffer, int Size ) = 0;
	virtual void			WriteSimLEDCommand( bool Value ) = 0;
	virtual bool			IsSimTabletConn() = 0;
	} ;

