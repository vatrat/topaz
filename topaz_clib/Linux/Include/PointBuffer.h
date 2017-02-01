//
//		PointBuffer.h
//

#define					MaxPointBufferSize			5000


class	PointBuffer
	{
	public:


										PointBuffer()
											{
											}
										~PointBuffer()
											{
											}

		TabletPoint					PointBufferData[ MaxPointBufferSize ];
		volatile TabletPoint*	PointBufferHead;
		volatile TabletPoint*	PointBufferTail;

		void							ResetBuffer();
		void							PutInPointBuffer( unsigned long Point );
		void							PutTabletPointInBuffer( unsigned long PRawData, unsigned long PTime, unsigned long PPressure );
		unsigned long				GetFromPointBuffer( );
		bool							GetTabletPointFromBuffer( TabletPoint* TPoint );
		int							PointsInPointBuffer( );
	} ;
