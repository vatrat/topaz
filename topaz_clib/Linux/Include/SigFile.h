//
//		SigFile.h
//

#define		FileSizeIncrement		1024

class SIGAPI SigFile
	{
	public:


									SigFile();
									~SigFile();


		int						CurrPos;
		int						FileError;
		int						BytesInBuffer;
		int						BufferSize;
		unsigned char*			Buffer;

		bool						LoadFromDisk( char* FileName );
		bool						SaveToDisk( char* FileName );
		void						SeekToBegin();
		void						SeekRelative( int Offset );
		int						Write( unsigned char* Buf, int Num );
		int						Read( unsigned char* Buf, int Num );
		int						Write( char* Buf, int Num );
		int						Read( char* Buf, int Num );
		bool						ReAllocBuffer();
		int						GetLength();
	};
