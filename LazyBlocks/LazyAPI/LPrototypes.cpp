/////////////
class LButton
/////////////
{
    SDL_Rect button;//the range of the background
	SDL_Surface *buttonSurface;//the button graphic
	public:
	LButton( int x, int w, int y, int h );//the the various button attribues
	~LButton();//free the button surface
	bool on_button();//returns true when the given coordinates are within the button
	void show_button( SDL_Surface *thisSurface );//applies the button in given surface
	SDL_Surface *button_surface();//retrieves a pointer to the button's surface
};

///////////
class LFont
///////////
{
	private:
	int x;//text blit offsets 
	int y;
	int w;//with of the space
	int h;//height of the text
	SDL_Surface* font;//the font image
	SDL_Rect textSurfaces[ LFONT_MAX_SURFACES ];//the clipping rect of each character

	public:
    LFont( SDL_Surface* fontImage, SDL_Rect rects[] );//set the font image and clipping
	void test_font( SDL_Surface* surface );//applies the text to a surface for testing
    void text_out( int x, int y, SDL_Surface *thisSurface, string text, unsigned long int flags = 0 );//apply text
	int calc_width( string text, SDL_Surface *surface = NULL );//calculate the width of a single line of text
	SDL_Rect calc_max( string text, SDL_Surface *surface = NULL );//calculate the height and maximum width of a chunk of text
    int get_space();//get the space width
	int get_height();//get the height of the text
};

////////////////
class LStringBox
////////////////
{
	private:
	int x;//location of the StringBox
	int y;
	bool input;//whether the mouse if clicked
	string text;//the string itself
	int maximumLength;//the maximum amount of characters in the string
	int textWidth;//width of the text surface
	int scrollPoint;//at what point to blit the string
    SDL_Surface *backSurface;//the box the text is in
	SDL_Surface *textSurface;//the actual text
	LFont *userFont;//font used for text in the TexBox
	bool shift();//if shift is down
	SDL_Rect *offset;//where to blit the text on the textbox

	public:
	LStringBox( int x, int y, int w, int maxLength, LFont *thisFont, string text = "" );//set location, width, length of the string, font used, and the text
	~LStringBox();
    void enter_text( SDL_Event *thisEvent );//handle key presses
	void show_box( SDL_Surface *surface );//apply stringbox to surface
	void allow_input();//these should explain themselves
	void deny_input();
	void get_text( string newText );//copy argument to box's string
    string get_string();//retrieve the string

};

////////////
class LTimer
////////////
{
	private:
	int start;//point at which the timer was started
	int pTicks;//ticks at the time of pausing
	bool timerPaused;//whether the timer is paused

	public:
	void start_timer();//these should explain themselves
	int get_ticks();
	void pause_timer();
	void resume_timer();
	bool paused();
};

//General utility Functions
SDL_Surface *load_surface( string fileName, Uint32 trans = LTRANS32 );//load an image
void apply_surface( int x, int y, SDL_Surface *thisSurface, SDL_Surface *thatSurface = SDL_GetVideoSurface(), SDL_Rect* clip = NULL );//apply a surface
void clear_surface( SDL_Surface *surface, Uint32 trans = LTRANS32 );//clear a surface
void fill_surface( SDL_Surface *surface, int r, int g, int b );//fill a surface with specified RGB 
void fill_surface( SDL_Surface *surface, Uint32 color );//fill a surface with specified color
void border_fill_surface( SDL_Surface *surface, Uint32 bColor, Uint32 fColor, int border = 1 );//fill surface with a border
void update_screen();//guess...
SDL_Surface *get_new_surface( const int surfacetType, int w, int h );//allocated a new surface
void destroy_surface( SDL_Surface *surface );//free a surface
bool check_overlap( SDL_Rect *A, SDL_Rect *B );//returns true if the rects overlap
SDL_Rect make_rect( int x, int y, int w, int h );//returns a rect with given attributes
