//
//		CircularBuffer.h
//

#define					MaxBufferSize					32768


class	CircularBuffer
	{
	public:

		virtual					~CircularBuffer()
										{
										}


		virtual void			ResetBuffer() = 0;
		virtual void			AddToCircularBuffer( char* Buffer, int Count ) = 0;
		virtual void			PutInCircularBuffer( char Byte ) = 0;
		virtual char			GetFromCircularBuffer( ) = 0;
		virtual int				BytesInCircularBuffer( ) = 0;
		virtual int				WaitForCircularBuffer( ) = 0;
		virtual void			SetDataReady() = 0;
	} ;
