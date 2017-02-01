//
//		CharacterMap.h
//



class SIGAPI CharacterMap
	{
	public:

								CharacterMap( );
								CharacterMap( char* FileName );
								CharacterMap( unsigned char* FontData, unsigned int FontSize );
								~CharacterMap();

		bool					LoadCharacterMap( char* FileName );
		bool					LoadCharacterMap( unsigned char* FontData, unsigned int FontSize );
		
		BitmapCharacter*	LookupCharacter( int CharCode );


		short					NumCharacters;
		BitmapCharacter**	Characters;

	} ;

