//
//		Include file for Class interface to SigTablt library
//

SIGAPI void						LogMessage( const char* Msg );
SIGAPI void						LogBinaryData( const char* Msg, unsigned char* Data, int Size );

#include "SigPoint.h"
#include "SigStroke.h"
#include "TabletParameters.h"
#include "CircularBuffer.h"
#include "SerialIoIF.h"
#include "HidIoIF.h"
#include "UsbIoIF.h"
#include "SocketIoIF.h"
#include "NewSocketIoIF.h"
#include "SimIoIF.h"
#include "ProcessSerialData.h"
#include "CaptureSig.h"
#include "TabletPoint.h"
#include "PointBuffer.h"
#include "TabletInterface.h"
#include "TabletSampleList.h"
#include "SigWindowType.h"
#include "SigFile.h"
#include "md5.h"
#include "Utilities.h"
#include "HotSpot.h"
#include "HotSpotList.h"
#include	"BitmapCharacter.h"
#include "CharacterMap.h"
#include "TiffImage.h"
#include "LCDGraphicBitmap.h"
#include "LCDInterface.h"

#include "Signature.h"


