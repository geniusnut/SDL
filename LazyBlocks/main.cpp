#include "LazyAPI/LazyAPI.cpp"
#include "constants.cpp"
#include "prototypes.cpp"
#include "globals.cpp"
#include "block.cpp"
#include "piece.cpp"
#include "LBPlayer.cpp"
#include "fileIO.cpp"

//////////////////////////////////
int main( int argc, char *argv[] )
//////////////////////////////////
{
    //let's just make sure the game starts
	quit = false;
	
	//Open a window
	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE );
	
	//Set the caption
	SDL_WM_SetCaption( DEFAULT_CAPTION, NULL );
	SDL_WM_SetIcon( load_surface( "graphics/icon.bmp" ), NULL );
	    
	//Start the sound
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 1, 4096 );
	
	//Load the files
	load_files();

    bool controllsShown = false;

    //the game loop
	while ( quit == false )
	{
        intro();
	    title();
	    
	    //if the controls have not been shown
	    if( controllsShown == false )
	    {
            //show them
            show_controls();
            
            //and don't show them again
            controllsShown = true;    
        }
        
		play_game();   
	}

    //Show ending credits
	credits();
    
	return 0;
}

////////////////
void play_game()
////////////////
{
    //make a player
    LazyBlocksPlayer player;
    
    //keeps track of the game over
	bool gameOver = false;
	
    //make a Frames per second timer
    LTimer frame;

    //seed random
	srand( SDL_GetTicks() );
    
    //apply the background
    apply_surface( 0, 0, playBG );
    
    //create the border
    int xPBG, yPBG;
    
    player.get_playOffsets( xPBG, yPBG );
    
    SDL_Rect border;
    
    border.x = xPBG - 1;
    border.y = yPBG - 1;
    border.w = player.get_playSurface()->w + 2;
    border.h = player.get_playSurface()->h + 2;
    
    //make the border
    SDL_FillRect( screen, &border, 0 );
    
    //show player data
    player.show_data( screen );
    
    //play the music
    if ( quit == false )
    {
	   Mix_PlayMusic( music, -1 );
    }

    //while the game is in play
	while( ( gameOver == false ) && ( quit == false ) )
	{
        //start the frames per second timer
		frame.start_timer();
		
		//if there's an event to handle
        if( SDL_PollEvent( &event ) )
		{
            //handle player input
            player.handle_events( &event );
			
			//handle quits
			switch( event.type )
			{
				case SDL_KEYDOWN:
                if( event.key.keysym.sym == SDLK_ESCAPE )
                {
                    quit = true;    
                }
				break;

				case SDL_QUIT:
                quit = true;
				break;
			}
		}
		
		//display the blocks
		player.show_player_blocks( screen );
		update_screen();
	    
	    //manage the blocks
        gameOver = player.check_blocks();
		
		//get a new piece if needed
		player.manage_piece();

        //wait to keep the proper frames per second
		while( frame.get_ticks() < ( 1000 / FRAMES_PER_SECOND ) )
		{
		
		}

	}

    //stop the music
    Mix_HaltMusic();
    
	if( quit == false )
	{
        //do the game over animation
		game_over( &player );
		
		//show the high scores
		high_scores( player.get_score() );
	}
	
}

////////////
void intro()
////////////
{
    //make sure to start the intro
	bool endIntro = false;
	
	//a limit timer
	LTimer timer;

    //if the user does not want to quit
    if( quit == false )
    {
        //apply the back ground
        apply_surface( 0, 0, introBG );

        //apply the text
        largeFont->text_out( 0, 0, screen, "Lazy Foo' Productions Presents...", LFONT_HCENTER | LFONT_VCENTER );
        update_screen();
    }

    //start the timer
	timer.start_timer();

    //while the intro is still going
	while( ( endIntro == false ) && ( quit == false ) )
	{
        //if there's events to be handled
		if( SDL_PollEvent( &event ) )
		{
            //if a button was pressed
			if( event.type == SDL_KEYDOWN )
			{
                //if esc was pressed
                if( event.key.keysym.sym == SDLK_ESCAPE )
				{
                    //quit the game
                    quit = true;    
                }
                
                //end the intro
                endIntro = true;
			}
			//if the user Xed out
			if( event.type == SDL_QUIT )
			{
                //quit the game
                quit = true;    
            }
		}
		
		//if time is up
		if( timer.get_ticks() > 2000 )
		{
            //end the intro
            endIntro = true;
        }
	}
}

////////////
void title()
////////////
{
    //make sure to start the title screen
	bool endTitle = false;

    //play the music
    if( quit == false )
    {
	   Mix_PlayMusic( titleMusic, 0 );
    }
    
    //create a message buffer
    char text[ 128 ];
    
    //just a random number I typed
    int num = 305723198;
    
    //add a random number
    num += SDL_GetTicks() % 100;
    
    //put a message in the message buffer
    sprintf( text, "Half assed tetris clone # %d", num );
    
    //if the user hasn't quit
    if( quit == false )
    {
        //apply the back ground
   	    apply_surface( 0, 0, titleBG );
   	    
   	    //apply the message buffer
   	    largeFont->text_out( 0, 50, screen, text, LFONT_HCENTER );
        
        //show the game logo
        apply_surface( ( screen->w - titleScreen->w ) / 2, ( screen->h - titleScreen->h ) / 2, titleScreen );
        
        //show the footer
        largeFont->text_out( 0, 400, screen, "Press enter to begin.", LFONT_HCENTER );
        
        //update the screen
	    update_screen();
    }

    //while the title screen is going
	while( ( endTitle == false ) && ( quit == false ) )
	{
        //if there's an event on queue
		if( SDL_PollEvent( &event ) )
		{
            //if a key is pressed
            if( event.type == SDL_KEYDOWN )
			{
                //if escape is pressed
                if( event.key.keysym.sym == SDLK_ESCAPE )
                {
                    //quit
                    quit = true;
                }
                //if return was pressed
                else if( event.key.keysym.sym == SDLK_RETURN )
                {
                    //end the title loop
                    endTitle = true;
                }
            }
            //if the user Xed out
			else if( event.type == SDL_QUIT )
			{
                //quit
                quit = true;    
            }
		}
	}
	
	//stop the music
	Mix_HaltMusic();
}

////////////////////
void show_controls()
////////////////////
{
    //remember to show the controls
	bool endControls = false;
	
	//
	LTimer timer;

    if( quit == false )
    {
        
        apply_surface( 0, 0, introBG );
        
        largeFont->text_out( 0, 0, screen, "Controls:\nLeft: move left\nRight: move right\nDown: move down\nX: rotate clockwise\nZ: rotate counterclockwise\nUp: quick rotate", LFONT_HCENTER | LFONT_VCENTER );
        update_screen();
        Mix_PlayMusic( controlMusic, -1 );
    }

    //start the timer
	timer.start_timer();

    //while the control display is on
	while( ( endControls == false ) && ( quit == false ) )
	{
        //if there's an event to be handled
		if( SDL_PollEvent( &event ) )
		{
            //if a key is pressed
			if( event.type == SDL_KEYDOWN )
			{
                //if esc was pressed
                if( event.key.keysym.sym == SDLK_ESCAPE )
				{
                    //quit
                    quit = true;    
                }
                
                //end the control display
				endControls = true;
			}
			//if the user Xed out
			if( event.type == SDL_QUIT )
			{
                //quit
                quit = true;    
            }
		}
		
		//if time is up
		if( timer.get_ticks() > 5000 )
		{
            //end the control display
            endControls = true;
        }
	}
	
	//stop the music
	Mix_HaltMusic();
}

/////////////////////////////////
void high_scores( int thisScore )
/////////////////////////////////
{
    //the highscores themselves
	int highScores[ 10 ] = { 10000, 9000, 8000, 7000, 6000, 5000, 4000, 3000, 2000, 1000 };
	
    //the record names
    string names[ 10 ] = { "ABC", "EFG", "HIJ", "KLM", "NOP", "QRS", "TUV", "WXY", "ZZZ", "#*(" }; 

    //keeps track where the new score is
	int newScore = -1;

    //make sure to show the scores
	bool exit = false;

	//load the scores file
	ifstream loadScores( "high_scores.ini" );

    //if the file was found
	if( loadScores != NULL )
	{
        //while the 10 entries need to be entered
		for( int load = 0; load < 10; load++ )
		{
            //read the score
			loadScores >> highScores[ load ];
			
			//read the name
			getline( loadScores, names[ load ] );
			getline( loadScores, names[ load ] );
		}

        //close the high score file
		loadScores.close();
	}

	//while we haven't found a place for the new score
	for( int check = 0; ( check < 10 ) && ( newScore < 0 ); check++ )
	{
        //if the new score is greater than any of thr scores
		if( thisScore > highScores[ check ] )
		{
            //remember what position the new score is in
			newScore = check;

            //go thorugh the scores
			for( int shift = 0; shift < 10; shift++ )
			{
                //if the score is less than the new score, and if not out of the array bounds
				if( ( highScores[ 9 - shift ] < thisScore ) && ( ( 9 - shift ) - 1 >= 0 ) )
				{
                    //push back the score and name
					highScores[ 9 - shift ] = highScores[ ( 9 - shift ) - 1 ];
					names[ 9 - shift ] = names[ ( 9 - shift ) - 1 ];
				}
			}

            //insert the score
			highScores[ check ] = thisScore;
		}
	}

	//if a new high score was made
	if( newScore >= 0 )
	{
        //play the music
        if( quit == false )
        {
	       Mix_PlayMusic( highscoreMusic, -1 );
        }
        
        //remember to enter the score
		bool scoreEntered = false;

        //create a string box
		LStringBox enterScore( ( screen->w - 80 ) / 2, 100, 80, 3, largeFont );

        //apply the backgorund
		apply_surface( 0, 0, scoreBG );
		
		//apply the text
		largeFont->text_out( 0, 10, screen, "New High Score!", LFONT_HCENTER );
		largeFont->text_out( 0, 400, screen, "Press Enter to Input Score", LFONT_HCENTER );
		
        //allow input on the string box
        enterScore.allow_input();
		
		//while the score hasn't been entered
		while( ( scoreEntered == false ) && ( quit == false ) )
		{
            //if there's an event to be handled
			if( SDL_PollEvent( &event ) )
			{
                //pass the events to the string box
				enterScore.enter_text( &event );

                //if the user pressed enter
                if( ( event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_RETURN ) )
				{
                    //the score has been entered
                    scoreEntered = true;
                }
                //if the user wants to quit
                else if( event.type == SDL_QUIT )
                {
                    //quit
                    quit = true;
                }
			}
			
			//score the box
			enterScore.show_box( screen );
			
            //update the screen
            update_screen();
		}

        //get the new name
		names[ newScore ] = enterScore.get_string().c_str();
		
		//stop the music
		Mix_HaltMusic();
	}
	
	//apply the background
	apply_surface( 0, 0, scoreBG );
	
    //create a message buffer
    char m[ 128 ];

    //fill the buffer with the names and scores
	sprintf( m, "High Scores:\n%d : %s\n%d : %s\n%d : %s\n%d : %s\n%d : %s\n%d : %s\n%d : %s\n%d : %s\n%d : %s\n%d : %s\n\nPress Any Key To Continue", highScores[ 0 ], names[ 0 ].c_str(), highScores[ 1 ], names[ 1 ].c_str(), highScores[ 2 ], names[ 2 ].c_str(), highScores[ 3 ], names[ 3 ].c_str(), highScores[ 4 ], names[ 4 ].c_str(), highScores[ 5 ], names[ 5 ].c_str(), highScores[ 6 ], names[ 6 ].c_str(), highScores[ 7 ], names[ 7 ].c_str(), highScores[ 8 ], names[ 8 ].c_str(), highScores[ 9 ], names[ 9 ].c_str() );
	
    //apply the message
    largeFont->text_out( 0, 0, screen, m, LFONT_HCENTER | LFONT_VCENTER );
	
    //update the screen
    update_screen();

    //play the tune
    if( quit == false )
    {
	    Mix_PlayMusic( highscoreTune, 0 );
    }
    
    //while the user wants to see the scores
	while( ( exit == false ) && ( quit == false ) )
	{
        //if there's an event to be handled
		if( SDL_PollEvent( &event ) )
		{
			switch( event.type )
			{
                //if a key is pressed
				case SDL_KEYDOWN:
                    
                //exit the score screen
				exit = true;
				
				//if esc was pressed
				if( event.key.keysym.sym == SDLK_ESCAPE )
				{
                    //quit
                    quit = true;    
                }
				break;
				
				//if the user Xed out
				case SDL_QUIT:
                //quit
                quit = true;
				break;
			}
		}
	}

	
	//open the score file
	ofstream saveScores( "high_scores.ini" );

    //go through the score and names
	for( int save = 0; save < 10; save++ )
	{
        //and save them to the file
		saveScores << highScores[ save ] << endl << names[ save ] << endl;
	}
	
}

//////////////////////////////////////////
void game_over( LazyBlocksPlayer* player )
//////////////////////////////////////////
{
    //a frames per second keeper
	LTimer timer;

    //get the offet of the play surface
    int x = 0, y = 0;
    player->get_playOffsets( x, y );
    
    //play the over limit effect
	Mix_PlayChannel( -1, effects[ EFFECTS_OVER_LIMIT ], 0 );
    
    //go through the rows
	for( int grey = 0; grey < TOTAL_ROWS; grey++ )
	{
        //start the animation timer
		timer.start_timer();

        //fill the current row with grey blocks
		for( int fillRow = 0; fillRow < FULL_ROW; fillRow++ )
		{
			apply_surface( BLOCK_WIDTH * fillRow, BLOCK_HEIGHT * grey, block_surface[ 7 ], player->get_playSurface() );
		}

        //if we filled the last row
		if ( grey == ( TOTAL_ROWS - 1 ) )
		{
            //play the game over music
			Mix_PlayChannel( -1, effects[ EFFECTS_TRYAGAIN ], 0 );
			
            //display the message
            largeFont->text_out( 0, 0, player->get_playSurface(), "Game Over\nTry Again!", LFONT_VCENTER | LFONT_HCENTER );
		}

        //apply the play surface
		apply_surface( x, y, player->get_playSurface() );

        //update the screen
		update_screen();

        //wait
		while( timer.get_ticks() < ( 1000 / FRAMES_PER_SECOND ) )
		{
		
		}

	}

    //wait 2 seconds
	SDL_Delay( 2000 );
}

//////////////
void credits()
//////////////
{
    //basic loop maanger
	bool endCredits = false;
	
    //fill the screen
	fill_surface( screen, 0xD0, 0xD8, 0xD0 );

    //apply the text
	largeFont->text_out( 0, 0, screen, "Credits:\n\nPretty much everything:\nSal Llamas\n\nOriginal Concept:\nAlexey Pazhitnov\n\nSound:\nNintendo, Capcom\nPlease don\'t sue me", LFONT_HCENTER | LFONT_VCENTER );
	
    //update the screen
    update_screen();

    //start the timer
    LTimer timer;
	timer.start_timer();

    //while the credits aren't over
	while( endCredits == false )
	{
        //if there's an event to handle
		if( SDL_PollEvent( &event ) )
		{
            //if the user Xed out or quit
			if( ( event.type == SDL_QUIT ) || ( event.type == SDL_KEYDOWN ) )
			{
                //end the credits
				endCredits = true;
			}
		}
		
		//if time is up
		if( timer.get_ticks() > 10000 )
		{
            //end the credits
			endCredits = true;
		}
	}
}
