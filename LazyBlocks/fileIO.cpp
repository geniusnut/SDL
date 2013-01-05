/////////////////
void load_files()
/////////////////
{
    //load the text
	load_large_text();
	
	//load the graphics
	load_graphics();
	
	//load the audio
	load_audio();
}

//////////////////////
void load_large_text()
//////////////////////
{
    //load the font image
    SDL_Surface* fontImage = load_surface( "graphics/largefont.png" );
    
    //make an array of clip rects
    SDL_Rect text[ LFONT_MAX_SURFACES ];
    
    //carve out the text
	text[ LFONT_A ] = make_rect( 1, 1, 18 - 0, 30 );
    text[ LFONT_B ] = make_rect( 20, 1, 37 - 19, 30 );
	text[ LFONT_C ] = make_rect( 39, 1, 54 - 38, 30 );
	text[ LFONT_D ] = make_rect( 56, 1, 73 - 55, 30 );
	text[ LFONT_E ] = make_rect( 75, 1, 90 - 74, 30 );
	text[ LFONT_F ] = make_rect( 92, 1, 107 - 91, 30 );
	text[ LFONT_G ] = make_rect( 109, 1, 126 - 108, 30 );
	text[ LFONT_H ] = make_rect( 128, 1, 145 - 127, 30 );
	text[ LFONT_I ] = make_rect( 147, 1, 152 - 146, 30 );
	text[ LFONT_J ] = make_rect( 154, 1, 167 - 153, 30 );
	text[ LFONT_K ] = make_rect( 169, 1, 186 - 168, 30 );
	text[ LFONT_L ] = make_rect( 188, 1, 203 - 187, 30 );
	text[ LFONT_M ] = make_rect( 205, 1, 226 - 204, 30 );

	text[ LFONT_N ] = make_rect( 1, 32, 18 - 0, 30 );
	text[ LFONT_O ] = make_rect( 20, 32, 37 - 19, 30 );
	text[ LFONT_P ] = make_rect( 39, 32, 56 - 38, 30 );
	text[ LFONT_Q ] = make_rect( 58, 32, 75 - 57, 30 );
	text[ LFONT_R ] = make_rect( 77, 32, 96 - 76, 30 );
	text[ LFONT_S ] = make_rect( 98, 32, 113 - 97, 30 );
	text[ LFONT_T ] = make_rect( 115, 32, 132 - 114, 30 );
	text[ LFONT_U ] = make_rect( 134, 32, 151 - 133, 30 );
	text[ LFONT_V ] = make_rect( 153, 32, 170 - 152, 30 );
	text[ LFONT_W ] = make_rect( 172, 32, 203 - 171, 30 );
	text[ LFONT_X ] = make_rect( 205, 32, 224 - 204, 30 );
	text[ LFONT_Y ] = make_rect( 226, 32, 247 - 225, 30 );
	text[ LFONT_Z ] = make_rect( 249, 32, 268 - 248, 30 );
	
	text[ LFONT_a ] = make_rect( 1, 63, 14 - 0, 30 );
	text[ LFONT_b ] = make_rect( 16, 63, 29 - 15, 30 );
	text[ LFONT_c ] = make_rect( 31, 63, 44 - 30, 30 );
	text[ LFONT_d ] = make_rect( 46, 63, 59 - 45, 30 );
	text[ LFONT_e ] = make_rect( 61, 63, 74 - 60, 30 );
	text[ LFONT_f ] = make_rect( 76, 63, 85 - 75, 30 );
	text[ LFONT_g ] = make_rect( 87, 63, 100 - 86, 30 );
	text[ LFONT_h ] = make_rect( 102, 63, 115 - 101, 30 );
	text[ LFONT_i ] = make_rect( 117, 63, 122 - 116, 30 );
	text[ LFONT_j ] = make_rect( 124, 63, 131 - 123, 30 );
	text[ LFONT_k ] = make_rect( 133, 63, 146 - 132, 30 );
	text[ LFONT_l ] = make_rect( 148, 63, 153 - 147, 30 );
	text[ LFONT_m ] = make_rect( 155, 63, 176 - 154, 30 );
	
	text[ LFONT_n ] = make_rect( 1, 94, 14 - 0, 30 );
	text[ LFONT_o ] = make_rect( 16, 94, 29 - 15, 30 );
	text[ LFONT_p ] = make_rect( 31, 94, 44 - 30, 30 );
	text[ LFONT_q ] = make_rect( 46, 94, 59 - 45, 30 );
	text[ LFONT_r ] = make_rect( 61, 94, 70 - 60, 30 );
	text[ LFONT_s ] = make_rect( 72, 94, 85 - 71, 30 );
	text[ LFONT_t ] = make_rect( 87, 94, 96 - 86, 30 );
	text[ LFONT_u ] = make_rect( 98, 94, 111 - 97, 30 );
	text[ LFONT_v ] = make_rect( 113, 94, 130 - 112, 30 );
	text[ LFONT_w ] = make_rect( 132, 94, 153 - 131, 30 );
	text[ LFONT_x ] = make_rect( 155, 94, 172 - 154, 30 );
	text[ LFONT_y ] = make_rect( 174, 94, 191 - 173, 30 );
	text[ LFONT_z ] = make_rect( 193, 94, 206 - 192, 30 );

	text[ LFONT_0 ] = make_rect( 1, 125, 14 - 0, 30 );
	text[ LFONT_1 ] = make_rect( 16, 125, 25 - 15, 30 );
	text[ LFONT_2 ] = make_rect( 27, 125, 40 - 26, 30 );
	text[ LFONT_3 ] = make_rect( 42, 125, 55 - 41, 30 );
	text[ LFONT_4 ] = make_rect( 57, 125, 70 - 56, 30 );
	text[ LFONT_5 ] = make_rect( 72, 125, 85 - 71, 30 );
	text[ LFONT_6 ] = make_rect( 87, 125, 100 - 86, 30 );
	text[ LFONT_7 ] = make_rect( 102, 125, 115 - 101, 30 );
	text[ LFONT_8 ] = make_rect( 117, 125, 130 - 116, 30 );
	text[ LFONT_9 ] = make_rect( 132, 125, 145 - 131, 30 );
	
	text[ LFONT_EXCLAIM ] = make_rect( 1, 156, 6 - 0, 30 );
	text[ LFONT_AT ] = make_rect( 8, 156, 33 - 7, 30 );
	text[ LFONT_HASH ] = make_rect( 35, 156, 52 - 34, 30 );
	text[ LFONT_DOLLAR ] = make_rect( 54, 156, 67 - 53, 30 );
	text[ LFONT_PERCENT ] = make_rect( 69, 156, 92 - 68, 30 );
	text[ LFONT_CARET ] = make_rect( 94, 156, 105 - 93, 30 );
	text[ LFONT_AMPERSAND ] = make_rect( 107, 156, 122 - 106, 30 );
	text[ LFONT_ASTERISK ] = make_rect( 124, 156, 137 - 123, 30 );
	text[ LFONT_LEFTPAREN ] = make_rect( 139, 156, 146 - 138, 30 );
	text[ LFONT_RIGHTPAREN ] = make_rect( 148, 156, 155 - 147, 30 );
	
	text[ LFONT_MINUS ] = make_rect( 1, 187, 10 - 0, 30 );
	text[ LFONT_UNDERSCORE ] = make_rect( 12, 187, 29 - 11, 30 );
	text[ LFONT_EQUALS ] = make_rect( 31, 187, 44 - 30, 30 );
	text[ LFONT_PLUS ] = make_rect( 46, 187, 59 - 45, 30 );
	text[ LFONT_LEFTBRACKET ] = make_rect( 61, 187, 68 - 60, 30 );
	text[ LFONT_RIGHTBRACKET ] = make_rect( 70, 187, 77 - 69, 30 );
	text[ LFONT_LEFTBRACE ] = make_rect( 79, 187, 88 - 78, 30 );
	text[ LFONT_RIGHTBRACE ] = make_rect( 90, 187, 99 - 89, 30 );
	text[ LFONT_SEMICOLON ] = make_rect( 101, 187, 108 - 100, 30 );
	text[ LFONT_COLON ] = make_rect( 110, 187, 115 - 109, 30 );
	text[ LFONT_QUOTE ] = make_rect( 117, 187, 122 - 116, 30 );
	text[ LFONT_DBLQUOTE ] = make_rect( 124, 187, 137 - 123, 30 );
	text[ LFONT_COMMA ] = make_rect( 139, 187, 146 - 138, 30 );
	text[ LFONT_PERIOD ] = make_rect( 148, 187, 153 - 147, 30 );
	text[ LFONT_LESS ] = make_rect( 155, 187, 168 - 154, 30 );
	text[ LFONT_GREATER ] = make_rect( 170, 187, 183 - 169, 30 );
	text[ LFONT_QUESTION ] = make_rect( 185, 187, 198 - 184, 30 );
	text[ LFONT_SLASH ] = make_rect( 200, 187, 209 - 199, 30 );
	text[ LFONT_LINE ] = make_rect( 211, 187, 216 - 210, 30 );
	text[ LFONT_BACKSLASH ] = make_rect( 218, 187, 227 - 217, 30 );
	text[ LFONT_BACKQUOTE ] = make_rect( 229, 187, 238 - 228, 30 );
	text[ LFONT_TILDE ] = make_rect( 240, 187, 251 - 239, 30 );
	//Yes I realize there was a far easier way of doing thise, but I realized that after I finished this
	
	//make the font
	largeFont = new LFont( fontImage, text );
}

////////////////////
void load_graphics()
////////////////////
{
    //load the block surfaces
	block_surface[ 0 ] = load_surface( "graphics/CRYSTAL.png" );
	block_surface[ 1 ] = load_surface( "graphics/RED.png" );
	block_surface[ 2 ] = load_surface( "graphics/YELLOW.png" );
	block_surface[ 3 ] = load_surface( "graphics/GREEN.png" );
	block_surface[ 4 ] = load_surface( "graphics/BLUE.png" );
	block_surface[ 5 ] = load_surface( "graphics/PURPLE.png" );
	block_surface[ 6 ] = load_surface( "graphics/WHITE.png" );
	block_surface[ 7 ] = load_surface( "graphics/DESAT.png" );
	
	//load the lazy block logo
	titleScreen = load_surface( "graphics/title.png" );
	
	//load the back grounds
    introBG = load_surface( "graphics/intro_back.png" );
    titleBG = load_surface( "graphics/title_back.png" );
    playBG = load_surface( "graphics/play_back.png" );
    scoreBG = load_surface( "graphics/score_back.png" );
}

/////////////////
void load_audio()
/////////////////
{
    //load the sound effects
	effects[ EFFECTS_CRASH ] = Mix_LoadWAV( "audio/crash.wav" );
	effects[ EFFECTS_DROP ] = Mix_LoadWAV( "audio/drop.wav" );
	effects[ EFFECTS_OVER_LIMIT ] = Mix_LoadWAV( "audio/overlimit.wav" );
	effects[ EFFECTS_ROTATION ] = Mix_LoadWAV( "audio/rotation.wav" );
	effects[ EFFECTS_ROW ] = Mix_LoadWAV( "audio/row.wav" );
	effects[ EFFECTS_SHIFT ] = Mix_LoadWAV( "audio/shift.wav" );
	effects[ EFFECTS_TETRA ] = Mix_LoadWAV( "audio/tetra.wav" );
	effects[ EFFECTS_TRYAGAIN ] = Mix_LoadWAV( "audio/tryagain.wav" );
	effects[ EFFECTS_LEVEL_UP ] = Mix_LoadWAV( "audio/levelup.wav" );
	effects[ EFFECTS_PAUSE ] = Mix_LoadWAV( "audio/pause.wav" );

    //load the music
    titleMusic = Mix_LoadMUS( "audio/intro.ogg" );
	music = Mix_LoadMUS( "audio/music.ogg" );
	controlMusic = Mix_LoadMUS( "audio/controls.ogg" );
	highscoreMusic = Mix_LoadMUS( "audio/highscore.ogg" );
	highscoreTune = Mix_LoadMUS( "audio/scoreDisplay.ogg" );
}
