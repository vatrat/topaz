//
//		SigWindowType.h
//


class SIGAPI SigWindowType
	{
	public:
							SigWindowType( );
							SigWindowType( int NewXPos, int NewYPos, int NewXSize, int NewYSize );
							~SigWindowType();

		int				XPos;
		int				YPos;
		int				XSize;
		int				YSize;
	
	
		bool				PtInRect( int XValue, int YValue );
		int				Width();
		int				Height();

	} ;




