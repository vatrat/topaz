//
//		TabletPoint.h
//



class	TabletPoint
	{
	public:


										TabletPoint()
											{
											PointRawData = 0;
											PointTime = 0;
											PointPressure = 0;
											}

		unsigned long				PointRawData;
		unsigned long				PointTime;
		unsigned long				PointPressure;

	} ;
