//
//		BitmapCharacter.h
//



class BitmapCharacter
	{
	public:

									BitmapCharacter();
									~BitmapCharacter();

		int						GetXSize();
		int						GetYSize();
		int						PixelValue( int X, int Y );

		int						CharCode;
		int						XSize;
		int						LineSize;
		int						YSize;
		int						DataSize;
		char*						Data;

	} ;

