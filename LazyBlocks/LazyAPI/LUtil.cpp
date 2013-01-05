//////////////////////////////////////////////////////////
SDL_Surface *load_surface( string fileName, Uint32 trans )
//////////////////////////////////////////////////////////
{
	SDL_Surface *newSurface, *optimizedSurface;

    //load the surface
	newSurface = IMG_Load( fileName.c_str() );

    //if there was an error in loading the surface
	if( newSurface == NULL )
	{
        //return NULL
		return NULL;
	}

	//optimize the surface
	optimizedSurface = SDL_DisplayFormat( newSurface );

    //Get rid of the old surface
	SDL_FreeSurface( newSurface );

	//remove any transparent pixels from the surface
	SDL_SetColorKey( optimizedSurface, SDL_SRCCOLORKEY | SDL_RLEACCEL, trans );

    //and return the surface
	return optimizedSurface;
}

/////////////////////////////////////////////////////////////////////////////////////////////
void apply_surface( int x, int y, SDL_Surface *thisSurface, SDL_Surface *thatSurface, SDL_Rect* clip )
/////////////////////////////////////////////////////////////////////////////////////////////
{
	//put the x and y coordinates and put them in a rect
	SDL_Rect position;
	position.x = x;
	position.y = y;

    //if neither surface is null
    if( ( thisSurface != NULL ) && ( thatSurface != NULL ) )
    {
        //and finally blit it to the screen
	    SDL_BlitSurface( thisSurface, clip, thatSurface, &position );   
    }
}

////////////////////////////////////////////////////////
void clear_surface( SDL_Surface *surface, Uint32 trans )
////////////////////////////////////////////////////////
{
    //fill the surface with the default tranparent color
	SDL_FillRect( surface, &surface->clip_rect, trans );
	
	//and clear it
	SDL_SetColorKey( surface, SDL_SRCCOLORKEY, trans );
}

///////////////////////////////////////////////////////////
void fill_surface( SDL_Surface *surface, int r, int g, int b )
///////////////////////////////////////////////////////////
{ 
    //Full the surface
	SDL_FillRect( surface, &surface->clip_rect, SDL_MapRGB( surface->format, r, g, b ) );
}

////////////////////////////////////////////////////
void fill_surface( SDL_Surface *surface, Uint32 color )
////////////////////////////////////////////////////
{ 
    //Full the surface
	SDL_FillRect( surface, &surface->clip_rect, color );
}

////////////////////////////////////////////////////////////////////////////////////
void border_fill_surface( SDL_Surface *surface, Uint32 bColor, Uint32 fColor, int border )
////////////////////////////////////////////////////////////////////////////////////
{
    //fill the surface with a back ground color
	fill_surface( surface, bColor );
	
	//make a new Rect
	SDL_Rect temp = surface->clip_rect;

    //set the border
	temp.x = border;
	temp.y = border;
	temp.w -= border * 2;
	temp.h -= border * 2;
	
	//and fill the front color
	SDL_FillRect( surface, &temp, fColor );
}

////////////////////
void update_screen()
////////////////////
{
    //update the whole screen
	SDL_UpdateRect( SDL_GetVideoSurface(), 0, 0, SDL_GetVideoSurface()->w, SDL_GetVideoSurface()->h );
}

/////////////////////////////////////////////////////////////////
SDL_Surface *get_new_surface( const int surfaceType, int w, int h )
/////////////////////////////////////////////////////////////////
{
    //create and return a surface of the given width and hieght
    return SDL_CreateRGBSurface( surfaceType, w, h, SDL_GetVideoSurface()->format->BitsPerPixel, 0, 0, 0, 0 );
}

/////////////////////////////////////////
void destroy_surface( SDL_Surface *surface )
/////////////////////////////////////////
{
    SDL_FreeSurface( surface );
}

////////////////////////////////////////
bool check_overlap( SDL_Rect *A, SDL_Rect *B )
////////////////////////////////////////
{
    //I'm not even going to bother explaining how it works, I just know it does
	if( ( A->x > B->x ) && ( A->x < B->w + B->x ) && ( A->y > B->y ) && ( A->y < B->h + B->y ) )
	{
		return true;
	}
	if( ( A->x + A->w > B->x ) && ( A->x + A->w < B->w + B->x ) && ( A->y > B->y ) && ( A->y < B->h + B->y ) )
	{
		return true;
	}
	if( ( A->x > B->x ) && ( A->x < B->w + B->x ) && ( A->y + A->h > B->y ) && ( A->y + A->h < B->h + B->y ) )
	{
		return true;
	}
	if( ( A->x + A->w > B->x ) && ( A->x + A->w < B->w + B->x ) && ( A->y + A->h > B->y ) && ( A->y + A->h < B->h + B->y ) )
	{
		return true;
	}
	
	if( ( B->x > A->x ) && ( B->x < A->w + A->x ) && ( B->y > A->y ) && ( B->y < A->h + A->y ) )
	{
		return true;
	}
	if( ( B->x + B->w > A->x ) && ( B->x + B->w < A->w + A->x ) && ( B->y > A->y ) && ( B->y < A->h + A->y ) )
	{
		return true;
	}
	if( ( B->x > A->x ) && ( B->x < A->w + A->x ) && ( B->y + B->h > A->y ) && ( B->y + B->h < A->h + A->y ) )
	{
		return true;
	}
	if( ( B->x + B->w > A->x ) && ( B->x + B->w < A->w + A->x ) && ( B->y + B->h > A->y ) && ( B->y + B->h < A->h + A->y ) )
	{
		return true;
	}
		
	if( ( ( A->x == B->x ) && ( A->x + A->w == B->x + B->w ) ) && ( ( ( A->y > B->y ) && ( A->y < B->h + B->y ) ) || ( ( A->y + A->h > B->y ) && ( A->y + A->h < B->h + B->y ) ) ) )
	{
		return true;
	}

	if( ( ( A->y == B->y ) && ( A->y + A->h == B->y + B->h ) ) && ( ( ( A->x > B->x ) && ( A->x < B->w + B->x ) ) || ( ( A->x + A->w > B->x ) && ( A->x + A->w < B->w + B->x ) ) ) )
	{
		return true;
	}

	if( ( ( B->x == A->x ) && ( B->x + B->w == A->x + A->w ) ) && ( ( ( B->y > A->y ) && ( B->y < A->h + A->y ) ) || ( ( B->y + B->h > A->y ) && ( B->y + B->h < A->h + A->y ) ) ) )
	{
		return true;
	}

	if( ( ( B->y == A->y ) && ( B->y + B->h == A->y + A->h ) ) && ( ( ( B->x > A->x ) && ( B->x < A->w + A->x ) ) || ( ( B->x + B->w > A->x ) && ( B->x + B->w < A->w + A->x ) ) ) )
	{
		return true;
	}
	
	if( ( A->x == B->x ) && ( A->y == B->y ) && ( A->w == B->w ) && ( A->h == B->h ) )
	{
        return true;    
    }
    
	return false;
}

/////////////////////////////////////////////
SDL_Rect make_rect( int x, int y, int w, int h )
/////////////////////////////////////////////
{
    //make a rect 
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    
    //and return it
    return rect;
}

