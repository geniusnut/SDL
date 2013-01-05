//////////////
Block::Block()
//////////////
{
    //initialize the block offsets and dimentions
	box[ BLOCK_CENTER ].x = 0;
	box[ BLOCK_CENTER ].y = 0;
	box[ BLOCK_CENTER ].w = BLOCK_WIDTH;
	box[ BLOCK_CENTER ].h = BLOCK_HEIGHT;

    //set the dimentions of the surrounding collision boxes
	box[ BLOCK_TOP ].w = BLOCK_WIDTH;
	box[ BLOCK_TOP ].h = BLOCK_HEIGHT / 2;

	box[ BLOCK_BOTTOM ].w = BLOCK_WIDTH;
	box[ BLOCK_BOTTOM ].h = BLOCK_HEIGHT / 2;

	box[ BLOCK_LEFT ].w = BLOCK_WIDTH / 2;
	box[ BLOCK_LEFT ].h = BLOCK_HEIGHT;

	box[ BLOCK_RIGHT ].w = BLOCK_WIDTH / 2;
	box[ BLOCK_RIGHT ].h = BLOCK_HEIGHT;

    //set the locations
	set();
	
	//initialize the block's surface
	surface = NULL;

    //initialize the block's animation
	frame = 0;
	
	//initialize the block's status
	status = BLOCK_OUT_OF_PLAY;
}

/////////////////
void Block::set()
/////////////////
{
    //move the surrounding collision boxes
	box[ BLOCK_TOP ].x = box[ BLOCK_CENTER ].x;
	box[ BLOCK_TOP ].y = box[ BLOCK_CENTER ].y - BLOCK_HEIGHT / 2;

	box[ BLOCK_BOTTOM ].x = box[ BLOCK_CENTER ].x;
	box[ BLOCK_BOTTOM ].y = box[ BLOCK_CENTER ].y + box[ BLOCK_CENTER ].h;

	box[ BLOCK_LEFT ].x = box[ BLOCK_CENTER ].x - BLOCK_WIDTH / 2;
	box[ BLOCK_LEFT ].y = box[ BLOCK_CENTER ].y;

	box[ BLOCK_RIGHT ].x = box[ BLOCK_CENTER ].x + box[ BLOCK_CENTER ].w;
	box[ BLOCK_RIGHT ].y = box[ BLOCK_CENTER ].y;
}

////////////////////////////////
void Block::move( int x, int y )
////////////////////////////////
{
    //move the center block over the given amount
	box[ BLOCK_CENTER ].x += x;
	box[ BLOCK_CENTER ].y += y;
	
	//move the surrounding blocks
	set();
}

//////////////////////////////////
void Block::move_to( int x, int y)
//////////////////////////////////
{
    //move the the center block to a specific location
	box[ BLOCK_CENTER ].x = x;
	box[ BLOCK_CENTER ].y = y;
	
    //move the surrounding blocks
    set();
}

//////////////////
int Block::get_x()
//////////////////
{
    //get the X offset of the block
    return box[ BLOCK_CENTER ].x;
}

//////////////////
int Block::get_y()
//////////////////
{
    //get the Y offset of the block
    return box[ BLOCK_CENTER ].y;    
}
	
///////////////////////////////////////////////
void Block::set_surface( SDL_Surface* surface )
///////////////////////////////////////////////
{
    //set the block's surface
    this->surface = surface;   
}

//////////////////////////////
SDL_Surface* Block::get_surface()
//////////////////////////////
{
    //A temp surface pointer
    SDL_Surface* animation;
    
    //if the block is not in play
    if( status == BLOCK_OUT_OF_PLAY )
    {
        //set the animation to NULL
        animation = NULL;
    }
    
    //if the block is being used
    else if( ( status == BLOCK_IN_PLAY ) || ( status == BLOCK_STATIONARY ) )
    {
        //set the animation to the block's surface
        animation = surface;
    }
    
    //if the block is being shattered
    else if( status == BLOCK_SHATTERED )
    {
        //if the current frame is divisable by 2
        if( frame % 2 == 0 )
        {
            //set the animation to the block's surface
            animation = surface;
        }
        //other wise
        else
        {
            //set the animation to NULL
            animation = NULL;
        }
        
        //move over one frame
        frame++;
        
        //if the block has been flashing for more than one second
        if( frame > FRAMES_PER_SECOND )
        {
            //reset the animation
            frame = 0;
            
            //take out the block
            status = BLOCK_OUT_OF_PLAY;
        }
    }

    //return the animation
    return animation;    
}

/////////////////////////////////////
void Block::set_status( char status )
/////////////////////////////////////
{
    //set the status
    this->status = status;
}

////////////////////////
char Block::get_status()
////////////////////////
{
    //get the status
    return status;
}

//////////////////////////////////
void Block::set_frame( int frame )
//////////////////////////////////
{
    //set the frame
    this->frame = frame;
}

//////////////////////
int Block::get_frame()
//////////////////////
{
    //get the frame
    return frame;
}

////////////////////////////////////
SDL_Rect* Block::get_box( int thisBox )
////////////////////////////////////
{
    //return a pointer to a specified collision box
    return &box[ thisBox ];    
}    

//////////////////////////////////////////
Block *get_new_Block( Block* theseBlocks )
//////////////////////////////////////////
{
    //go through the set of blocks
	for( int get = 0; get < TOTAL_BLOCKS; get++ )
	{
        //if the block is not being used
		if( theseBlocks[ get ].get_status() == BLOCK_OUT_OF_PLAY )
		{
            //set the block in play
			theseBlocks[ get ].set_status( BLOCK_IN_PLAY );
			
            //return the block
            return &theseBlocks[ get ];
		}
	}

    //if nothing has been found return NULL
	return NULL;
}

////////////////////////////////////////////////////////////////
bool Block_out_of_bounds( Block *thisBlock, Block* theseBlocks )
////////////////////////////////////////////////////////////////
{
    //if the block is over the left of the screen
	if( thisBlock->get_x() < 0 )
	{
		return true;
	}
	
	//if the block is over the right of the screen
	else if( thisBlock->get_x() + BLOCK_WIDTH > BLOCK_WIDTH * FULL_ROW )
	{
		return true;
	}
	
	//if the block is under the block of the screen
	else if( thisBlock->get_y() + BLOCK_HEIGHT > TOTAL_ROWS * BLOCK_HEIGHT )
	{
		return true;
	}
	
	//go through the blocks
	for( int overlap = 0; overlap < TOTAL_BLOCKS ; overlap++ )
	{
        //if this block is in the same location as another stationary block
		if( ( thisBlock->get_x() == theseBlocks[ overlap ].get_x() ) && ( thisBlock->get_y() == theseBlocks[ overlap ].get_y() ) && ( theseBlocks[ overlap ].get_status() == BLOCK_STATIONARY ) )
		{
			return true;
		}
	}

    //if its not some place it shouldn't be
	return false;
}

///////////////////////////////////////////////////////////////
bool touches_stationary_block( SDL_Rect *box, Block* theseBlocks )
///////////////////////////////////////////////////////////////
{
    //go through the blocks
	for( int check = 0; check < TOTAL_BLOCKS; check++ )
	{
        //if a block is stationary
		if( theseBlocks[ check ].get_status() == BLOCK_STATIONARY )
		{
            //and the collision box touches the block
			if( check_overlap( box, theseBlocks[ check ].get_box( BLOCK_CENTER ) ) == true )
			{
				return true;
			}
		}
	}
	
	//if nothing was found
	return false;
}
