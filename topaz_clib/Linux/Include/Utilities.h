//
//		Utilities.h
//


SIGAPI unsigned long		GetTimeInMS();
SIGAPI void					SigSleep( unsigned long TimeInMS );
SIGAPI int					SigGetPrivateProfileInt( const char* Section, const char* Item, int Default, const char* IniFileName );
SIGAPI void					SigGetPrivateProfileString( const char* Section, const char* Item, const char* Default, char* Dest, int DestSize, const char* IniFileName );
SIGAPI short				ByteSwapShort( short Value );
SIGAPI int					ByteSwapInt( int Value );
SIGAPI long					ByteSwapLong( long Value );
SIGAPI long					GetThreadId( void );
