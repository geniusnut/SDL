//////////////
Piece::Piece()
//////////////
{
    //put the piece in use
    destroy = false;
}

///////////////////////////
bool Piece::destroy_piece()
///////////////////////////
{
    //return destruction status
    return destroy;
}

/////////////////////////////
int Piece::number_of_blocks()
/////////////////////////////
{
    //return number of blocks
    return numBlocks;    
}

////////////////////////////////////
Block* Piece::get_block( int block )
////////////////////////////////////
{
    //if the requested block exists
    if( block < numBlocks )
    {
        //return the block
        return theseBlocks[ block ];
    }
    
    //otherwise return NULL
    return NULL;    
}

///////////////////////////////////
BasicPiece::BasicPiece( int level )
///////////////////////////////////
{
    //initialize direction variables
	down = false;
    left = false;
    right = false;
	direction = 0;
	
	//set to default rotation
    rotationStatus = 0;
    
    //set the drop rate
    if( level > 20 )
	{
		dropRate = 0;
	}
	else
	{
		dropRate = 1000 - ( level * ( 1000 / FRAMES_PER_SECOND ) );
	}
    
    //set the drop point to the bottom
    dropPoint = TOTAL_ROWS * BLOCK_HEIGHT;
    
    //start the drop timer
	timer.start_timer();
}

////////////////////////////
void BasicPiece::move_down()
////////////////////////////
{
    //get ready to move the piece
	bool move = true;
	
	//go through the blocks
	for( int shift = 0; shift < 4; shift ++ )
	{
        //if the blocks can't be moved down
		if( ( theseBlocks[ shift ]->get_y() + BLOCK_HEIGHT == BLOCK_HEIGHT * TOTAL_ROWS ) || ( touches_stationary_block( theseBlocks[ shift ]->get_box( BLOCK_BOTTOM ), blockSet ) == true ) )
		{
            //remember not to move the blocks
			move = false;
		}
	}

    //if the blocks can be moved
	if( move == true )
	{
        //move the piece down
		y += BLOCK_HEIGHT;
		
		//move the blocks down
		theseBlocks[ 0 ]->move( 0, BLOCK_HEIGHT );
		theseBlocks[ 1 ]->move( 0, BLOCK_HEIGHT );
		theseBlocks[ 2 ]->move( 0, BLOCK_HEIGHT );
		theseBlocks[ 3 ]->move( 0, BLOCK_HEIGHT );
	}
	else
	{
        //stop the blocks
		theseBlocks[ 0 ]->set_status( BLOCK_STATIONARY );
		theseBlocks[ 1 ]->set_status( BLOCK_STATIONARY );
		theseBlocks[ 2 ]->set_status( BLOCK_STATIONARY );
		theseBlocks[ 3 ]->set_status( BLOCK_STATIONARY );
		
        //remember to destroy the piece
        destroy = true;
    
        //play the effect
		Mix_PlayChannel( -1, effects[ EFFECTS_CRASH ], 0 );
	}
}

////////////////////////////
void BasicPiece::move_left()
////////////////////////////
{
    //get ready to move the piece
	bool move = true;
	
	//go through the blocks
	for( int shift = 0; shift < 4; shift ++ )
	{
        //if the piece can't be moved
		if( ( theseBlocks[ shift ]->get_x() == 0 ) || ( touches_stationary_block( theseBlocks[ shift ]->get_box( BLOCK_LEFT ), blockSet ) == true ) )
		{
            //don't move the piece
			move = false;
		}
	}

    //if we have to move the piece
	if( move == true )
	{
        //move it to the left
		x -= BLOCK_WIDTH;
		
		//move the blocks to the left
		theseBlocks[ 0 ]->move( -BLOCK_WIDTH, 0 );
		theseBlocks[ 1 ]->move( -BLOCK_WIDTH, 0 );
		theseBlocks[ 2 ]->move( -BLOCK_WIDTH, 0 );
		theseBlocks[ 3 ]->move( -BLOCK_WIDTH, 0 );

        //play the shift effect
		Mix_PlayChannel( -1, effects[ EFFECTS_SHIFT ], 0 );
	}
}

/////////////////////////////
void BasicPiece::move_right()
/////////////////////////////
{
	bool move = true;
	
	//go through the blocks
	for( int shift = 0; shift < 4; shift ++ )
	{
        //if the piece can't be moved
		if( ( theseBlocks[ shift ]->get_x() + BLOCK_WIDTH == BLOCK_WIDTH * FULL_ROW ) || ( touches_stationary_block( theseBlocks[ shift ]->get_box( BLOCK_RIGHT ), blockSet ) == true ) )
		{
            //remember not to move the piece
			move = false;
		}
	}

    //if the piece needs to be moved
	if( move == true )
	{
        //move the piece over
		x += BLOCK_WIDTH;
		
		//move the blocks
		theseBlocks[ 0 ]->move( BLOCK_WIDTH, 0 );
		theseBlocks[ 1 ]->move( BLOCK_WIDTH, 0 );
		theseBlocks[ 2 ]->move( BLOCK_WIDTH, 0 );
		theseBlocks[ 3 ]->move( BLOCK_WIDTH, 0 );

        //play the shift effect
		Mix_PlayChannel( -1, effects[ EFFECTS_SHIFT ], 0 );
	}
}

/////////////////////////////////////////////////////
void BasicPiece::handle_input( SDL_Event *thisEvent )
/////////////////////////////////////////////////////
{
    //if pause has been pressed
    if( ( thisEvent->key.keysym.sym == playerKeys[ LBKEY_PAUSE ] ) && ( thisEvent->type == SDL_KEYDOWN ) )
    {
        //if the timer is not paused
        if( timer.paused() == false )
        {   
            //pause the timer
            timer.pause_timer();
        }
        //otherwise
        else
        {
            //unpause the timer    
            timer.resume_timer();
        }
    }
    
    //if a button has been pressed or released
	if( ( thisEvent->type == SDL_KEYDOWN ) || ( thisEvent->type == SDL_KEYUP ) )
	{
        //get the state of the keys
		Uint8 *keystate = SDL_GetKeyState( NULL );
		
		//if left is down
		if( keystate[ playerKeys[ LBKEY_LEFT ] ] )
		{
			left = true;	
		}
		else
		{
			left = false;
		}

        //if right is down
		if( keystate[ playerKeys[ LBKEY_RIGHT ] ] )
		{
			right = true;	
		}
		else
		{
			right = false;
		}

        //if left is down
		if( keystate[ playerKeys[ LBKEY_DOWN ] ] )
		{
			down = true;
            dropPoint = y;	
		}
		else
		{
			down = false;
		}

        //if both left and right are down
		if( ( left == true ) && ( right == true ) )
		{
            //nullify them both
			left = false;
			right = false;
		}
	
	    //if a button has been pressed
		if( thisEvent->type == SDL_KEYDOWN )
		{
            //if up was pressed
			if( thisEvent->key.keysym.sym == playerKeys[ LBKEY_UP ] )
			{
                //rotate counter clockwise
				rotate_cw();
			}
			
			//if action 1 was pressed
			if( thisEvent->key.keysym.sym == playerKeys[ LBKEY_ACTION_1 ] )
			{
                //rotate clockwise
				rotate_ccw();
			}
			
			//if action 2 was pressed
			if( thisEvent->key.keysym.sym == playerKeys[ LBKEY_ACTION_2 ] )
			{
                //rotate counter clockwise
				rotate_cw();
			}
		}
	}
}

//////////////////////////////////////////////
void BasicPiece::on_frame( SDL_Surface *playArea )
//////////////////////////////////////////////
{
    //if the piece is still in use
    if( destroy == false )
    {
        //if left is down
        if( left == true )
	    {
            //reset the direction if needed
            if( direction > 0 )
    		{
    			direction = 0;
    		}

            //if the piece has finished its initial stall
    		if( ( direction == 0 ) || ( direction < -( FRAMES_PER_SECOND / 10 ) ) )
    		{
                //move the piece
    			move_left();
    		}

            //track the direction
    		direction--;
        }
        //if right is down
    	else if( right == true )
    	{
            //reset the direction if needed
    		if( direction < 0 )
    		{
    			direction = 0;
	       	}
            
            //if the piece finished its initial stall
    		if( ( direction == 0 ) || ( direction > ( FRAMES_PER_SECOND / 10 ) ) )
    		{
                //move right
    			move_right();
    		}

            //track the direction
    		direction++;
    	}
    	//if neither direction is down
    	else
    	{
            //reset the direction
    		direction = 0;	
    	}

        //if down is true
    	if( down == true )
    	{
            //move down
    		move_down();
    		
    		//reset the drop timer
    		timer.start_timer();

            //reset the direction
	        direction = 0;
    	}

        //if the time is up on drop timer
    	if( timer.get_ticks() > dropRate )
    	{
            //move down
    		move_down();
    		
    		//reset the drop timer
    		timer.start_timer();
    	}
    }
}

////////////////////////////////////////
int BasicPiece::get_destruction_points()
////////////////////////////////////////
{
    //initialize the score
    int score = 0;
    
    //if the player is not holding down
    if( down == false )
    {
        score = 0;    
    }
    //other wise
    else
    {
        //the score is relative to the distance between the point where the user pressed down
        //and where the piece stopped
        score = ( y - dropPoint ) / BLOCK_HEIGHT;    
    }
    
    //cap the score at 15
    if( score > 15 )
    {
        score = 15;    
    }
    
    //return the score
    return score;    
}


/*
After this point in this file I get lazy with the commenting mainly because I 
repeat myself a lot. So I'll explain how eveything in the rest of the file here.

The constructors for each of the pieces pretty much work like this:

move the piece to its initial spot
get the player's blockset
set the number of blocks
get the player's keys
initialize the blocks
move the blocks to their location



rotate() works like this:

if( rotationStatus == 0 )
{
    move block 0 here
    move block 1 here
    etc
}
else if( rotationStatus == 0 )
{
    move block 0 here
    move block 1 here
    etc
}



rotate_cw works like this:

increment rotationStatus

if rotationStatus is too high
set it to 0

call rotate()

if any of the blocks are out of bounds
decrement rotationStatus
call rotate


rotate_ccw works the same way only it goes rotationStatus goes down instead of up




From this point on in the file expect commenting to be more inconsistent than usual.
*/

//////////////////////////////////////////////////////////////////////////////////
Square::Square( Block* playerBlocks, SDLKey *keys, int level ):BasicPiece( level )
//////////////////////////////////////////////////////////////////////////////////
{
    //move the piece to its initial spot
	x = BLOCK_WIDTH * 4;
	y = 0;
    
    //get the player's blockset
    blockSet = playerBlocks;

    //set the number of blocks
	numBlocks = 4;

    //get the player's keys
    playerKeys = keys;
        
    //initialize the blocks
	for( int init = 0; init < 4; init++ )
	{
		theseBlocks[ init ] = get_new_Block( blockSet );
		theseBlocks[ init ]->set_surface( block_surface[ 1 ] );
		theseBlocks[ init ]->set_status( BLOCK_IN_PLAY );
		theseBlocks[ init ]->set_frame( 0 );
	}
    
    //move the blocks to their location
	theseBlocks[ 0 ]->move_to( x, y );
	theseBlocks[ 1 ]->move_to( x + BLOCK_WIDTH, y );
	theseBlocks[ 2 ]->move_to( x, y + BLOCK_HEIGHT );
	theseBlocks[ 3 ]->move_to( x + BLOCK_WIDTH, y + BLOCK_HEIGHT );
}

//////////////////////////////////////////////////////////////////////////////
Line::Line( Block* playerBlocks, SDLKey *keys, int level ):BasicPiece( level )
//////////////////////////////////////////////////////////////////////////////
{
    //move the piece to its initial spot
	x = BLOCK_WIDTH * 5;
	y = BLOCK_HEIGHT;
    
    //get the player's blockset
    blockSet = playerBlocks;
    
    //set the number of blocks
	numBlocks = 4;

    //get the player's keys
    playerKeys = keys;
    
	for( int init = 0; init < 4; init++ )
	{
		theseBlocks[ init ] = get_new_Block( blockSet );
		theseBlocks[ init ]->set_surface( block_surface[ 2 ] );
		theseBlocks[ init ]->set_status( BLOCK_IN_PLAY );
		theseBlocks[ init ]->set_frame( 0 );
	}
	
	rotate();
}

/////////////////////
void Line::rotate_cw()
/////////////////////
{
	rotationStatus++;
	if( rotationStatus > 1 )
	{
		rotationStatus = 0;
	}

	rotate();

	bool shiftBack = false;
	for( int error = 0; error < 4; error++ )
	{
		if( Block_out_of_bounds( theseBlocks[ error ], blockSet ) == true )
		{
			shiftBack = true;
		}
	}

	if( shiftBack == true )
	{
		rotationStatus--;
	
		if( rotationStatus < 0 )
		{
			rotationStatus = 1;
		}

		rotate();
	}
	else
	{
		Mix_PlayChannel( -1, effects[ EFFECTS_ROTATION ], 0 );
	}
}

///////////////////////
void Line::rotate_ccw()
///////////////////////
{
	rotationStatus--;
	if( rotationStatus < 0 )
	{
		rotationStatus = 1;
	}

	rotate();

	bool shiftBack = false;
	for( int error = 0; error < 4; error++ )
	{
		if( Block_out_of_bounds( theseBlocks[ error ], blockSet ) == true )
		{
			shiftBack = true;
		}
	}

	if( shiftBack == true )
	{
		rotationStatus++;
	
		if( rotationStatus > 1 )
		{
			rotationStatus = 0;
		}

		rotate();
	}
	else
	{
		Mix_PlayChannel( -1, effects[ EFFECTS_ROTATION ], 0 );
	}
}

///////////////////
void Line::rotate()
///////////////////
{
	if( rotationStatus == 0 )
	{
		theseBlocks[ 0 ]->move_to( x, y );
		theseBlocks[ 1 ]->move_to( x + BLOCK_WIDTH, y );
		theseBlocks[ 2 ]->move_to( x - BLOCK_WIDTH, y );
		theseBlocks[ 3 ]->move_to( x - BLOCK_WIDTH * 2, y );
	}
	else if( rotationStatus == 1 )
	{
		theseBlocks[ 0 ]->move_to( x, y );
		theseBlocks[ 1 ]->move_to( x, y + BLOCK_HEIGHT );
		theseBlocks[ 2 ]->move_to( x, y - BLOCK_HEIGHT );
		theseBlocks[ 3 ]->move_to( x, y - BLOCK_HEIGHT * 2 );
	}
}

//////////////////////////////////////////////////////////////////////////////////////
Triangle::Triangle( Block* playerBlocks, SDLKey *keys, int level ):BasicPiece( level )
//////////////////////////////////////////////////////////////////////////////////////
{
    //move the piece to its initial spot
	x = BLOCK_WIDTH * 4;
	y = BLOCK_HEIGHT;

    //get the player's blockset
    blockSet = playerBlocks;
    
    //set the number of blocks
    numBlocks = 4;
    
    //get the player's keys
    playerKeys = keys;
    
	for( int init = 0; init < 4; init++ )
	{
		theseBlocks[ init ] = get_new_Block( blockSet );
		theseBlocks[ init ]->set_surface( block_surface[ 0 ] );
		theseBlocks[ init ]->set_status( BLOCK_IN_PLAY );
		theseBlocks[ init ]->set_frame( 0 );
	}

	rotate();
}

/////////////////////////
void Triangle::rotate_cw()
/////////////////////////
{
	rotationStatus++;
	if( rotationStatus > 3 )
	{
		rotationStatus = 0;
	}

	rotate();

	bool shiftBack = false;
	for( int error = 0; error < 4; error++ )
	{
		if( Block_out_of_bounds( theseBlocks[ error ], blockSet ) == true )
		{
			shiftBack = true;
		}
	}

	if( shiftBack == true )
	{
		rotationStatus--;
		
		if( rotationStatus < 0 )
		{
			rotationStatus = 3;
		}

		rotate();
	}
	else
	{
		Mix_PlayChannel( -1, effects[ EFFECTS_ROTATION ], 0 );
	}
}

///////////////////////////
void Triangle::rotate_ccw()
///////////////////////////
{
	rotationStatus--;
	if( rotationStatus < 0 )
	{
		rotationStatus = 3;
	}

	rotate();

	bool shiftBack = false;
	for( int error = 0; error < 4; error++ )
	{
		if( Block_out_of_bounds( theseBlocks[ error ], blockSet ) == true )
		{
			shiftBack = true;
		}
	}

	if( shiftBack == true )
	{
		rotationStatus++;
	
		if( rotationStatus > 3 )
		{
			rotationStatus = 0;
		}

		rotate();
	}
	else
	{
		Mix_PlayChannel( -1, effects[ EFFECTS_ROTATION ], 0 );
	}
}

///////////////////////
void Triangle::rotate()
///////////////////////
{
	if( rotationStatus == 0 )
	{
		theseBlocks[ 0 ]->move_to( x, y );
		theseBlocks[ 1 ]->move_to( x, y - BLOCK_HEIGHT );
		theseBlocks[ 2 ]->move_to( x - BLOCK_WIDTH, y );
		theseBlocks[ 3 ]->move_to( x + BLOCK_WIDTH, y );
	}
	else if( rotationStatus == 1 )
	{
		theseBlocks[ 0 ]->move_to( x, y );
		theseBlocks[ 1 ]->move_to( x, y - BLOCK_HEIGHT );
		theseBlocks[ 2 ]->move_to( x, y + BLOCK_HEIGHT );
		theseBlocks[ 3 ]->move_to( x + BLOCK_WIDTH, y );
	}
	else if( rotationStatus == 2 )
	{
		theseBlocks[ 0 ]->move_to( x, y );
		theseBlocks[ 1 ]->move_to( x + BLOCK_WIDTH, y );
		theseBlocks[ 2 ]->move_to( x - BLOCK_WIDTH, y );
		theseBlocks[ 3 ]->move_to( x, y + BLOCK_HEIGHT );
	}
	else if( rotationStatus == 3 )
	{
		theseBlocks[ 0 ]->move_to( x, y );
		theseBlocks[ 1 ]->move_to( x - BLOCK_WIDTH, y );
		theseBlocks[ 2 ]->move_to( x, y - BLOCK_HEIGHT );
		theseBlocks[ 3 ]->move_to( x, y + BLOCK_HEIGHT );
	}
}

//////////////////////////////////////////////////////////////////////////////////////
ForwardL::ForwardL( Block* playerBlocks, SDLKey *keys, int level ):BasicPiece( level )
//////////////////////////////////////////////////////////////////////////////////////
{
    //move the piece to its initial spot
	x = BLOCK_WIDTH * 4;
	y = BLOCK_HEIGHT;

    //get the player's blockset
    blockSet = playerBlocks;

    //set the number of blocks
    numBlocks = 4;
    
    //get the player's keys
    playerKeys = keys;
    
	for( int init = 0; init < 4; init++ )
	{
		theseBlocks[ init ] = get_new_Block( blockSet );
		theseBlocks[ init ]->set_surface( block_surface[ 3 ] );
		theseBlocks[ init ]->set_status( BLOCK_IN_PLAY );
		theseBlocks[ init ]->set_frame( 0 );
	}

	rotate();
}

/////////////////////////
void ForwardL::rotate_cw()
/////////////////////////
{
	rotationStatus++;
	if( rotationStatus > 3 )
	{
		rotationStatus = 0;
	}

	rotate();

	bool shiftBack = false;
	for( int error = 0; error < 4; error++ )
	{
		if( Block_out_of_bounds( theseBlocks[ error ], blockSet ) == true )
		{
			shiftBack = true;
		}
	}

	if( shiftBack == true )
	{
		rotationStatus--;
	
		if( rotationStatus < 0 )
		{
			rotationStatus = 3;
		}

		rotate();
	}
	else
	{
		Mix_PlayChannel( -1, effects[ EFFECTS_ROTATION ], 0 );
	}
}

///////////////////////////
void ForwardL::rotate_ccw()
///////////////////////////
{
	rotationStatus--;
	if( rotationStatus < 0 )
	{
		rotationStatus = 3;
	}

	rotate();

	bool shiftBack = false;
	for( int error = 0; error < 4; error++ )
	{
		if( Block_out_of_bounds( theseBlocks[ error ], blockSet ) == true )
		{
			shiftBack = true;
		}
	}

	if( shiftBack == true )
	{
		rotationStatus++;
	
		if( rotationStatus > 3 )
		{
			rotationStatus = 0;
		}

		rotate();
	}
	else
	{
		Mix_PlayChannel( -1, effects[ EFFECTS_ROTATION ], 0 );
	}
}

///////////////////////
void ForwardL::rotate()
///////////////////////
{
	if( rotationStatus == 0 )
	{
		theseBlocks[ 0 ]->move_to( x, y );
		theseBlocks[ 1 ]->move_to( x - BLOCK_WIDTH, y );
		theseBlocks[ 2 ]->move_to( x + BLOCK_WIDTH, y );
		theseBlocks[ 3 ]->move_to( x - BLOCK_WIDTH, y + BLOCK_HEIGHT );
	}
	else if( rotationStatus == 1 )
	{
		theseBlocks[ 0 ]->move_to( x, y );
		theseBlocks[ 1 ]->move_to( x, y - BLOCK_HEIGHT );
		theseBlocks[ 2 ]->move_to( x, y + BLOCK_HEIGHT );
		theseBlocks[ 3 ]->move_to( x - BLOCK_WIDTH, y - BLOCK_HEIGHT );
	}
	else if( rotationStatus == 2 )
	{
		theseBlocks[ 0 ]->move_to( x, y );
		theseBlocks[ 1 ]->move_to( x + BLOCK_WIDTH, y);
		theseBlocks[ 2 ]->move_to( x - BLOCK_WIDTH, y );
		theseBlocks[ 3 ]->move_to( x + BLOCK_WIDTH, y - BLOCK_HEIGHT );
	}
	else if( rotationStatus == 3 )
	{
		theseBlocks[ 0 ]->move_to( x, y );
		theseBlocks[ 1 ]->move_to( x, y - BLOCK_HEIGHT );
		theseBlocks[ 2 ]->move_to( x, y + BLOCK_HEIGHT );
		theseBlocks[ 3 ]->move_to( x + BLOCK_WIDTH, y + BLOCK_HEIGHT );
	}
}

//////////////////////////////////////////////////////////////////////////////////////
ReverseL::ReverseL( Block* playerBlocks, SDLKey *keys, int level ):BasicPiece( level )
//////////////////////////////////////////////////////////////////////////////////////
{
    //move the piece to its initial spot
	x = BLOCK_WIDTH * 4;
	y = BLOCK_HEIGHT;

    //get the player's blockset
    blockSet = playerBlocks;
    
    //set the number of blocks
    numBlocks = 4;
	
	//get the player's keys
	playerKeys = keys;
	
	for( int init = 0; init < 4; init++ )
	{
		theseBlocks[ init ] = get_new_Block( blockSet );
		theseBlocks[ init ]->set_surface( block_surface[ 4 ] );
		theseBlocks[ init ]->set_status( BLOCK_IN_PLAY );
		theseBlocks[ init ]->set_frame( 0 );
	}

    rotate();
}

/////////////////////////
void ReverseL::rotate_cw()
/////////////////////////
{
	rotationStatus++;
	if( rotationStatus > 3 )
	{
		rotationStatus = 0;
	}

	rotate();

	bool shiftBack = false;
	for( int error = 0; error < 4; error++ )
	{
		if( Block_out_of_bounds( theseBlocks[ error ], blockSet ) == true )
		{
			shiftBack = true;
		}
	}

	if( shiftBack == true )
	{
		rotationStatus--;

		if( rotationStatus < 0 )
		{
			rotationStatus = 3;
		}

		rotate();
	}
	else
	{
		Mix_PlayChannel( -1, effects[ EFFECTS_ROTATION ], 0 );
	}
}

///////////////////////
void ReverseL::rotate_ccw()
///////////////////////
{
	rotationStatus--;
	if( rotationStatus < 0 )
	{
		rotationStatus = 3;
	}

	rotate();

	bool shiftBack = false;
	for( int error = 0; error < 4; error++ )
	{
		if( Block_out_of_bounds( theseBlocks[ error ], blockSet ) == true )
		{
			shiftBack = true;
		}
	}

	if( shiftBack == true )
	{
		rotationStatus++;

		if( rotationStatus > 3 )
		{
			rotationStatus = 0;
		}

		rotate();
	}
	else
	{
		Mix_PlayChannel( -1, effects[ EFFECTS_ROTATION ], 0 );
	}
}

///////////////////////
void ReverseL::rotate()
///////////////////////
{
	if( rotationStatus == 0 )
	{
		theseBlocks[ 0 ]->move_to( x, y );
		theseBlocks[ 1 ]->move_to( x + BLOCK_WIDTH, y );
		theseBlocks[ 2 ]->move_to( x - BLOCK_WIDTH, y );
		theseBlocks[ 3 ]->move_to( x + BLOCK_WIDTH, y + BLOCK_HEIGHT );
	}
	else if( rotationStatus == 1 )
	{
		theseBlocks[ 0 ]->move_to( x, y );
		theseBlocks[ 1 ]->move_to( x, y - BLOCK_HEIGHT );
		theseBlocks[ 2 ]->move_to( x, y + BLOCK_HEIGHT );
		theseBlocks[ 3 ]->move_to( x - BLOCK_WIDTH, y + BLOCK_HEIGHT );
	}
	else if( rotationStatus == 2 )
	{
		theseBlocks[ 0 ]->move_to( x, y );
		theseBlocks[ 1 ]->move_to( x - BLOCK_WIDTH, y );
		theseBlocks[ 2 ]->move_to( x + BLOCK_WIDTH, y );
		theseBlocks[ 3 ]->move_to( x - BLOCK_WIDTH, y - BLOCK_HEIGHT );
	}
	else if( rotationStatus == 3 )
	{
		theseBlocks[ 0 ]->move_to( x, y );
		theseBlocks[ 1 ]->move_to( x, y - BLOCK_HEIGHT );
		theseBlocks[ 2 ]->move_to( x, y + BLOCK_HEIGHT );
		theseBlocks[ 3 ]->move_to( x + BLOCK_WIDTH, y - BLOCK_HEIGHT );
	}
}

//////////////////////////////////////////////////////////////////////////////////////
ForwardS::ForwardS( Block* playerBlocks, SDLKey *keys, int level ):BasicPiece( level )
//////////////////////////////////////////////////////////////////////////////////////
{
    //move the piece to its initial spot
	x = BLOCK_WIDTH * 4;
	y = BLOCK_HEIGHT;

    //get the player's blockset
    blockSet = playerBlocks;
    
    //set the number of blocks
    numBlocks = 4;
    
    //get the player's keys
    playerKeys = keys;
    
	for( int init = 0; init < 4; init++ )
	{
		theseBlocks[ init ] = get_new_Block( blockSet );
		theseBlocks[ init ]->set_surface( block_surface[ 5 ] );
		theseBlocks[ init ]->set_status( BLOCK_IN_PLAY );
		theseBlocks[ init ]->set_frame( 0 );
	}

	rotate();
}

/////////////////////////
void ForwardS::rotate_cw()
/////////////////////////
{
	rotationStatus++;
	if( rotationStatus > 1 )
	{
		rotationStatus = 0;
	}

	rotate();

	bool shiftBack = false;
	for( int error = 0; error < 4; error++ )
	{
		if( Block_out_of_bounds( theseBlocks[ error ], blockSet ) == true )
		{
			shiftBack = true;
		}
	}

	if( shiftBack == true )
	{
		rotationStatus--;
	
		if( rotationStatus < 0 )
		{
			rotationStatus = 1;
		}

		rotate();
	}
	else
	{
		Mix_PlayChannel( -1, effects[ EFFECTS_ROTATION ], 0 );
	}
}

///////////////////////
void ForwardS::rotate_ccw()
///////////////////////
{
	rotationStatus--;
	if( rotationStatus < 0 )
	{
		rotationStatus = 1;
	}

	rotate();

	bool shiftBack = false;
	for( int error = 0; error < 4; error++ )
	{
		if( Block_out_of_bounds( theseBlocks[ error ], blockSet ) == true )
		{
			shiftBack = true;
		}
	}

	if( shiftBack == true )
	{
		rotationStatus++;

		if( rotationStatus > 1 )
		{
			rotationStatus = 0;
		}

		rotate();
	}
	else
	{
		Mix_PlayChannel( -1, effects[ EFFECTS_ROTATION ], 0 );
	}
}

///////////////////////
void ForwardS::rotate()
///////////////////////
{
	if( rotationStatus == 0 )
	{
		theseBlocks[ 0 ]->move_to( x, y );
		theseBlocks[ 1 ]->move_to( x - BLOCK_WIDTH, y );
		theseBlocks[ 2 ]->move_to( x, y + BLOCK_HEIGHT );
		theseBlocks[ 3 ]->move_to( x + BLOCK_WIDTH, y + BLOCK_HEIGHT );
	}
	else if( rotationStatus == 1 )
	{
		theseBlocks[ 0 ]->move_to( x, y );
		theseBlocks[ 1 ]->move_to( x + BLOCK_WIDTH, y );
		theseBlocks[ 2 ]->move_to( x + BLOCK_WIDTH, y - BLOCK_HEIGHT );
		theseBlocks[ 3 ]->move_to( x, y + BLOCK_HEIGHT );
	}
}

//////////////////////////////////////////////////////////////////////////////////////
ReverseS::ReverseS( Block* playerBlocks, SDLKey *keys, int level ):BasicPiece( level )
//////////////////////////////////////////////////////////////////////////////////////
{
    //move the piece to its initial spot
	x = BLOCK_WIDTH * 4;
	y = BLOCK_HEIGHT;

    //get the player's blockset
    blockSet = playerBlocks;
    
    //set the number of blocks
    numBlocks = 4;
    
    //get the player's keys
    playerKeys = keys;
	
	for( int init = 0; init < 4; init++ )
	{
		theseBlocks[ init ] = get_new_Block( blockSet );
		theseBlocks[ init ]->set_surface( block_surface[ 6 ] );
		theseBlocks[ init ]->set_status( BLOCK_IN_PLAY );
		theseBlocks[ init ]->set_frame( 0 );
	}
    
	rotate();
}

/////////////////////////
void ReverseS::rotate_cw()
/////////////////////////
{
	rotationStatus++;
	if( rotationStatus > 1 )
	{
		rotationStatus = 0;
	}

	rotate();

	bool shiftBack = false;
	for( int error = 0; error < 4; error++ )
	{
		if( Block_out_of_bounds( theseBlocks[ error ], blockSet ) == true )
		{
			shiftBack = true;
		}
	}

	if( shiftBack == true )
	{
		rotationStatus--;

		if( rotationStatus < 0 )
		{
			rotationStatus = 1;
		}

		rotate();
	}
	else
	{
		Mix_PlayChannel( -1, effects[ EFFECTS_ROTATION ], 0 );
	}
}

///////////////////////////
void ReverseS::rotate_ccw()
///////////////////////////
{
	rotationStatus--;
	if( rotationStatus < 0 )
	{
		rotationStatus = 1;
	}

	rotate();

	bool shiftBack = false;
	for( int error = 0; error < 4; error++ )
	{
		if( Block_out_of_bounds( theseBlocks[ error ], blockSet ) == true )
		{
			shiftBack = true;
		}
	}

	if( shiftBack == true )
	{
		rotationStatus++;

		if( rotationStatus > 1 )
		{
			rotationStatus = 0;
		}

		rotate();
	}
	else
	{
		Mix_PlayChannel( -1, effects[ EFFECTS_ROTATION ], 0 );
	}
}

///////////////////////
void ReverseS::rotate()
///////////////////////
{
	if( rotationStatus == 0 )
	{
		theseBlocks[ 0 ]->move_to( x, y );
		theseBlocks[ 1 ]->move_to( x + BLOCK_WIDTH, y );
		theseBlocks[ 2 ]->move_to( x, y + BLOCK_HEIGHT );
		theseBlocks[ 3 ]->move_to( x - BLOCK_WIDTH, y + BLOCK_HEIGHT );
	}
	else if( rotationStatus == 1 )
	{
		theseBlocks[ 0 ]->move_to( x, y );
		theseBlocks[ 1 ]->move_to( x + BLOCK_WIDTH, y );
		theseBlocks[ 2 ]->move_to( x + BLOCK_WIDTH, y + BLOCK_HEIGHT );
		theseBlocks[ 3 ]->move_to( x, y - BLOCK_HEIGHT );
	}
}
