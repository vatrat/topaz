//
//		TabletSampleList.h
//

#define	MaxSamplesToSave	16




class	SIGAPI TabletSample
	{
	public:
	
		TabletSample( int x, int y, int Stat, int Time, int Pressure )
		   {
			X = x;
			Y = y;
			Status = Stat;
			TimeValue = Time;
			PressureValue = Pressure;
			}
	 
		TabletSample( )
			 {
			X = 0;
			Y = 0;
			Status = 0;
			TimeValue = 0;
			PressureValue = 0;
			}

		int				X;
		int				Y;
		int    			Status;
		unsigned long	TimeValue;
		unsigned long	PressureValue;
	} ;





class SIGAPI TabletSampleList
	{
	public:
									TabletSampleList();
									~TabletSampleList();

		TabletSample*			List[ MaxSamplesToSave ];
		int						Head;
		int						Tail;

		TabletSample*			RemoveHead();
		void						AddTail( TabletSample* Sample );
		int						GetCount();
		void						DumpAt( int Index );

	};
