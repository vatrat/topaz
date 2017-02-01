//
//		TiffImage.h
//
//


struct TiffTag
	{
							TiffTag( unsigned char* RawData, bool Swap );

	unsigned short		Tag;
	unsigned short		Type;
	unsigned long		Count;
	unsigned long		Data;
	};


class TiffImage
	{
	public:

									TiffImage();
									TiffImage( char* TiffFileName );
									~TiffImage();


		long						XSize;
		long						YSize;
#ifdef	UseOldTiffCode
		unsigned char*			ImageData;
#else
		unsigned int*			ImageData;
#endif

		FILE*						TiffFile;
		bool						UnsupportedFormat;
		bool						Swap;
		short						FillOrder;
		short						BitsPerSample;
		long						NumStrips;
		long						RowsPerStrip;
		long						StripByteCountsOffset;
		int						StripByteCountsSize;
		long						StripByteOffsetsOffset;
		int						StripByteOffsetsSize;
		long*						StripByteCounts;
		long*						StripByteOffsets;

		bool						LoadImage( char* TiffFileName );
#ifdef	UseOldTiffCode
		unsigned char			GetPixel( int X, int Y );
#else
		unsigned int			GetPixel( int X, int Y );
#endif
		void						ReadTags( unsigned long Offset );
		short						ReadShort( unsigned long Offset );
		int						ReadInt( unsigned long Offset );
		long						ReadLong( unsigned long Offset );
		void						ReadStrip( int StripNumber );
		void						ReadStripByteCounts();
		void						ReadStripByteOffsets();
	};

