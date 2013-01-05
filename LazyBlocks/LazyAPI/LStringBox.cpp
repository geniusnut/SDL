//////////////////////////////////////////////////////////////////////////////////////////
LStringBox::LStringBox( int x, int y, int w, int maxLength, LFont *thisFont, string text )
//////////////////////////////////////////////////////////////////////////////////////////
{
    //do some intialization
	input = false;
	scrollPoint = 0;
	textWidth = 0;
	
	//handle arguments
	this->x = x;
	this->y = y;
	
	//get the maximum length
    this->maximumLength = maxLength;
    
    //get the actual string data
	this->text = text;
	
	//and get the font used
	userFont = thisFont;

    //create needed surfaces
	this->backSurface = get_new_surface( SDL_SWSURFACE, w, userFont->get_height() + 2 );
	border_fill_surface( this->backSurface, LBLACK32, LWHITE32 );

	this->textSurface = get_new_surface( SDL_SWSURFACE, w - 2, userFont->get_height() );
    clear_surface( this->textSurface );
	
	//create the blit offsets
	this->offset = new SDL_Rect;
		
	this->offset->x = 1;
	this->offset->y = 1;
}

/////////////////////////
LStringBox::~LStringBox()
/////////////////////////
{
    //free the surfaces made in the constructor
    destroy_surface( backSurface );
    destroy_surface( textSurface );
}

////////////////////////
bool LStringBox::shift()
////////////////////////
{
    //get the keys
	Uint8 *keystate = SDL_GetKeyState( NULL );

    //if either shift button is down
	if ( ( keystate[ SDLK_LSHIFT ] ) || ( keystate[ SDLK_RSHIFT ] ) )
	{
		return true;
	}

	return false;
}

///////////////////////////////////////////////////
void LStringBox::enter_text( SDL_Event *thisEvent )//interprets keypresses
///////////////////////////////////////////////////
{
	int stringPosition = 0;
	bool updateText = true;

	if( ( input == true ) && ( thisEvent->type == SDL_KEYDOWN ) )
	{
        //look for the last character in the string
		while( text[ stringPosition ] != '\0' )
		{
			stringPosition++;
		}

        //if we haven't gone out of bounds
		if( stringPosition < maximumLength )
		{	
            //is the shift button is down
			if( shift() == true )
			{
                //assign the proper character
				switch( thisEvent->key.keysym.sym )
				{
					case SDLK_a: text[ stringPosition ] = 'A'; break;
					case SDLK_b: text[ stringPosition ] = 'B'; break;
					case SDLK_c: text[ stringPosition ] = 'C'; break;
					case SDLK_d: text[ stringPosition ] = 'D'; break;
					case SDLK_e: text[ stringPosition ] = 'E'; break;
					case SDLK_f: text[ stringPosition ] = 'F'; break;
					case SDLK_g: text[ stringPosition ] = 'G'; break;
					case SDLK_h: text[ stringPosition ] = 'H'; break;
					case SDLK_i: text[ stringPosition ] = 'I'; break;
					case SDLK_j: text[ stringPosition ] = 'J'; break;
					case SDLK_k: text[ stringPosition ] = 'K'; break;
					case SDLK_l: text[ stringPosition ] = 'L'; break;
					case SDLK_m: text[ stringPosition ] = 'M'; break;
					case SDLK_n: text[ stringPosition ] = 'N'; break;
					case SDLK_o: text[ stringPosition ] = 'O'; break;
					case SDLK_p: text[ stringPosition ] = 'P'; break;
					case SDLK_q: text[ stringPosition ] = 'Q'; break;
					case SDLK_r: text[ stringPosition ] = 'R'; break;
					case SDLK_s: text[ stringPosition ] = 'S'; break;
					case SDLK_t: text[ stringPosition ] = 'T'; break;
					case SDLK_u: text[ stringPosition ] = 'U'; break;
					case SDLK_v: text[ stringPosition ] = 'V'; break;
					case SDLK_w: text[ stringPosition ] = 'W'; break;
					case SDLK_x: text[ stringPosition ] = 'X'; break;
					case SDLK_y: text[ stringPosition ] = 'Y'; break;
					case SDLK_z: text[ stringPosition ] = 'Z'; break;
					case SDLK_1: text[ stringPosition ] = '!'; break;
					case SDLK_2: text[ stringPosition ] = '@'; break;
					case SDLK_3: text[ stringPosition ] = '#'; break;
					case SDLK_4: text[ stringPosition ] = '$'; break;
					case SDLK_5: text[ stringPosition ] = '%'; break;
					case SDLK_6: text[ stringPosition ] = '^'; break;
					case SDLK_7: text[ stringPosition ] = '&'; break;
					case SDLK_8: text[ stringPosition ] = '*'; break;
					case SDLK_9: text[ stringPosition ] = '('; break;
					case SDLK_0: text[ stringPosition ] = ')'; break;
					case SDLK_BACKQUOTE: text[ stringPosition ] = '~'; break;
					case SDLK_MINUS: text[ stringPosition ] = '_'; break;
					case SDLK_EQUALS: text[ stringPosition ] = '+'; break;
					case SDLK_LEFTBRACKET: text[ stringPosition ] = '{'; break;
					case SDLK_RIGHTBRACKET: text[ stringPosition ] = '}'; break;
					case SDLK_SEMICOLON: text[ stringPosition ] = ':'; break;
					case SDLK_QUOTE: text[ stringPosition ] = '"'; break;
					case SDLK_COMMA: text[ stringPosition ] = '<'; break;
					case SDLK_PERIOD: text[ stringPosition ] = '>'; break;
					case SDLK_SLASH: text[ stringPosition ] = '?'; break;
					case SDLK_BACKSLASH: text[ stringPosition ] = '|'; break;
					default: updateText = false; break;//if no valid key was pressed don't update the text
				}
			}
			else//if the shift buttons are not down
			{
                //assign the proper character
				switch( thisEvent->key.keysym.sym )
				{
					case SDLK_0: text[ stringPosition ] = '0'; break;
					case SDLK_1: text[ stringPosition ] = '1'; break;
					case SDLK_2: text[ stringPosition ] = '2'; break;
					case SDLK_3: text[ stringPosition ] = '3'; break;
					case SDLK_4: text[ stringPosition ] = '4'; break;
					case SDLK_5: text[ stringPosition ] = '5'; break;
					case SDLK_6: text[ stringPosition ] = '6'; break;
					case SDLK_7: text[ stringPosition ] = '7'; break;
					case SDLK_8: text[ stringPosition ] = '8'; break;
					case SDLK_9: text[ stringPosition ] = '9'; break;
					case SDLK_a: text[ stringPosition ] = 'a'; break;
					case SDLK_b: text[ stringPosition ] = 'b'; break;
					case SDLK_c: text[ stringPosition ] = 'c'; break;
					case SDLK_d: text[ stringPosition ] = 'd'; break;
					case SDLK_e: text[ stringPosition ] = 'e'; break;
					case SDLK_f: text[ stringPosition ] = 'f'; break;
					case SDLK_g: text[ stringPosition ] = 'g'; break;
					case SDLK_h: text[ stringPosition ] = 'h'; break;
					case SDLK_i: text[ stringPosition ] = 'i'; break;
					case SDLK_j: text[ stringPosition ] = 'j'; break;
					case SDLK_k: text[ stringPosition ] = 'k'; break;
					case SDLK_l: text[ stringPosition ] = 'l'; break;
					case SDLK_m: text[ stringPosition ] = 'm'; break;
					case SDLK_n: text[ stringPosition ] = 'n'; break;
					case SDLK_o: text[ stringPosition ] = 'o'; break;
					case SDLK_p: text[ stringPosition ] = 'p'; break;
					case SDLK_q: text[ stringPosition ] = 'q'; break;
					case SDLK_r: text[ stringPosition ] = 'r'; break;
					case SDLK_s: text[ stringPosition ] = 's'; break;
					case SDLK_t: text[ stringPosition ] = 't'; break;
					case SDLK_u: text[ stringPosition ] = 'u'; break;
					case SDLK_v: text[ stringPosition ] = 'v'; break;
					case SDLK_w: text[ stringPosition ] = 'w'; break;
					case SDLK_x: text[ stringPosition ] = 'x'; break;
					case SDLK_y: text[ stringPosition ] = 'y'; break;
					case SDLK_z: text[ stringPosition ] = 'z'; break;
					case SDLK_BACKQUOTE: text[ stringPosition ] = '`'; break;
					case SDLK_MINUS: text[ stringPosition ] = '-'; break;
					case SDLK_EQUALS: text[ stringPosition ] = '='; break;
					case SDLK_LEFTBRACKET: text[ stringPosition ] = '['; break;
					case SDLK_RIGHTBRACKET: text[ stringPosition ] = ']'; break;
					case SDLK_SEMICOLON: text[ stringPosition ] = ';'; break;
					case SDLK_QUOTE: text[ stringPosition ] = '\''; break;
					case SDLK_COMMA: text[ stringPosition ] = ','; break;
					case SDLK_PERIOD: text[ stringPosition ] = '.'; break;
					case SDLK_SLASH: text[ stringPosition ] = '/'; break;
					case SDLK_BACKSLASH: text[ stringPosition ] = '\\'; break;
					case SDLK_SPACE: text[ stringPosition ] = ' '; break;

					case SDLK_BACKSPACE:
					//go back
                    stringPosition--;
					
					//as long as we don't go out of bounds
					if( stringPosition >= 0 )
					{
                        //make the character null
						text[ stringPosition ] = '\0';
					}
					break;

					default: updateText = false; break; //if no valid key was pressed don't update the text
				}
			}
			//set the next character to null
			text[ stringPosition + 1 ] = '\0';
		}
		else if( stringPosition >= maximumLength )
		{
            //if backspace is pressed
			if( thisEvent->key.keysym.sym == SDLK_BACKSPACE )
			{
                //go back and nullify the character
				stringPosition--; 
				text[ stringPosition ] = '\0';
			}
		}
	}

    //if the text needs to be updated
	if( updateText == true )
	{
        //clear the surface
		clear_surface( this->textSurface );
		
        //calculate the text width	
		textWidth = userFont->calc_width( text, NULL );
	
	    //if the text width is wider than the surface
		if( textWidth > textSurface->w )
		{
            //scroll
			scrollPoint = textSurface->w - textWidth;
		}
		else
		{
			scrollPoint = 0;
		}

        //out put the text
		userFont->text_out( scrollPoint, 0, this->textSurface, text );
	}
}

//////////////////////////////////////////////
void LStringBox::show_box( SDL_Surface *surface )
//////////////////////////////////////////////
{
    //get the blit offsets
    SDL_Rect temp = *this->offset;
    
    //and add the box offsets
    temp.x += x;
    temp.y += y;
    
    //apply the box
	apply_surface( this->x, this->y, this->backSurface, surface );
	
	//apply the text
	apply_surface( temp.x, temp.y, this->textSurface, surface );
}

//////////////////////////////
void LStringBox::allow_input()
//////////////////////////////
{
	input = true;
}

/////////////////////////////
void LStringBox::deny_input()
/////////////////////////////
{
	input = false;
}

//////////////////////////////////////////
void LStringBox::get_text( string newText )
//////////////////////////////////////////
{
    //copy the string
	text = newText;
    
    //clear the surface
	clear_surface( this->textSurface );
		
    //calculate the text width	
	textWidth = userFont->calc_width( text, NULL );
	
	//if the text width is wider than the surface
	if( textWidth > textSurface->w )
	{
        //scroll
		scrollPoint = textSurface->w - textWidth;
	}
	else
	{
		scrollPoint = 0;
	}

    //output the text
	userFont->text_out( scrollPoint, 0, this->textSurface, text );
}

///////////////////////////////
string LStringBox::get_string()
///////////////////////////////
{
    //return the text
	return text;
}
