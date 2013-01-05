////////////////////////////////////////////////////////
LFont::LFont( SDL_Surface* fontImage, SDL_Rect rects[] )
////////////////////////////////////////////////////////
{
    //initialize x and y
	x = 0;
	y = 0;

    //get the font image
    font = fontImage;
    
	//get the clip rects
    for( int loadRects = 0; loadRects < LFONT_MAX_SURFACES; loadRects++ )
    {
        textSurfaces[ loadRects ] = rects[ loadRects ];
    }
    
    //initialize the space width
    w = 0;
    
    //calculate the average width
	for( int calcAW = 0; calcAW < LFONT_MAX_SURFACES; calcAW++ )
	{
		w += textSurfaces[ calcAW ].w;
	}

    //and assign the average width to the space width
    w = w / LFONT_MAX_SURFACES;

    //initalize the text height
	h = 0;
	
	//and set the maximum height to the text height
	for( int calcH = 0; calcH < LFONT_MAX_SURFACES; calcH++ )
	{
        if( textSurfaces[ calcH ].w > h )
        {
		  h = textSurfaces[ calcH ].w;
        }
	}
}

//////////////////////////////////////////
void LFont::test_font( SDL_Surface* surface )
//////////////////////////////////////////
{
    //this was just a quick testing function, nothing important here
    
    fill_surface( surface, LWHITE32 );
    text_out( 0, 0, surface, "" );
    /*
    ABCDEFGHIJKLM
    NOPQRSTUVWXYZ
    abcdefghijklm
    nopqrstuvwxyz
    0123456789
    !@#$%^&*()
    -_=+[]{};:\'\",.<>?/\\|`~
    */
    update_screen();
    SDL_Delay( 5000 );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void LFont::text_out( int x, int y, SDL_Surface *thisSurface, string text, unsigned long int flags )
//////////////////////////////////////////////////////////////////////////////////////////////////////
{
	//get the new x and y coordinates
	this->y = y;
	this->x = x; 

	//the part of the text image going to be used
	SDL_Rect textImage;

    //align x offset
	if( bool( flags & LFONT_HCENTER ) )
	{
		x = ( thisSurface->w - calc_width( text, thisSurface ) ) / 2;
	}
	else if( bool( flags & LFONT_LEFT ) )
	{
        x = 0;    
    }
    else if( bool( flags & LFONT_RIGHT ) )
	{
        x = ( thisSurface->w - calc_width( text, thisSurface ) );
    }

    //align the y off set
	if( bool( flags & LFONT_VCENTER ) )
	{
		y = ( thisSurface->h - calc_max( text, thisSurface ).h ) / 2;
	}
	else if( bool( flags & LFONT_TOP ) )
	{
        y = 0;
    }
    else if( bool( flags & LFONT_BOTTOM ) )
	{
        y = ( thisSurface->h - calc_max( text, thisSurface ).h );
    }

	//go through the string
	for( int stringPosition = 0; text[ stringPosition ] != '\0'; stringPosition++ )//while the current postion in the string is not a null character, keep going through the string
	{
		switch( text[ stringPosition ] )//the current postion in the string
		{
			//assign the proper surface
			case 'A': textImage = textSurfaces[ LFONT_A ]; break;
			case 'B': textImage = textSurfaces[ LFONT_B ]; break;
			case 'C': textImage = textSurfaces[ LFONT_C ]; break;
			case 'D': textImage = textSurfaces[ LFONT_D ]; break;
			case 'E': textImage = textSurfaces[ LFONT_E ]; break;
			case 'F': textImage = textSurfaces[ LFONT_F ]; break;
			case 'G': textImage = textSurfaces[ LFONT_G ]; break;
			case 'H': textImage = textSurfaces[ LFONT_H ]; break;
			case 'I': textImage = textSurfaces[ LFONT_I ]; break;
			case 'J': textImage = textSurfaces[ LFONT_J ]; break;
			case 'K': textImage = textSurfaces[ LFONT_K ]; break;
			case 'L': textImage = textSurfaces[ LFONT_L ]; break;
			case 'M': textImage = textSurfaces[ LFONT_M ]; break;
			case 'N': textImage = textSurfaces[ LFONT_N ]; break;
			case 'O': textImage = textSurfaces[ LFONT_O ]; break;
			case 'P': textImage = textSurfaces[ LFONT_P ]; break;
			case 'Q': textImage = textSurfaces[ LFONT_Q ]; break;
			case 'R': textImage = textSurfaces[ LFONT_R ]; break;
			case 'S': textImage = textSurfaces[ LFONT_S ]; break;
			case 'T': textImage = textSurfaces[ LFONT_T ]; break;
			case 'U': textImage = textSurfaces[ LFONT_U ]; break;
			case 'V': textImage = textSurfaces[ LFONT_V ]; break;
			case 'W': textImage = textSurfaces[ LFONT_W ]; break;
			case 'X': textImage = textSurfaces[ LFONT_X ]; break;
			case 'Y': textImage = textSurfaces[ LFONT_Y ]; break;
			case 'Z': textImage = textSurfaces[ LFONT_Z ]; break;

			case 'a': textImage = textSurfaces[ LFONT_a ]; break;
			case 'b': textImage = textSurfaces[ LFONT_b ]; break;
			case 'c': textImage = textSurfaces[ LFONT_c ]; break;
			case 'd': textImage = textSurfaces[ LFONT_d ]; break;
			case 'e': textImage = textSurfaces[ LFONT_e ]; break;
			case 'f': textImage = textSurfaces[ LFONT_f ]; break;
			case 'g': textImage = textSurfaces[ LFONT_g ]; break;
			case 'h': textImage = textSurfaces[ LFONT_h ]; break;
			case 'i': textImage = textSurfaces[ LFONT_i ]; break;
			case 'j': textImage = textSurfaces[ LFONT_j ]; break;
			case 'k': textImage = textSurfaces[ LFONT_k ]; break;
			case 'l': textImage = textSurfaces[ LFONT_l ]; break;
			case 'm': textImage = textSurfaces[ LFONT_m ]; break;
			case 'n': textImage = textSurfaces[ LFONT_n ]; break;
			case 'o': textImage = textSurfaces[ LFONT_o ]; break;
			case 'p': textImage = textSurfaces[ LFONT_p ]; break;
			case 'q': textImage = textSurfaces[ LFONT_q ]; break;
			case 'r': textImage = textSurfaces[ LFONT_r ]; break;
			case 's': textImage = textSurfaces[ LFONT_s ]; break;
			case 't': textImage = textSurfaces[ LFONT_t ]; break;
			case 'u': textImage = textSurfaces[ LFONT_u ]; break;
			case 'v': textImage = textSurfaces[ LFONT_v ]; break;
			case 'w': textImage = textSurfaces[ LFONT_w ]; break;
			case 'x': textImage = textSurfaces[ LFONT_x ]; break;
			case 'y': textImage = textSurfaces[ LFONT_y ]; break;
			case 'z': textImage = textSurfaces[ LFONT_z ]; break;

			case '0': textImage = textSurfaces[ LFONT_0 ]; break;
			case '1': textImage = textSurfaces[ LFONT_1 ]; break;
			case '2': textImage = textSurfaces[ LFONT_2 ]; break;
			case '3': textImage = textSurfaces[ LFONT_3 ]; break;
			case '4': textImage = textSurfaces[ LFONT_4 ]; break;
			case '5': textImage = textSurfaces[ LFONT_5 ]; break;
			case '6': textImage = textSurfaces[ LFONT_6 ]; break;
			case '7': textImage = textSurfaces[ LFONT_7 ]; break;
			case '8': textImage = textSurfaces[ LFONT_8 ]; break;
			case '9': textImage = textSurfaces[ LFONT_9 ]; break;

			case '!': textImage = textSurfaces[ LFONT_EXCLAIM ]; break;
			case '@': textImage = textSurfaces[ LFONT_AT ]; break;
			case '#': textImage = textSurfaces[ LFONT_HASH ]; break;
			case '$': textImage = textSurfaces[ LFONT_DOLLAR ]; break;
			case '%': textImage = textSurfaces[ LFONT_PERCENT ]; break;
			case '^': textImage = textSurfaces[ LFONT_CARET ]; break;
			case '&': textImage = textSurfaces[ LFONT_AMPERSAND ]; break;
			case '*': textImage = textSurfaces[ LFONT_ASTERISK ]; break;
			case '(': textImage = textSurfaces[ LFONT_LEFTPAREN ]; break;
			case ')': textImage = textSurfaces[ LFONT_RIGHTPAREN ]; break;
			case '-': textImage = textSurfaces[ LFONT_MINUS ]; break;
			case '_': textImage = textSurfaces[ LFONT_UNDERSCORE ]; break;
			case '=': textImage = textSurfaces[ LFONT_EQUALS ]; break;
			case '+': textImage = textSurfaces[ LFONT_PLUS ]; break;
			case '[': textImage = textSurfaces[ LFONT_LEFTBRACKET ]; break;
			case ']': textImage = textSurfaces[ LFONT_RIGHTBRACKET ]; break;
			case '{': textImage = textSurfaces[ LFONT_LEFTBRACE ]; break;
			case '}': textImage = textSurfaces[ LFONT_RIGHTBRACE ]; break;
			case ';': textImage = textSurfaces[ LFONT_SEMICOLON ]; break;
			case ':': textImage = textSurfaces[ LFONT_COLON ]; break;
			case '\'': textImage = textSurfaces[ LFONT_QUOTE ]; break;
			case '\"': textImage = textSurfaces[ LFONT_DBLQUOTE ]; break;
			case ',': textImage = textSurfaces[ LFONT_COMMA ]; break;
			case '.': textImage = textSurfaces[ LFONT_PERIOD ]; break;
			case '<': textImage = textSurfaces[ LFONT_LESS ]; break;
			case '>': textImage = textSurfaces[ LFONT_GREATER ]; break;
			case '?': textImage = textSurfaces[ LFONT_QUESTION ]; break;
			case '/': textImage = textSurfaces[ LFONT_SLASH ]; break;
			case '|': textImage = textSurfaces[ LFONT_LINE ]; break;
			case '\\': textImage = textSurfaces[ LFONT_BACKSLASH ]; break;
			case '`': textImage = textSurfaces[ LFONT_BACKQUOTE ]; break;
			case '~': textImage = textSurfaces[ LFONT_TILDE ]; break;

			case ' ': x += w; break;//if there's a space move overthe space width

			case '\n': x = 0; y += h; break;//if there's newline, move down the text height
		}
	
	    // if the current character is not null, a newline or a space
		if( ( text[ stringPosition ] != '\0' ) && ( text[ stringPosition ] != '\n' ) && ( text[ stringPosition ] != ' ' ) )
		{
            //if the text surface will go off the screen
			if( x + textImage.w > thisSurface->w )
			{
                //if wrap is enabled
				if( bool( flags & LFONT_WRAP ) )
				{
                    //move down
					x = 0;
					y += h;

                    //and align the x offset
					if( bool( flags & LFONT_HCENTER ) )
					{
						x = ( thisSurface->w - calc_width( &text[ stringPosition + 1 ], thisSurface ) ) / 2;
					}
					else if( bool( flags & LFONT_LEFT ) )
	                {
                        x = 0;    
                    }
                    else if( bool( flags & LFONT_RIGHT ) )
	                {
                        x = ( thisSurface->w - calc_width( &text[ stringPosition + 1 ], thisSurface ) );
                    }
				}
			}
			
			//stick the text surface onto the surface
			apply_surface( x, y, font, thisSurface, &textImage );
			
			//and move over the x offset the width of the surface 
			x += textImage.w;
		}
		else
		{	
            //if there's a new line
			if( text[ stringPosition ] == '\n' )
			{
                //align the x offset
				if( bool( flags & LFONT_HCENTER ) )
				{
					x = ( thisSurface->w - calc_width( &text[ stringPosition + 1 ], thisSurface ) ) / 2;
				}
				else if( bool( flags & LFONT_LEFT ) )
	            {
                    x = 0;    
                }
                else if( bool( flags & LFONT_RIGHT ) )
	            {
                    x = ( thisSurface->w - calc_width( &text[ stringPosition + 1 ], thisSurface ) );
                }
			}
		}	
    
	}
}

//////////////////////////////////////////////////////////
int LFont::calc_width( string text, SDL_Surface *surface )
//////////////////////////////////////////////////////////
{
	int width = 0;
	int max = -1;

    //if no surface is given, it will not wrap
	if( surface != NULL )
	{
		max = surface->w;
	}

    //while we haven't reached the end of a line
	for( int calc = 0; ( text[ calc ] != '\0' ) && ( text[ calc ] != '\n' ) && ( ( width <= max ) || ( max == -1 ) ); calc++ )
	{
		int tempWidth = 0;

		switch( text[ calc ] )//the current postion in the string
		{
			//assign the proper surface
			case 'A': tempWidth = textSurfaces[ LFONT_A ].w; break;
			case 'B': tempWidth = textSurfaces[ LFONT_B ].w; break;
			case 'C': tempWidth = textSurfaces[ LFONT_C ].w; break;
			case 'D': tempWidth = textSurfaces[ LFONT_D ].w; break;
			case 'E': tempWidth = textSurfaces[ LFONT_E ].w; break;
			case 'F': tempWidth = textSurfaces[ LFONT_F ].w; break;
			case 'G': tempWidth = textSurfaces[ LFONT_G ].w; break;
			case 'H': tempWidth = textSurfaces[ LFONT_H ].w; break;
			case 'I': tempWidth = textSurfaces[ LFONT_I ].w; break;
			case 'J': tempWidth = textSurfaces[ LFONT_J ].w; break;
			case 'K': tempWidth = textSurfaces[ LFONT_K ].w; break;
			case 'L': tempWidth = textSurfaces[ LFONT_L ].w; break;
			case 'M': tempWidth = textSurfaces[ LFONT_M ].w; break;
			case 'N': tempWidth = textSurfaces[ LFONT_N ].w; break;
			case 'O': tempWidth = textSurfaces[ LFONT_O ].w; break;
			case 'P': tempWidth = textSurfaces[ LFONT_P ].w; break;
			case 'Q': tempWidth = textSurfaces[ LFONT_Q ].w; break;
			case 'R': tempWidth = textSurfaces[ LFONT_R ].w; break;
			case 'S': tempWidth = textSurfaces[ LFONT_S ].w; break;
			case 'T': tempWidth = textSurfaces[ LFONT_T ].w; break;
			case 'U': tempWidth = textSurfaces[ LFONT_U ].w; break;
			case 'V': tempWidth = textSurfaces[ LFONT_V ].w; break;
			case 'W': tempWidth = textSurfaces[ LFONT_W ].w; break;
			case 'X': tempWidth = textSurfaces[ LFONT_X ].w; break;
			case 'Y': tempWidth = textSurfaces[ LFONT_Y ].w; break;
			case 'Z': tempWidth = textSurfaces[ LFONT_Z ].w; break;

			case 'a': tempWidth = textSurfaces[ LFONT_a ].w; break;
			case 'b': tempWidth = textSurfaces[ LFONT_b ].w; break;
			case 'c': tempWidth = textSurfaces[ LFONT_c ].w; break;
			case 'd': tempWidth = textSurfaces[ LFONT_d ].w; break;
			case 'e': tempWidth = textSurfaces[ LFONT_e ].w; break;
			case 'f': tempWidth = textSurfaces[ LFONT_f ].w; break;
			case 'g': tempWidth = textSurfaces[ LFONT_g ].w; break;
			case 'h': tempWidth = textSurfaces[ LFONT_h ].w; break;
			case 'i': tempWidth = textSurfaces[ LFONT_i ].w; break;
			case 'j': tempWidth = textSurfaces[ LFONT_j ].w; break;
			case 'k': tempWidth = textSurfaces[ LFONT_k ].w; break;
			case 'l': tempWidth = textSurfaces[ LFONT_l ].w; break;
			case 'm': tempWidth = textSurfaces[ LFONT_m ].w; break;
			case 'n': tempWidth = textSurfaces[ LFONT_n ].w; break;
			case 'o': tempWidth = textSurfaces[ LFONT_o ].w; break;
			case 'p': tempWidth = textSurfaces[ LFONT_p ].w; break;
			case 'q': tempWidth = textSurfaces[ LFONT_q ].w; break;
			case 'r': tempWidth = textSurfaces[ LFONT_r ].w; break;
			case 's': tempWidth = textSurfaces[ LFONT_s ].w; break;
			case 't': tempWidth = textSurfaces[ LFONT_t ].w; break;
			case 'u': tempWidth = textSurfaces[ LFONT_u ].w; break;
			case 'v': tempWidth = textSurfaces[ LFONT_v ].w; break;
			case 'w': tempWidth = textSurfaces[ LFONT_w ].w; break;
			case 'x': tempWidth = textSurfaces[ LFONT_x ].w; break;
			case 'y': tempWidth = textSurfaces[ LFONT_y ].w; break;
			case 'z': tempWidth = textSurfaces[ LFONT_z ].w; break;

			case '0': tempWidth = textSurfaces[ LFONT_0 ].w; break;
			case '1': tempWidth = textSurfaces[ LFONT_1 ].w; break;
			case '2': tempWidth = textSurfaces[ LFONT_2 ].w; break;
			case '3': tempWidth = textSurfaces[ LFONT_3 ].w; break;
			case '4': tempWidth = textSurfaces[ LFONT_4 ].w; break;
			case '5': tempWidth = textSurfaces[ LFONT_5 ].w; break;
			case '6': tempWidth = textSurfaces[ LFONT_6 ].w; break;
			case '7': tempWidth = textSurfaces[ LFONT_7 ].w; break;
			case '8': tempWidth = textSurfaces[ LFONT_8 ].w; break;
			case '9': tempWidth = textSurfaces[ LFONT_9 ].w; break;

			case '!': tempWidth = textSurfaces[ LFONT_EXCLAIM ].w; break;
			case '@': tempWidth = textSurfaces[ LFONT_AT ].w; break;
			case '#': tempWidth = textSurfaces[ LFONT_HASH ].w; break;
			case '$': tempWidth = textSurfaces[ LFONT_DOLLAR ].w; break;
			case '%': tempWidth = textSurfaces[ LFONT_PERCENT ].w; break;
			case '^': tempWidth = textSurfaces[ LFONT_CARET ].w; break;
			case '&': tempWidth = textSurfaces[ LFONT_AMPERSAND ].w; break;
			case '*': tempWidth = textSurfaces[ LFONT_ASTERISK ].w; break;
			case '(': tempWidth = textSurfaces[ LFONT_LEFTPAREN ].w; break;
			case ')': tempWidth = textSurfaces[ LFONT_RIGHTPAREN ].w; break;
			case '-': tempWidth = textSurfaces[ LFONT_MINUS ].w; break;
			case '_': tempWidth = textSurfaces[ LFONT_UNDERSCORE ].w; break;
			case '=': tempWidth = textSurfaces[ LFONT_EQUALS ].w; break;
			case '+': tempWidth = textSurfaces[ LFONT_PLUS ].w; break;
			case '[': tempWidth = textSurfaces[ LFONT_LEFTBRACKET ].w; break;
			case ']': tempWidth = textSurfaces[ LFONT_RIGHTBRACKET ].w; break;
			case '{': tempWidth = textSurfaces[ LFONT_LEFTBRACE ].w; break;
			case '}': tempWidth = textSurfaces[ LFONT_RIGHTBRACE ].w; break;
			case ';': tempWidth = textSurfaces[ LFONT_SEMICOLON ].w; break;
			case ':': tempWidth = textSurfaces[ LFONT_COLON ].w; break;
			case '\'': tempWidth = textSurfaces[ LFONT_QUOTE ].w; break;
			case '\"': tempWidth = textSurfaces[ LFONT_DBLQUOTE ].w; break;
			case ',': tempWidth = textSurfaces[ LFONT_COMMA ].w; break;
			case '.': tempWidth = textSurfaces[ LFONT_PERIOD ].w; break;
			case '<': tempWidth = textSurfaces[ LFONT_LESS ].w; break;
			case '>': tempWidth = textSurfaces[ LFONT_GREATER ].w; break;
			case '?': tempWidth = textSurfaces[ LFONT_QUESTION ].w; break;
			case '/': tempWidth = textSurfaces[ LFONT_SLASH ].w; break;
			case '|': tempWidth = textSurfaces[ LFONT_LINE ].w; break;
			case '\\': tempWidth = textSurfaces[ LFONT_BACKSLASH ].w; break;
			case '`': tempWidth = textSurfaces[ LFONT_BACKQUOTE ].w; break;
			case '~': tempWidth = textSurfaces[ LFONT_TILDE ].w; break;
			case ' ': tempWidth = w;
		}	
		
		width += tempWidth;
	}

	return width;
}

//////////////////////////////////////////////////////////////
SDL_Rect LFont::calc_max( string text, SDL_Surface *surface )
//////////////////////////////////////////////////////////////
{
    //A rect to hold the maximum values
	SDL_Rect max;

    //initalize the variables
	max.x = 0;
	max.y = 0;
	max.w = 0;
	max.h = 0;

	//go through the string
	for( int stringPosition = 0; text[ stringPosition ] != '\0'; stringPosition++ )//while the current postion in the string is not a null character, keep going through the string
	{
		int tempWidth = 0;
		
		//the current postion in the string
		switch( text[ stringPosition ] )
		{
			//assign the proper surface width
			case 'A': tempWidth = textSurfaces[ LFONT_A ].w; break;
			case 'B': tempWidth = textSurfaces[ LFONT_B ].w; break;
			case 'C': tempWidth = textSurfaces[ LFONT_C ].w; break;
			case 'D': tempWidth = textSurfaces[ LFONT_D ].w; break;
			case 'E': tempWidth = textSurfaces[ LFONT_E ].w; break;
			case 'F': tempWidth = textSurfaces[ LFONT_F ].w; break;
			case 'G': tempWidth = textSurfaces[ LFONT_G ].w; break;
			case 'H': tempWidth = textSurfaces[ LFONT_H ].w; break;
			case 'I': tempWidth = textSurfaces[ LFONT_I ].w; break;
			case 'J': tempWidth = textSurfaces[ LFONT_J ].w; break;
			case 'K': tempWidth = textSurfaces[ LFONT_K ].w; break;
			case 'L': tempWidth = textSurfaces[ LFONT_L ].w; break;
			case 'M': tempWidth = textSurfaces[ LFONT_M ].w; break;
			case 'N': tempWidth = textSurfaces[ LFONT_N ].w; break;
			case 'O': tempWidth = textSurfaces[ LFONT_O ].w; break;
			case 'P': tempWidth = textSurfaces[ LFONT_P ].w; break;
			case 'Q': tempWidth = textSurfaces[ LFONT_Q ].w; break;
			case 'R': tempWidth = textSurfaces[ LFONT_R ].w; break;
			case 'S': tempWidth = textSurfaces[ LFONT_S ].w; break;
			case 'T': tempWidth = textSurfaces[ LFONT_T ].w; break;
			case 'U': tempWidth = textSurfaces[ LFONT_U ].w; break;
			case 'V': tempWidth = textSurfaces[ LFONT_V ].w; break;
			case 'W': tempWidth = textSurfaces[ LFONT_W ].w; break;
			case 'X': tempWidth = textSurfaces[ LFONT_X ].w; break;
			case 'Y': tempWidth = textSurfaces[ LFONT_Y ].w; break;
			case 'Z': tempWidth = textSurfaces[ LFONT_Z ].w; break;

			case 'a': tempWidth = textSurfaces[ LFONT_a ].w; break;
			case 'b': tempWidth = textSurfaces[ LFONT_b ].w; break;
			case 'c': tempWidth = textSurfaces[ LFONT_c ].w; break;
			case 'd': tempWidth = textSurfaces[ LFONT_d ].w; break;
			case 'e': tempWidth = textSurfaces[ LFONT_e ].w; break;
			case 'f': tempWidth = textSurfaces[ LFONT_f ].w; break;
			case 'g': tempWidth = textSurfaces[ LFONT_g ].w; break;
			case 'h': tempWidth = textSurfaces[ LFONT_h ].w; break;
			case 'i': tempWidth = textSurfaces[ LFONT_i ].w; break;
			case 'j': tempWidth = textSurfaces[ LFONT_j ].w; break;
			case 'k': tempWidth = textSurfaces[ LFONT_k ].w; break;
			case 'l': tempWidth = textSurfaces[ LFONT_l ].w; break;
			case 'm': tempWidth = textSurfaces[ LFONT_m ].w; break;
			case 'n': tempWidth = textSurfaces[ LFONT_n ].w; break;
			case 'o': tempWidth = textSurfaces[ LFONT_o ].w; break;
			case 'p': tempWidth = textSurfaces[ LFONT_p ].w; break;
			case 'q': tempWidth = textSurfaces[ LFONT_q ].w; break;
			case 'r': tempWidth = textSurfaces[ LFONT_r ].w; break;
			case 's': tempWidth = textSurfaces[ LFONT_s ].w; break;
			case 't': tempWidth = textSurfaces[ LFONT_t ].w; break;
			case 'u': tempWidth = textSurfaces[ LFONT_u ].w; break;
			case 'v': tempWidth = textSurfaces[ LFONT_v ].w; break;
			case 'w': tempWidth = textSurfaces[ LFONT_w ].w; break;
			case 'x': tempWidth = textSurfaces[ LFONT_x ].w; break;
			case 'y': tempWidth = textSurfaces[ LFONT_y ].w; break;
			case 'z': tempWidth = textSurfaces[ LFONT_z ].w; break;

			case '0': tempWidth = textSurfaces[ LFONT_0 ].w; break;
			case '1': tempWidth = textSurfaces[ LFONT_1 ].w; break;
			case '2': tempWidth = textSurfaces[ LFONT_2 ].w; break;
			case '3': tempWidth = textSurfaces[ LFONT_3 ].w; break;
			case '4': tempWidth = textSurfaces[ LFONT_4 ].w; break;
			case '5': tempWidth = textSurfaces[ LFONT_5 ].w; break;
			case '6': tempWidth = textSurfaces[ LFONT_6 ].w; break;
			case '7': tempWidth = textSurfaces[ LFONT_7 ].w; break;
			case '8': tempWidth = textSurfaces[ LFONT_8 ].w; break;
			case '9': tempWidth = textSurfaces[ LFONT_9 ].w; break;

			case '!': tempWidth = textSurfaces[ LFONT_EXCLAIM ].w; break;
			case '@': tempWidth = textSurfaces[ LFONT_AT ].w; break;
			case '#': tempWidth = textSurfaces[ LFONT_HASH ].w; break;
			case '$': tempWidth = textSurfaces[ LFONT_DOLLAR ].w; break;
			case '%': tempWidth = textSurfaces[ LFONT_PERCENT ].w; break;
			case '^': tempWidth = textSurfaces[ LFONT_CARET ].w; break;
			case '&': tempWidth = textSurfaces[ LFONT_AMPERSAND ].w; break;
			case '*': tempWidth = textSurfaces[ LFONT_ASTERISK ].w; break;
			case '(': tempWidth = textSurfaces[ LFONT_LEFTPAREN ].w; break;
			case ')': tempWidth = textSurfaces[ LFONT_RIGHTPAREN ].w; break;
			case '-': tempWidth = textSurfaces[ LFONT_MINUS ].w; break;
			case '_': tempWidth = textSurfaces[ LFONT_UNDERSCORE ].w; break;
			case '=': tempWidth = textSurfaces[ LFONT_EQUALS ].w; break;
			case '+': tempWidth = textSurfaces[ LFONT_PLUS ].w; break;
			case '[': tempWidth = textSurfaces[ LFONT_LEFTBRACKET ].w; break;
			case ']': tempWidth = textSurfaces[ LFONT_RIGHTBRACKET ].w; break;
			case '{': tempWidth = textSurfaces[ LFONT_LEFTBRACE ].w; break;
			case '}': tempWidth = textSurfaces[ LFONT_RIGHTBRACE ].w; break;
			case ';': tempWidth = textSurfaces[ LFONT_SEMICOLON ].w; break;
			case ':': tempWidth = textSurfaces[ LFONT_COLON ].w; break;
			case '\'': tempWidth = textSurfaces[ LFONT_QUOTE ].w; break;
			case '\"': tempWidth = textSurfaces[ LFONT_DBLQUOTE ].w; break;
			case ',': tempWidth = textSurfaces[ LFONT_COMMA ].w; break;
			case '.': tempWidth = textSurfaces[ LFONT_PERIOD ].w; break;
			case '<': tempWidth = textSurfaces[ LFONT_LESS ].w; break;
			case '>': tempWidth = textSurfaces[ LFONT_GREATER ].w; break;
			case '?': tempWidth = textSurfaces[ LFONT_QUESTION ].w; break;
			case '/': tempWidth = textSurfaces[ LFONT_SLASH ].w; break;
			case '|': tempWidth = textSurfaces[ LFONT_LINE ].w; break;
			case '\\': tempWidth = textSurfaces[ LFONT_BACKSLASH ].w; break;
			case '`': tempWidth = textSurfaces[ LFONT_BACKQUOTE ].w; break;
			case '~': tempWidth = textSurfaces[ LFONT_TILDE ].w; break;

			case ' ': max.w += w; break;//if there's a space move over the space width

			case '\n': max.x = 0; max.y += h; break;//if there's newline, move down the text height
		}
        
        //if the end of line has been reached	
		if( ( text[ stringPosition ] != '\0' ) && ( text[ stringPosition ] != '\n' ) && ( text[ stringPosition ] != ' ' ) )// if the current character is not null, a newline or a space
		{
            //set a new maximum width if needed
            if( max.x > max.w )
            {
                max.w = max.x;
            }
            
            //move down if needed
			if( max.x + tempWidth > surface->w )//if the text surface will go off the screen
			{
				//go back to the beginning of the screen and go down the text height
				max.x = 0;
				max.y += h;
			}
			
			//move over the text image width 
			max.x += tempWidth;
		}
    
	}
	
	//set a new maximum width if needed
	if( max.x > max.w )
    {
        max.w = max.x;
    }

    //increment one more line
	max.h = max.y + h;

    //and return the maximum values
	return max;
}

///////////////////////
int LFont::get_height()
///////////////////////
{
	//return the text height
	return h;
}

//////////////////////
int LFont::get_space()
//////////////////////
{
    //return the average width
	return w;
}
