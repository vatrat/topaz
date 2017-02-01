//
//		HotSpotList.h
//



class SIGAPI HotSpotList
	{
	public:

								HotSpotList();
								~HotSpotList();


		HotSpot*				Head;

		void					AddHotSpot(short KeyCode, short XPos, short YPos, short XSize, short YSize); 
		void					ClearHotSpotList();
		HotSpot*				FindHotSpot( int KeyCode );
		int					FindHotSpot( TabletSample* Pnt  );

	} ;
