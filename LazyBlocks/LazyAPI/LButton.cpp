////////////////////////////////////////////
LButton::LButton( int x,int w,int y, int h )
////////////////////////////////////////////
{
    //pass the attributes to the Rect
	button.x = x;
	button.w = w;
	button.y = y;
	button.h = h;

    //make a new surface and box fill it
	this->buttonSurface = get_new_surface( SDL_SWSURFACE, w, h );
    border_fill_surface( this->buttonSurface, LWHITE32, LBLACK32 );
}

///////////////////
LButton::~LButton()
///////////////////
{
    //destroy the surface made in the constructor
    destroy_surface( buttonSurface );    
}

/////////////////////////
bool LButton::on_button()
/////////////////////////
{
    //get the mouse coordinates
    int x, y;
    SDL_GetMouseState( &x, &y );
    
    //check if the coordinates are within the button
	if( ( x >= button.x ) && ( x <= button.w + button.x ) && ( y >= button.y ) && ( y <= button.h + button.y ) )//if the coordinates are within the boundries
	{
		return true;
	}
	else
	{
		return false;
	}
}

//////////////////////////////////////
SDL_Surface *LButton::button_surface()
//////////////////////////////////////
{
    //simply return the surface
    return buttonSurface;    
}

/////////////////////////////////////////////////////
void LButton::show_button( SDL_Surface *thisSurface )
/////////////////////////////////////////////////////
{
    //apply the button's surface to the given surface
	apply_surface( button.x, button.y, buttonSurface, thisSurface );
}
