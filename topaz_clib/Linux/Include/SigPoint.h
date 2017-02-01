//
//		SigPoint.h
//
//



class SIGAPI SigPoint
	{
	public:

						SigPoint();
						SigPoint( int XValue, int YValue, unsigned long Time, unsigned long Pressure );
						~SigPoint();


		int			X;
		int			Y;
		long			TimeValue;
		long			PressureValue;
		SigPoint*	NextPoint;
	} ;

