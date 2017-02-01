//
//		SigLib.h
//
//
//		Top level master include for SigLib
//
extern const char*		SigLibVersionString;


#ifdef	WIN32

#define	Windows32

#ifdef	SIGLIBDLL
#define	SIGAPI	__declspec( dllexport ) 
#else
#define SIGAPI
#endif

#elif	WIN64


#define	Windows32

#ifdef	SIGLIBDLL
#define	SIGAPI	__declspec( dllexport ) 
#else
#define SIGAPI
#endif

#else

#define	SIGAPI

#endif


#ifdef	_WIN32_WCE
#define	WindowsCE
#define	NeedPrivateProfileFunctions
#endif

#ifdef	Linux
#define	NeedPrivateProfileFunctions
#endif

#ifdef	MacOSX
#define	NeedPrivateProfileFunctions
#endif

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <ctype.h>


#ifndef	WindowsCE

#ifdef	_MOBILE_SDK_6
#define	WindowsCE
#define	NeedPrivateProfileFunctions

#include <windows.h>
#include <strsafe.h>

#include <types.h>
//#include <stat.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
#endif

#endif

#ifdef	Linux
#include	<unistd.h>
#endif

#ifdef	MacOSX
#include	<sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

typedef unsigned long COLORREF;

#include "AALines.h"

#include "SigClasses.h"

