/*
#include <wtypes.h>
#include <initguid.h>

#define MAX_LOADSTRING 256

extern "C" {
#include "hidsdi.h"
#include <setupapi.h>
}

#include <winsock.h>
#include <mmsystem.h>
*/

extern "C" {

#include "polarssl/aes.h"
#include "polarssl/dhm.h"
#include "polarssl/havege.h"
#include "polarssl/sha2.h"

}




void						InitLogFile( TabletParameters* TabletParams );
void						CloseLogFile();


#define					GET_DATA_TIMED_OUT	0xFFFFFFFF

#define					SigPlusIniFile					"SigPlus.ini"

#define					DefaultTabletX1				500
#define					DefaultTabletY1				350
#define					DefaultTabletX2				2650
#define					DefaultTabletY2				2100

#define					DefaultTabletLogicalXSize	2150
#define					DefaultTabletLogicalYSize	1400

#define					DefaultTabletResolution		410





#define					MaxMessageSize					32768

const unsigned char	StatusSerialNoData			= 0x02;
const unsigned char	StatusCmdData					= 0x03;

#define					UsbDown							0x08
#define					UsbNear							0x04

#define					UsbStatusDataMask				0x60

enum	TabletType	{ 
						SerialTabletType,						// 0
						WinTabTabletType,						// 1
						UsbTabletType,							// 2
						TransSerialTabletType,				// 3
 						SigLiteTabletType,					// 4
						SocketTabletType,						// 5
						HidSerialTabletType,					// 6
						NewSocketTabletType,					// 7
						SimTabletType                    // 8
	               };

enum SerialState
						{
						WaitForStartByte,
						WaitForSecondByte,
						WaitForRestOfPacket
						} ;




class	TabletInterface;
#include <stdio.h>
#include <stdlib.h>


class	SIGAPI TabletInterface
	{
	public:
//
//		Top level interface from dll to class
//

									TabletInterface();
									~TabletInterface();

		TabletParameters		TabletParams;

		bool						TabletOpen;
		FILE*						LogFile;

		CircularBuffer*		CircBuff;
		PointBuffer*			PointBuff;
		PointBuffer*			NonPointBuff;
		SerialIoIF*				SerialIF;
		HidIoIF*					HidIF;
		UsbIoIF*					UsbIF;
		SocketIoIF*				SockIF;
		NewSocketIoIF*			NewSockIF;
		SimIoIF*             SimIF;
		ProcessSerialData*	ProcIF;

		unsigned long			SerialNumber;
		unsigned long			ModelNumber;
		unsigned long			CurrentPressure;


//
//		Serial and SerialHID thread support stuff
//
		
		volatile enum SerialState	SerialInputState;
		volatile bool			KillProcessInputData;
		volatile bool			SerialStateReset;
		volatile bool			ProcessInputDataRunning;


		bool						EncryptHostData;
		bool						EncryptTabletData;
		dhm_context				dhm;

		aes_context				AesEnc;
		aes_context				AesDec;
		unsigned char			KeyBuff[ 128 ];

		bool						OpenTablet();
		bool						OpenTabletRaw();
		bool						CloseTablet();
		bool						CloseTabletRaw();
		
		unsigned long			GetTabletData( unsigned long TimeOutInMs );
		unsigned long			GetTabletPointData( unsigned long TimeOutInMs );
		bool						GetTabletPointData( TabletPoint* Data, unsigned long TimeOutInMs );
		bool						PutTabletData(  unsigned char* Buffer, int Count );
		bool						WriteTabletData( unsigned char* Buffer, int Count );
		bool						WaitForCommandResponse( unsigned char CSum, int Timeout );
	
		int						TabletDataReady();
		bool						TabletPresent();

		void						ProcessInputData( ProcessSerialData* ProcIF );
		void						SendSerialNPData( unsigned char StatusByte, int XPos, int YPos );
		void						ProcessNonPointData( unsigned char StatusByte, unsigned char* DataBytes );
		bool						WaitForNonPointCmdData( unsigned long TimeOut, int ReturnCount );
		bool						CheckTabletConnected();

		unsigned long			GetSerialNumber();
		unsigned long			GetModelNumber();

//
//		TabletCore.cpp
//
		TabletType				GetTabletIfType();
		void						ScaleCoordData( int* XPos, int* YPos );
		void						PutInPointBuffer( unsigned long Point );
		unsigned long			GetFromPointBuffer( );
		int						PointsInPointBuffer( );

//
//		TabletParameters.cpp
//
		void						InitTabletParams();
		void						GetTabletParameters( TabletParameters* Params );
		void						SetTabletParameters( TabletParameters* Params );
		void						LoadDefaultParameters();
		void						LoadIniParameters();
//
//		Serial and HIDSerial support code
//
		bool						IsStartByte( unsigned char Byte );
		int						ConvertCoordData( unsigned char Lsb, unsigned char Msb );
		int						ConvertPressureData( unsigned char Lsb, unsigned char Msb );
		bool						IsBadPacket( unsigned char* Buffer );
		bool						IsSerialPenData( unsigned char Status );
		bool						IsSerialPressureData( unsigned char Status );
		void						InitProcessInputData();
		void						CloseProcessInputData();
		void						ResetSerialInputState( );
		unsigned long			MakeLongPoint( unsigned char StatusByte, int XPos, int YPos );
		unsigned long			MakeLongCmd( unsigned char Cmd );
		void						SetPenDown( unsigned char* Status );
		void						SetPenNear( unsigned char* Status );
		bool						EnableTabletEncryption();
		void						SetTabletEncryptionModes( bool HostMode, bool TabletMode );
		void						AddToCircularBuffer( unsigned char* Data, int Count );


	};

