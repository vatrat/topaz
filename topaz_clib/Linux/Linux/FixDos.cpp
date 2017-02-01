#include <stdlib.h>
#include <stdio.h>


main( int ArgC, char** ArgV )
	{
	FILE*		InFile;
	FILE*		OutFile;
	int		Ch;

	InFile = fopen( ArgV[ 1 ], "rb" );
	OutFile = fopen( ArgV[ 2 ], "w" );

	if ( InFile == NULL )
		{
		printf( "Unable to open %s\n", ArgV[ 1 ] );
		exit( 0 );
		}

	if ( OutFile == NULL )
		{
		printf( "Unable to opem %s\n", ArgV[ 2 ] );
		exit( 0 );
		}

	while( 1 )
		{
		Ch = fgetc( InFile );
		if ( feof( InFile ) != 0 )
			{
			break;
			}
		if ( Ch != 13 )
			{
			fputc( Ch, OutFile );
			}
		}

	fclose( InFile );
	fclose( OutFile );
	}
