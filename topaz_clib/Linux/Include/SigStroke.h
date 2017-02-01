//
//		SigStroke.h
//

class SigStroke
	{
	public:

							SigStroke();
							~SigStroke();

		SigStroke*		NextStroke;
		SigPoint*		PointList;

		int				NumberOfPoints();
		void				AddPoint( int XValue, int YValue, unsigned long Time, unsigned long Pressure );
		SigPoint*		GetPoint( int Point );
	};
