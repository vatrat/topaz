#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SigLib.h>


static Signature*				Sig;
static TabletParameters		Params;
static TabletInterface*		Tablet;


static bool				Init( void );
static void				Close( void );





int
main( int ArgC, char** ArgV )
	{
	int		Total;
	char		Msg[ 256 ];

	

	while ( true )
		{
                printf( "Before Init\n" );
		if ( Init() == false )
			{
			LogMessage( "Tablet failed to open" );
			SigSleep( 1000 );
			continue;
			}
		LogMessage( "Tablet opened ok" );
		Sig->ClearSignature();
		SigSleep( 30000 );
		if ( ( Total = Sig->TotalPoints() ) != 0 )
			{
			sprintf( Msg, "Tablet captured %d points", Total );
			LogMessage( Msg );
			printf( "Success\n" );
			}
		else
			{
			LogMessage( "Tablet failed to get points, FAILURE" );
			printf( "FAILURE\n" );
			}
		Close();
		}
	return 0;
	}



static bool
Init( void )

	{
	Tablet = new TabletInterface();
	Sig = new Signature( Tablet );
	
        printf( "Before GetTabletParams\n" );
	Tablet->GetTabletParameters( &Params );
	printf( "Before changing params\n" );
        Params.EnableLogging = 1;
	Params.TestIfConnected = true;
	printf( "Before Setting params\n" );
	Tablet->SetTabletParameters( &Params );

	printf( "Before starting capture\n" );
        Sig->StartCapture( Tablet );

	printf( "Before OpenTablet\n" );
        if ( Tablet->OpenTablet() == false )
		{
		Sig->StopCapture();
		return false;
		}

	printf( "At end of Init\n" );
	return true;
	}


static void
Close()
	{
      printf( "Before Stop capture\n" );
        Sig->StopCapture();
	printf( "Before CloseTablet\n" );
        Tablet->CloseTablet();
      printf( "After close tablet\n" );

	delete Sig;
	delete Tablet;
	}







