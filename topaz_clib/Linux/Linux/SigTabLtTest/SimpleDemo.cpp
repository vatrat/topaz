#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SigLib.h>



static Signature*				Sig;
static TabletParameters		Params;
static TabletInterface*		Tablet;


static bool				Init( void );
static void				Close( void );


static int				TestTabletType( TabletInterface* Tab );
static void				ProcessInput( void );



void
SimpleDemo(  )
	{
	int		TabPresent;

	Sig = new Signature();
	Tablet = new TabletInterface();
	
	TabPresent = TestTabletType( Tablet );

	if ( Init() == false )
		{
		return;
		}

	printf( "Calling process Input\n" );
	ProcessInput();
	printf( "ClosingTablet\n" );
	
	Close();
	}



static bool
Init( void )

	{
	
	Tablet->GetTabletParameters( &Params );
	Params.EnableLogging = 1;
//	Params.TestIfConnected = true;
	Tablet->SetTabletParameters( &Params );

	Sig->StartCapture( Tablet );

	if ( Tablet->OpenTablet() == false )
		{
		Sig->StopCapture();
		return false;
		}

	return true;
	}


static void
Close()
	{
	Sig->StopCapture();
//	Sig->ExportSigFile( "Sigtablt.sig" );
//create myStr to hold a sample compressed SigString 
	static char  myStr[] = "08001F00F8011D01FFFF00000100000001000101000200040108000B010E0110021301130214011302130211010F010E010B010A010702050204010302020000000100FF1A0050013A0101FE05FC08FA0CF80FF811F912FA12FB13FD13FE12FF1200130012011200120110000FFF0D000BFE0AFE06FE02FF01FFFF00260089020601FF020004FF07FF0BFE0DFD0FFD10FC12FD12FC12FD12FD10FF0E010C020B0509070709050A030C020DFF0DFE0DFB0CFA0BF90BF90BF80BF809F809F906F904FA02FB01FC00FE00000000170046027901FF00FE0000FF000005FF07FF0BFE0DFE10FE11FD11FE12FD10FD10FD0EFC0DFC0BFB07FC03FE00FF00000000130061022B01FE00FF01FE00FF01020105FF07FF0BFF0DFE10FF12FE13FE14FF14FF100006000300FE002D00B1033901FE00FD01FA01F801F703F602F603F603F604F605F704F905FB06FE070008040B070C0A0D0B0D0C0C0B0C0A0B08090507050502050003FF03FD02FA02F800F500F300F3FFF2FEF3FFF4FFF500F700F900FD00FF00000000001500EE034B01000100040107010B000D011002120213021302120212030F020E010C010900060002000100FF000010009F034D0101FF03FF07FE0CFE12FE17FF1DFF21FE24FE23FC1EFC0CFE05FFFF00000000000000000000000000000000000000000000000000000000000000000000000000";

	Sig->CompressionMode = 1;
	Sig->SetSigString(myStr); //set the SigString to hard-coded signature
	Sig->DrawSignature( 10, 10, 800, 200, AutoJustify, 1 ); 
	Sig->WriteImageFile( ImageBmpMono, "Image.bmp" );  //write out image file
	Tablet->CloseTablet();

	delete Sig;
	delete Tablet;
	}


static int
TestTabletType( TabletInterface* Tab )
	{
	LCDInterface*	LCD = new LCDInterface( Tab );
	int				Value;

	Tablet->GetTabletParameters( &Params );
	Params.EnableLogging = 1;
	Params.TestIfConnected = true;
	Tablet->SetTabletParameters( &Params );

	if ( Tab->OpenTablet() == false )
		{
		Value = 0;
		}
	else
		{
		if ( 	LCD->LCDRefresh( 0, 0, 0, 20, 20 ) == true )
			{
			Value = 1;
			}
		else
			{
			Value = 2;
			}
		Tab->CloseTablet();
		}
	
	delete LCD;

	return Value;
	}






static void
ProcessInput()
	{
	bool		DoingSig = false;
	bool		PenDownLastTime = false;
	long		PenUpTime;

	while( true )
		{
		SigSleep( 10 );
		if ( Sig->PenState == PenDownState )
			{
			PenDownLastTime = true;
			continue;
			}
		if ( DoingSig == false )
			{
			if ( Sig->TotalPoints() != 0 )
				{
				DoingSig = true;
				}
			continue;
			}
		if ( PenDownLastTime == true )
			{
			PenUpTime = GetTimeInMS();
			PenDownLastTime = false;
			}
		else
			{
			if ( ( GetTimeInMS() - PenUpTime ) > 2000 )
				{
				break;
				}
			}
		}
		
	}


