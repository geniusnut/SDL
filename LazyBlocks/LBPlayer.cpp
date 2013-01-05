////////////////////////////////////
LazyBlocksPlayer::LazyBlocksPlayer()
////////////////////////////////////
{
    //initialize score variables
    lines = 0;
    score = 0;
    
    //set the next piece
    nextPiece = rand() % 7;
    
    //initialize the blocks
    for( int init = 0; init < TOTAL_BLOCKS; init++ )
	{
		playerBlocks[ init ].set_status( BLOCK_OUT_OF_PLAY );
	}
	
	//initialize the rows
    for( int init = 0; init < TOTAL_ROWS; init++ )
	{
		playerRows[ init ].x = 0;
		playerRows[ init ].y = init * BLOCK_HEIGHT;
		playerRows[ init ].h = BLOCK_HEIGHT;
		playerRows[ init ].w = BLOCK_WIDTH * FULL_ROW; 
	}
	
	//get a new piece
	get_new_piece();
	
	//set the play surface
	xPlay = 220, yPlay = 50;
	playSurface = get_new_surface( SDL_SWSURFACE, FULL_ROW * BLOCK_WIDTH, TOTAL_ROWS * BLOCK_HEIGHT );
	
	//set the piece preview surface
	xPiece = 10, yPiece = 100;
    pieceSurface = get_new_surface( SDL_SWSURFACE, BLOCK_HEIGHT * 5, BLOCK_HEIGHT * 5 );
	
	//set the lines surface
	xLines = 500, yLines = 200;
    linesSurface = get_new_surface( SDL_SWSURFACE, 100, 60 );
	
	//set the level surface
	xLevel = 500, yLevel = 300;
    levelSurface = get_new_surface( SDL_SWSURFACE, 100, 60 );
	
	//set the score surface
	xScore = 220, yScore = 10;
    scoreSurface = get_new_surface( SDL_SWSURFACE, 200, 30 );
    
    //set the keys
    keys[ LBKEY_UP ] = DEFAULT_UP;
    keys[ LBKEY_DOWN ] = DEFAULT_DOWN;
    keys[ LBKEY_LEFT ] = DEFAULT_LEFT;
    keys[ LBKEY_RIGHT ] = DEFAULT_RIGHT;
    keys[ LBKEY_ACTION_1 ] = DEFAULT_ACTION_1;
    keys[ LBKEY_ACTION_2 ] = DEFAULT_ACTION_2;
    keys[ LBKEY_PAUSE ] = DEFAULT_PAUSE;
}

/////////////////////////////////////
LazyBlocksPlayer::~LazyBlocksPlayer()
/////////////////////////////////////
{
    //if there's a piece to delete
    if( playerPiece != NULL )
    {
        delete playerPiece;
    }
    
    //free the surfaces
    destroy_surface( playSurface );
    destroy_surface( pieceSurface );
    destroy_surface( linesSurface );
    destroy_surface( levelSurface );
    destroy_surface( scoreSurface );
}

////////////////////////////////////////////////////////
void LazyBlocksPlayer::handle_events( SDL_Event *event )
////////////////////////////////////////////////////////
{
    //handle piece events
    playerPiece->handle_input( event );
    
    //if the player wants to pause
    if( ( event->key.keysym.sym == keys[ LBKEY_PAUSE ] ) && ( event->type == SDL_KEYDOWN ) )
    {
        //stop the music
        Mix_PauseMusic();
        
        //Print "Pause" on the screen
        largeFont->text_out( 0, 0, screen, "Paused", LFONT_HCENTER | LFONT_VCENTER );
        
        //update the screen
        update_screen();
        
        //play pause sound effect            
        Mix_PlayChannel( -1, effects[ EFFECTS_PAUSE ], 0 );
                    
        //pause the game
        bool paused = true;
        
        //while the game is pause
        while( paused == true )
        {
            //if there's an event to handle
            if( SDL_PollEvent( event ) )
            {
                //if a key was pressed
                if( event->type == SDL_KEYDOWN )
                {
                    //if the player want to unpause
                    if( event->key.keysym.sym == keys[ LBKEY_PAUSE ] )
                    {
                        //unpause the piece
                        playerPiece->handle_input( event );
                        
                        //start the music again
                        Mix_ResumeMusic();
                        
                        //unpause
                        paused = false;
                    }
                    //if the user want to quit
                    else if( event->key.keysym.sym == SDLK_ESCAPE )
                    {
                        //quit the game
                        quit = true;
                        
                        //unpause
                        paused = false;
                    }
                }
                //if the user Xed out
                else if( event->type == SDL_QUIT )
                {
                    //quit the game
                    quit = true;
                        
                    //unpause
                    paused = false;                    
                }
            }
        }
    }
}

/////////////////////////////////////////////////////////////////
void LazyBlocksPlayer::show_player_blocks( SDL_Surface* surface )
/////////////////////////////////////////////////////////////////
{
    //fill the surface grey
	fill_surface( playSurface, 128, 128, 128 );

    //apply the block surfaces
	for( int show = 0; show < TOTAL_BLOCKS; show++ )
	{
		apply_surface( playerBlocks[ show ].get_x(), playerBlocks[ show ].get_y(), playerBlocks[ show ].get_surface(), playSurface );
	}
	
	//do piece animation
	if( playerPiece != NULL )
	{
	   playerPiece->on_frame( playSurface );
    }
    
    //apply the playSurface
    apply_surface( xPlay, yPlay, playSurface, surface );
}

////////////////////////////////////////////////////////
void LazyBlocksPlayer::show_data( SDL_Surface* surface )
////////////////////////////////////////////////////////
{
    //show status surfaces
    show_next_piece( surface );
    show_lines( surface );
    show_level( surface );
    show_score( surface );
}

/////////////////////////////////////
void LazyBlocksPlayer::manage_piece()
/////////////////////////////////////
{
    //if we need a new piece
    if( playerPiece->destroy_piece() )
	{
        //get the points form the piece
        score += playerPiece->get_destruction_points();
	    
        //delete the piece
        delete playerPiece;
	    
	    //get a new one
	    get_new_piece();
	    
	    //update the data
	    show_data( screen );
    }
}

/////////////////////////////////////
bool LazyBlocksPlayer::check_blocks()
/////////////////////////////////////
{
    //check for a game over
    bool gameOver = over_limit();
    
    //shatter any made rows
    shatter_rows();
    
    //return the game over status
    return gameOver;
}

//////////////////////////////////////////////////////////////
void LazyBlocksPlayer::show_next_piece( SDL_Surface* surface )
//////////////////////////////////////////////////////////////
{
    //fill the surface
	border_fill_surface( pieceSurface, 0, 0xD0D8D0 );

    //and show the next piece
	switch( nextPiece )
	{
		case PIECE_TYPE_SQUARE: 
		apply_surface( ( ( pieceSurface->w - ( BLOCK_WIDTH * 2 ) ) / 2 ), ( ( pieceSurface->h - ( BLOCK_HEIGHT * 2 ) ) / 2 ), block_surface[ 1 ], pieceSurface );

		apply_surface( BLOCK_WIDTH + ( ( pieceSurface->w - ( BLOCK_WIDTH * 2 ) ) / 2 ), ( ( pieceSurface->h - ( BLOCK_HEIGHT * 2 ) ) / 2 ), block_surface[ 1 ], pieceSurface );
		
		apply_surface( ( ( pieceSurface->w - ( BLOCK_WIDTH * 2 ) ) / 2 ), BLOCK_HEIGHT + ( ( pieceSurface->h - ( BLOCK_HEIGHT * 2 ) ) / 2 ), block_surface[ 1 ], pieceSurface );
		
		apply_surface( BLOCK_WIDTH +  ( ( pieceSurface->w - ( BLOCK_WIDTH * 2 ) ) / 2 ), BLOCK_HEIGHT + ( ( pieceSurface->h - ( BLOCK_HEIGHT * 2 ) ) / 2 ), block_surface[ 1 ], pieceSurface );
		break;

		case PIECE_TYPE_TRIANGLE:
		apply_surface( ( ( pieceSurface->w - ( BLOCK_WIDTH ) ) / 2 ), ( ( pieceSurface->h - ( BLOCK_HEIGHT * 2 ) ) / 2 ), block_surface[ 0 ], pieceSurface );

		apply_surface( ( ( pieceSurface->w - ( BLOCK_WIDTH * 3 ) ) / 2 ), BLOCK_HEIGHT + ( ( pieceSurface->h - ( BLOCK_HEIGHT * 2 ) ) / 2 ), block_surface[ 0 ], pieceSurface );
		
		apply_surface( BLOCK_WIDTH + ( ( pieceSurface->w - ( BLOCK_WIDTH * 3 ) ) / 2 ), BLOCK_HEIGHT + ( ( pieceSurface->h - ( BLOCK_HEIGHT * 2 ) ) / 2 ), block_surface[ 0 ], pieceSurface );
		
		apply_surface( BLOCK_WIDTH * 2 +  ( ( pieceSurface->w - ( BLOCK_WIDTH * 3 ) ) / 2 ), BLOCK_HEIGHT + ( ( pieceSurface->h - ( BLOCK_HEIGHT * 2 ) ) / 2 ), block_surface[ 0 ], pieceSurface );
		break;

		case PIECE_TYPE_LINE: 
		apply_surface( ( ( pieceSurface->w - ( BLOCK_WIDTH * 4 ) ) / 2 ), ( ( pieceSurface->h - ( BLOCK_HEIGHT ) ) / 2 ), block_surface[ 2 ], pieceSurface );

		apply_surface( BLOCK_WIDTH + ( ( pieceSurface->w - ( BLOCK_WIDTH * 4 ) ) / 2 ), ( ( pieceSurface->h - ( BLOCK_HEIGHT ) ) / 2 ), block_surface[ 2 ], pieceSurface );
		
		apply_surface( BLOCK_WIDTH * 2 + ( ( pieceSurface->w - ( BLOCK_WIDTH * 4 ) ) / 2 ), ( ( pieceSurface->h - ( BLOCK_HEIGHT ) ) / 2 ), block_surface[ 2 ], pieceSurface );
		
		apply_surface( BLOCK_WIDTH * 3 +  ( ( pieceSurface->w - ( BLOCK_WIDTH * 4 ) ) / 2 ), ( ( pieceSurface->h - ( BLOCK_HEIGHT ) ) / 2 ), block_surface[ 2 ], pieceSurface );
		break;

		case PIECE_TYPE_FORWARDL:
		apply_surface( ( ( pieceSurface->w - ( BLOCK_WIDTH * 3 ) ) / 2 ), ( ( pieceSurface->h - ( BLOCK_HEIGHT * 2 ) ) / 2 ), block_surface[ 3 ], pieceSurface );

		apply_surface( BLOCK_WIDTH + ( ( pieceSurface->w - ( BLOCK_WIDTH * 3 ) ) / 2 ), ( ( pieceSurface->h - ( BLOCK_HEIGHT * 2 ) ) / 2 ), block_surface[ 3 ], pieceSurface );
		
		apply_surface( BLOCK_WIDTH * 2 + ( ( pieceSurface->w - ( BLOCK_WIDTH * 3 ) ) / 2 ), ( ( pieceSurface->h - ( BLOCK_HEIGHT * 2 ) ) / 2 ), block_surface[ 3 ], pieceSurface );
		
		apply_surface( ( ( pieceSurface->w - ( BLOCK_WIDTH * 3 ) ) / 2 ), BLOCK_HEIGHT + ( ( pieceSurface->h - ( BLOCK_HEIGHT * 2 ) ) / 2 ), block_surface[ 3 ], pieceSurface );
		break;

		case PIECE_TYPE_REVERSEL: 
		apply_surface( ( ( pieceSurface->w - ( BLOCK_WIDTH * 3 ) ) / 2 ), ( ( pieceSurface->h - ( BLOCK_HEIGHT * 2 ) ) / 2 ), block_surface[ 4 ], pieceSurface );

		apply_surface( BLOCK_WIDTH + ( ( pieceSurface->w - ( BLOCK_WIDTH * 3 ) ) / 2 ), ( ( pieceSurface->h - ( BLOCK_HEIGHT * 2 ) ) / 2 ), block_surface[ 4 ], pieceSurface );
		
		apply_surface( BLOCK_WIDTH * 2 + ( ( pieceSurface->w - ( BLOCK_WIDTH * 3 ) ) / 2 ), ( ( pieceSurface->h - ( BLOCK_HEIGHT * 2 ) ) / 2 ), block_surface[ 4 ], pieceSurface );
		
		apply_surface( BLOCK_WIDTH * 2 + ( ( pieceSurface->w - ( BLOCK_WIDTH * 3 ) ) / 2 ), BLOCK_HEIGHT + ( ( pieceSurface->h - ( BLOCK_HEIGHT * 2 ) ) / 2 ), block_surface[ 4 ], pieceSurface );
		break;

		case PIECE_TYPE_FORWARDS: 
		apply_surface( ( ( pieceSurface->w - ( BLOCK_WIDTH * 3 ) ) / 2 ), ( ( pieceSurface->h - ( BLOCK_HEIGHT * 2 ) ) / 2 ), block_surface[ 5 ], pieceSurface );

		apply_surface( BLOCK_WIDTH + ( ( pieceSurface->w - ( BLOCK_WIDTH * 3 ) ) / 2 ), ( ( pieceSurface->h - ( BLOCK_HEIGHT * 2 ) ) / 2 ), block_surface[ 5 ], pieceSurface );
		
		apply_surface( BLOCK_WIDTH + ( ( pieceSurface->w - ( BLOCK_WIDTH * 3 ) ) / 2 ), BLOCK_HEIGHT + ( ( pieceSurface->h - ( BLOCK_HEIGHT * 2 ) ) / 2 ), block_surface[ 5 ], pieceSurface );
		
		apply_surface( BLOCK_WIDTH * 2 + ( ( pieceSurface->w - ( BLOCK_WIDTH * 3 ) ) / 2 ), BLOCK_HEIGHT + ( ( pieceSurface->h - ( BLOCK_HEIGHT * 2 ) ) / 2 ), block_surface[ 5 ], pieceSurface );
		break;

		case PIECE_TYPE_REVERSES: 
		apply_surface( BLOCK_WIDTH + ( ( pieceSurface->w - ( BLOCK_WIDTH * 3 ) ) / 2 ), ( ( pieceSurface->h - ( BLOCK_HEIGHT * 2 ) ) / 2 ), block_surface[ 6 ], pieceSurface );

		apply_surface( BLOCK_WIDTH * 2 + ( ( pieceSurface->w - ( BLOCK_WIDTH * 3 ) ) / 2 ), ( ( pieceSurface->h - ( BLOCK_HEIGHT * 2 ) ) / 2 ), block_surface[ 6 ], pieceSurface );
		
		apply_surface( ( ( pieceSurface->w - ( BLOCK_WIDTH * 3 ) ) / 2 ), BLOCK_HEIGHT + ( ( pieceSurface->h - ( BLOCK_HEIGHT * 2 ) ) / 2 ), block_surface[ 6 ], pieceSurface );
		
		apply_surface( BLOCK_WIDTH + ( ( pieceSurface->w - ( BLOCK_WIDTH * 3 ) ) / 2 ), BLOCK_HEIGHT + ( ( pieceSurface->h - ( BLOCK_HEIGHT * 2 ) ) / 2 ), block_surface[ 6 ], pieceSurface );
		break;
	}
	
	//apply the piece preview surface to the sceen
	apply_surface( xPiece, yPiece, pieceSurface, surface );
}

/////////////////////////////////////////////////////////
void LazyBlocksPlayer::show_level( SDL_Surface* surface )
/////////////////////////////////////////////////////////
{
    //create a buffer
	char buffer[ 32 ];

    //put the message in the buffer
	sprintf( buffer, "Level:\n%d", lines / 10 );

    //fill the surface
	border_fill_surface( levelSurface, 0, 0xD0D8D0 );

    //apply the text
	largeFont->text_out( 0, 0, levelSurface, buffer, LFONT_VCENTER | LFONT_HCENTER );
	
	//apply the surface
	apply_surface( xLevel, yLevel, levelSurface, surface ); 
}

/////////////////////////////////////////////////////////
void LazyBlocksPlayer::show_lines( SDL_Surface* surface )
/////////////////////////////////////////////////////////
{
    //create a buffer
	char buffer[ 32 ];

    //put the message in the buffer
	sprintf( buffer, "Lines:\n%d", lines );
    
    //fill the surface
	border_fill_surface( linesSurface, 0, 0xD0D8D0 );
	
	//apply the text
	largeFont->text_out( 0, 0, linesSurface, buffer, LFONT_VCENTER | LFONT_HCENTER );
	
	//apply the surface
	apply_surface( xLines, yLines, linesSurface, surface ); 
}

/////////////////////////////////////////////////////////
void LazyBlocksPlayer::show_score( SDL_Surface* surface )
/////////////////////////////////////////////////////////
{
    //create a buffer
    char buffer[ 32 ];

    //put message in buffer
	sprintf( buffer, "Score:%d", score );

    //fill the surface
	border_fill_surface( scoreSurface, 0, 0xD0D8D0 );
	
	//apply the text
	largeFont->text_out( 0, 0, scoreSurface, buffer, LFONT_VCENTER | LFONT_HCENTER );
    
    //apply the surface
    apply_surface( xScore, yScore, scoreSurface, surface );    
}

/////////////////////////////////////
void LazyBlocksPlayer::shatter_rows()
/////////////////////////////////////
{
    //keep track of the number of rows shattered
	int numShattered = 0;
	
	//keep tracks of the rows shattered
    SDL_Rect *rowDrop[ TOTAL_ROWS ];

    //go through the rows
	for( int checkRows = 0; checkRows < TOTAL_ROWS; checkRows++ )
	{
        //the number of blocks touching the rows
		int blockCount = 0;
		
        //the pointers to the blocks in the row
        Block *shattering[ FULL_ROW ];
		
		//go thorugh the block
		for( int checkBlocks = 0; checkBlocks < TOTAL_BLOCKS; checkBlocks++ )
		{
            //if a stationary block is on a row
			if( ( check_overlap( &playerRows[ checkRows ], playerBlocks[ checkBlocks ].get_box( BLOCK_CENTER ) ) == true ) && ( playerBlocks[ checkBlocks ].get_status() == BLOCK_STATIONARY ) )
			{
                //the block to array of blocks
				shattering[ blockCount ] = &playerBlocks[ checkBlocks ];
				
                //up the block count
                blockCount++;
			}
		}
		
		//if we have a full array of blocks
		if( blockCount == FULL_ROW )
		{
            //shatter the blocks in the row
			for( int shatter = 0; shatter < blockCount; shatter++ )
			{
				shattering[ shatter ]->set_status( BLOCK_SHATTERED );
				shattering[ shatter ]->set_frame( 0 );
			}

            //add the row to the array of shattered rows
			rowDrop[ numShattered ] = &playerRows[ checkRows ];
			
            //up the shattered row count
            numShattered++;
		}
		
	}

    //if any rows have been shattered
	if( numShattered > 0 )
	{
        //make a Frames per second timer
		LTimer fps;
		
		//play the proper sound effect
		if( numShattered == 4 )
		{
			Mix_PlayChannel( -1, effects[ EFFECTS_TETRA ], 0 );
		}
		else
		{
			Mix_PlayChannel( -1, effects[ EFFECTS_ROW ], 0 );
		}

        //for one second
		for( int animate = 0; animate < FRAMES_PER_SECOND; animate++ )
		{
            //start the frames per second timer
			fps.start_timer();
			
            //show the blocks
            show_player_blocks( screen );
            update_screen();
			
			//wait
			while( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
			{
			
			}
		}

        //go thorugh the shattered rows
		for( int dropRows = 0; dropRows < numShattered; dropRows++ )
		{
            //go through the blocks
			for( int dropBlocks = 0; dropBlocks < TOTAL_BLOCKS; dropBlocks++ )
			{
                //if the block is above a now shattered row
				if( ( playerBlocks[ dropBlocks ].get_y() < rowDrop[ dropRows ]->y ) && ( playerBlocks[ dropBlocks ].get_status() == BLOCK_STATIONARY ) )
				{
                    //move it down
					playerBlocks[ dropBlocks ].move( 0, BLOCK_HEIGHT );
				}
			}
		}
		
		//play the drop effect
		Mix_PlayChannel( -1, effects[ EFFECTS_DROP ], 0 );
	}
	
	//add the row shattered points
	switch( numShattered )
	{
        case 1: score += 40; break;
        case 2: score += 100; break;
        case 3: score += 300; break;
        case 4: score += 1200; break;    
    }
    
    //if we have gone up a level
    if( ( lines / 10 ) < ( lines + numShattered ) / 10 )
	{
	    Mix_PlayChannel( -1, effects[ EFFECTS_LEVEL_UP ], 0 );
	}
            
    //add the newly shattered rows
	lines += numShattered;
}

///////////////////////////////////
bool LazyBlocksPlayer::over_limit()
///////////////////////////////////
{
    //if a piece is destroyed
    if( playerPiece->destroy_piece() == true )
    {
        //go through the piece blocks
        for( int overLimit = 0;  overLimit < playerPiece->number_of_blocks(); overLimit++ )
        {
            //go through the block set
            for( int overLap = 0; overLap < TOTAL_BLOCKS; overLap++ )
            {    
                //if any of the blocks in the piece over lap a stationary block
                if( ( playerPiece->get_block( overLimit )->get_x() == playerBlocks[ overLap ].get_x()) && ( playerPiece->get_block( overLimit )->get_y() == playerBlocks[ overLap ].get_y() ) && ( playerBlocks[ overLap ].get_status() == BLOCK_STATIONARY ) && ( playerPiece->get_block( overLimit ) != &playerBlocks[ overLap ] ) )
                {
                    return true;    
                }
            }
        }
    }    
    
    //if any stationary blocks are are over the top
	for( int overLimit = 0; overLimit < TOTAL_BLOCKS; overLimit++ )
	{
		if( ( playerBlocks[ overLimit ].get_y() < 0 ) && ( playerBlocks[ overLimit ].get_status() == BLOCK_STATIONARY ) )
		{
			return true;
		}
	}

    //if everything is ok
	return false;
}

//////////////////////////////////////
void LazyBlocksPlayer::get_new_piece()
//////////////////////////////////////
{
    //get a new piece
	switch( nextPiece )
	{
		case PIECE_TYPE_SQUARE: playerPiece = new Square( playerBlocks, keys, lines / 10 ); break;
		case PIECE_TYPE_LINE: playerPiece = new Line( playerBlocks, keys, lines / 10 ); break;
		case PIECE_TYPE_TRIANGLE: playerPiece = new Triangle( playerBlocks, keys, lines / 10 ); break;
		case PIECE_TYPE_FORWARDL: playerPiece = new ForwardL( playerBlocks, keys, lines / 10 ); break;
		case PIECE_TYPE_REVERSEL: playerPiece = new ReverseL( playerBlocks, keys, lines / 10 ); break;
		case PIECE_TYPE_FORWARDS: playerPiece = new ForwardS( playerBlocks, keys, lines / 10 ); break;
		case PIECE_TYPE_REVERSES: playerPiece = new ReverseS( playerBlocks, keys, lines / 10 ); break;
	}

    //set the next piece
    nextPiece = rand() % 7;
}

/////////////////////////////////
int LazyBlocksPlayer::get_score()
/////////////////////////////////
{
    //get the player score
    return score;
}

/////////////////////////////////////////////
SDL_Surface* LazyBlocksPlayer::get_playSurface()
/////////////////////////////////////////////
{
    //the the player's play surface
    return playSurface;
}

////////////////////////////////////////////////////////
void LazyBlocksPlayer::get_playOffsets( int &x, int &y )
////////////////////////////////////////////////////////
{
    //give the play offsets
    x = xPlay;
    y = yPlay;
}
