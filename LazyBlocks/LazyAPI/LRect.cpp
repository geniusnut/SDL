////////////////////////////////////////
bool check_overlap( LRect *A, LRect *B )
////////////////////////////////////////
{
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
LRect make_rect( int x, int y, int w, int h )
/////////////////////////////////////////////
{
    LRect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    
    return rect;
}
