bool quit = false;//This manages the game loop
SDL_Surface *screen;//The screen surface(duh)
SDL_Event event;//The event structure

SDL_Surface* block_surface[ 8 ];
SDL_Surface* titleScreen;
SDL_Surface* introBG;
SDL_Surface* titleBG;
SDL_Surface* playBG;
SDL_Surface* scoreBG;
Mix_Music *music, *titleMusic, *controlMusic, *highscoreMusic, *highscoreTune;

Mix_Chunk *effects[ 10 ];
LFont *largeFont;
