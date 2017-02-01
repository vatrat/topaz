#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SigLib.h>
#include	"Test20.h"



struct		KeyCodeMap
	{
	int		Code;
	short		XStart;
	short		YStart;
	short		XSize;
	short		YSize;
	};

KeyCodeMap	KeyMap[] =
	{
		{ 0,		4,		136,	31,	31 },
		{ 1,		4,		99,	31,	31 },
		{ 2,		42,	99,	31,	31 },
		{ 3,		80,	99,	31,	31 },
		{ 4,		4,		61,	31,	31 },
		{ 5,		42,	61,	31,	31	},
		{ 6,		80,	61,	31,	31	},
		{ 7,		4,		23,	31,	31	},
		{ 8,		42,	23,	31,	31	},
		{ 9,		80,	23,	31,	31	},
		{ 10,		80,	136,	31,	31	},
		{ 11,		42,	136,	31,	31	},
		{ 12,		118,	23,	31,	69	},
		{ 13,		118,	99,	31,	69	},
		{ 14,		175,	40,	65,	13	},
		{ 15,		175,	81,	65,	13	}
	} ;


#define	NumKeys		( sizeof( KeyMap ) / sizeof( KeyCodeMap ) )



CharacterMap*			Font = new CharacterMap( Test20Font, Test20Font_Size );
Signature*				Sig;
TabletParameters		Params;
TabletInterface*		Tablet;
LCDInterface*			LCD;

int						BillAmount = 4000;
int						TipPercent = 15;
int						TipAmount = 0;
int						Total;

bool						Init( LCDGraphicBitmap* BackGround );
void						Close();
void						InitKeyPad();

void						UpdateBillAmount();
void						UpdateTipPercent();
void						UpdateTipAmount();
void						UpdateTotal();
void						UpdateAmounts();
int						FigureTip();

void						ProcessInput();
void						ProcessKeyPadData();



void
TipDemo( )
	{
	LCDGraphicBitmap*		BackGround = new LCDGraphicBitmap( 0, 0, "test.tif" );
	Tablet = new TabletInterface();
	Sig = new Signature(Tablet);
	LCD = new LCDInterface( Tablet );

	if ( Init( BackGround ) == false )
		{
		return;
		}

	ProcessInput();
	
	Close();
	}



bool
Init( LCDGraphicBitmap* BackGround )

	{
	int	TestValue;
	
	Tablet->GetTabletParameters( &Params );
//	Params.TabletMode = 0;
	Params.EnableLogging = 1;
	Params.TestIfConnected = 1;
	Tablet->SetTabletParameters( &Params );
	TestValue = Tablet->CheckTabletConnected();
	
	printf( "TabletConnected returnes %d\n", TestValue );

	Sig->StartCapture( Tablet );

	InitKeyPad();
	Sig->SetSigWindow( 1, 4, 177, 308, 57 );
	if ( Tablet->OpenTablet() == false )
		{
		Sig->StopCapture();
		return false;
		}

	LCD->LCDRefresh( 0, 0, 0, 320, 240 );
	LCD->LCDSendGraphic( 0, 2, BackGround );
	delete BackGround;
	LCD->LCDSetWindow( 4, 177, 308, 57 );

	
	UpdateAmounts();
	return true;
	}


void
Close()
	{
	LCD->LCDRefresh( 0, 0, 0, 320, 240 );
	Sig->StopCapture();
	Sig->ExportSigFile( "Sigtablt.sig" );
	Sig->DrawSignature( 10, 10, 	800, 200, AutoJustify, 1 );
	Sig->WriteImageFile( ImageBmpMono, "Image.bmp" );
	Tablet->CloseTablet();

	delete Sig;
	delete Tablet;
	}



void
InitKeyPad()
	{
	int		i;
	
	for( i = 0; i < NumKeys; i++ )
		{
		Sig->KeyPadAddHotSpot( KeyMap[ i ].Code, 1, KeyMap[ i ].XStart, KeyMap[ i ].YStart, KeyMap[ i ].XSize, KeyMap[ i ].YSize );
		}
	}



void
UpdateBillAmount()
	{
	char		Str[ 20 ];
	int		Width;
	
	sprintf( Str, "$%d.%02d", BillAmount / 100, BillAmount % 100 );
	Width = LCD->LCDStringWidth( Font, (unsigned char*)Str );

	LCD->LCDWriteString( 0, 2, 304 - Width, 22, Font, (unsigned char*)Str );
	}





void
UpdateTipPercent()
	{
	char		Str[ 20 ];
	int		Width;
	
	sprintf( Str, "%d%%", TipPercent );
	Width = LCD->LCDStringWidth( Font, (unsigned char*)Str );

	LCD->LCDWriteString( 0, 2, 230 - Width, 58, Font, (unsigned char*)Str );
	}




void
UpdateTipAmount()
	{
	char		Str[ 20 ];
	int		Width;
	int		Amount = FigureTip();
	
	sprintf( Str, "$%d.%02d", Amount / 100, Amount % 100  );
	Width = LCD->LCDStringWidth( Font, (unsigned char*)Str );

	LCD->LCDWriteString( 0, 2, 304 - Width, 98, Font, (unsigned char*)Str );
	}




void
UpdateTotal()
	{
	char		Str[ 20 ];
	int		Width;
	int		Amount = BillAmount + FigureTip();
	
	sprintf( Str, "$%d.%02d", Amount / 100, Amount % 100  );
	Width = LCD->LCDStringWidth( Font, (unsigned char*)Str );

	LCD->LCDWriteString( 0, 2, 304 - Width, 131, Font, (unsigned char*)Str );
	}



int
FigureTip()
	{
	int	Amount;
	
	if ( TipAmount == 0 )
		{
		Amount = ( TipPercent * BillAmount ) / 100;
		}
	else
		{
		Amount = TipAmount;
		}
	return Amount;
	}


void
UpdateAmounts()
	{
	UpdateBillAmount();
	UpdateTipPercent();
	UpdateTipAmount();
	UpdateTotal();
	LCD->SetLCDCaptureMode( LCDCapInk );
	}




void
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
			ProcessKeyPadData();
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



void
ProcessKeyPadData()
	{
	int		i;
	int		KeyCode = -1;

	for( i = 0; i < NumKeys; i++ )
		{
		if ( Sig->KeyPadQueryHotSpot( KeyMap[ i ].Code ) != 0 )
			{
			KeyCode = KeyMap[ i ].Code;
			Sig->ClearHotSpotPoints();
			break;
			}
		}
	switch( KeyCode )
		{
		case 0:
			{
			TipAmount *= 10;
			break;
			}
		case 1:
			{
			TipAmount *= 10;
			TipAmount += 1;
			break;
			}
		case 2:
			{
			TipAmount *= 10;
			TipAmount += 2;
			break;
			}
		case 3:
			{
			TipAmount *= 10;
			TipAmount += 3;
			break;
			}
		case 4:
			{
			TipAmount *= 10;
			TipAmount += 4;
			break;
			}
		case 5:
			{
			TipAmount *= 10;
			TipAmount += 5;
			break;
			}
		case 6:
			{
			TipAmount *= 10;
			TipAmount += 6;
			break;
			}
		case 7:
			{
			TipAmount *= 10;
			TipAmount += 7;
			break;
			}
		case 8:
			{
			TipAmount *= 10;
			TipAmount += 8;
			break;
			}
		case 9:
			{
			TipAmount *= 10;
			TipAmount += 9;
			break;
			}
		case 10:
			{
			TipAmount *= 100;
			break;
			}
		case 11:
			{
			break;
			}
		case 12:
			{
			TipAmount = 0;
			break;
			}
		case 13:
			{
			TipAmount /= 10;
			break;
			}
		case 14:
			{
			TipAmount = 0;
			if ( TipPercent > 0 )
				{
				TipPercent--;
				}
			break;
			}
		case 15:
			{
			TipPercent++;
			break;
			}
		default:
			{
			break;
			}
		}
	if ( KeyCode >= 0 )
		{
		UpdateAmounts();
		}
	}




