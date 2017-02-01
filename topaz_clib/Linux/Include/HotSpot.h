//
//		HotSpot.h
//


class	HotSpot
	{
	public:

							HotSpot()
								{
								Spot.XPos = 0;
								Spot.YPos = 0;
								Spot.XSize = 0;
								Spot.YSize = 0;
								Code = -1;
								NextHotSpot = NULL;
								}

							HotSpot( int NewCode, int NewXPos, int NewYPos, int NewXSize, int NewYSize )
								{
								Spot.XPos = NewXPos;
								Spot.YPos = NewYPos;
								Spot.XSize = NewXSize;
								Spot.YSize = NewYSize;
								Code = NewCode;
								NextHotSpot = NULL;
								}

							~HotSpot()
								{
								}


		SigWindowType	Spot;
		int				Code;
		HotSpot*			NextHotSpot;


		bool				PointInSpot( long X, long Y )
								{
								return Spot.PtInRect( X, Y );
								}

	};


