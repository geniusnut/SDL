///////////
class Block
///////////
{
	private:
	void set();//set the collision boxes
	char status;//blcok status
	int frame;//current frame of animation
	SDL_Surface *surface;//the surface
	SDL_Rect box[ 5 ];//the collsion boxes
	public:
    Block();//variable initialization
    void move( int x, int y );//shift the block
	void move_to( int x, int y );//move the block to a specific location
	int get_y();//returns offsets
	int get_x();
    void set_surface( SDL_Surface* surface );
    SDL_Surface *get_surface();
    void set_status( char status );
    char get_status();
    void set_frame( int frame );
    int get_frame();
    SDL_Rect* get_box( int thisBox );//gets a collision box from the block
};

Block *get_new_Block( Block* theseBlocks );//gets an unused block from array of blocks
bool Block_out_of_bounds( Block *thisBlock, Block* theseBlocks );//checks if a block is out fo bounds
bool touches_stationary_block( SDL_Rect *box, Block* theseBlocks );//checks if a box collides with a block from array of blocks

//piece.cpp
///////////
class Piece
///////////
{
	private:
	protected:
	int x, y;//the offsets
    bool destroy;//whether to get a new piece
    SDLKey *playerKeys;//the player's keys
    Block *blockSet;//the player's array of blocks
	Block *theseBlocks[ 32 ];//pointers to the blocks used by the piece
	int numBlocks;//the number of block the piece has
	
    public:
    Piece();
	virtual void handle_input( SDL_Event * thisEvent ){}//handles events
	virtual void on_frame( SDL_Surface *playArea ){}//procedures done on the frame
	virtual int get_destruction_points(){ return 0; }//point gotten when the piece is destroyed
	bool destroy_piece();//checks whether the piece needs to be destroyed
	int number_of_blocks();//number of blocks the piece has
	Block* get_block( int block );//gets a block from the piece's array of blocks
};

///////////////////////////////
class BasicPiece : public Piece
///////////////////////////////
{
    protected:
	bool down, left, right;//directions the piece is moving in
	int direction;//how far its gone left or right
    int rotationStatus;//how its rotated
    int dropRate;//how mony milliseconds the piece waits before dropping again
    int dropPoint;//at what y offset the user started moving the piece down
	LTimer timer;//what keeps track of the piece's automatic dropping
	
    public:
    BasicPiece( int level );
    //moves the block
	void move_down();
	void move_left();
	void move_right();
	
	void handle_input( SDL_Event *thisEvent );
	void on_frame( SDL_Surface *playArea );
	int get_destruction_points();
	
    //rotates the blocks in the piece
    virtual void rotate_cw(){};
	virtual void rotate_ccw(){};
};

////////////////////////////////
class Square : public BasicPiece
////////////////////////////////
{ 
	public:
	Square( Block* playerBlocks, SDLKey *keys, int level );//gets the player's block, keys, and level
};

//////////////////////////////
class Line : public BasicPiece
//////////////////////////////
{ 
	public:
	Line( Block* playerBlocks, SDLKey *keys, int level );//same as above
	void rotate_cw();//rotates clockwise
	void rotate_ccw();//rotate counter clockwise
	void rotate();//manages rotation
};

/////////////////////////////
class Triangle : public BasicPiece
/////////////////////////////
{ 
	public:
    //same as above
	Triangle( Block* playerBlocks, SDLKey *keys, int level );
	void rotate_cw();
	void rotate_ccw();
	void rotate();
};

/////////////////////////////
class ForwardL : public BasicPiece
/////////////////////////////
{
	public:
    //same as above
	ForwardL( Block* playerBlocks, SDLKey *keys, int level );
	void rotate_cw();
	void rotate_ccw();
	void rotate();
};

/////////////////////////////
class ReverseL : public BasicPiece
/////////////////////////////
{ 
	public:
    //same as above
	ReverseL( Block* playerBlocks, SDLKey *keys, int level );
	void rotate_cw();
	void rotate_ccw();
	void rotate();
};

/////////////////////////////
class ForwardS : public BasicPiece
/////////////////////////////
{ 
	public:
    //same as above
	ForwardS( Block* playerBlocks, SDLKey *keys, int level );
	void rotate_cw();
	void rotate_ccw();
	void rotate();
};

/////////////////////////////
class ReverseS : public BasicPiece
/////////////////////////////
{
	public:
    //same as above
	ReverseS( Block* playerBlocks, SDLKey *keys, int level );
	void rotate_cw();
	void rotate_ccw();
	void rotate();
};

//////////////////////
class LazyBlocksPlayer
//////////////////////
{
    private:
    int lines;//number of lines the player has made
    int score;//the player's score
    int nextPiece;//the next piece
    
    int xPlay, yPlay;//offsets of the play surface
    SDL_Surface* playSurface;//the play surface
    
    int xPiece, yPiece;//the offsets of the next piece preview
    SDL_Surface* pieceSurface;//the piece preview surface
    
    int xLines, yLines;//the offsets of the line counter
    SDL_Surface* linesSurface;//the surface of the line counter
    
    int xLevel, yLevel;//the offsets of the level indicator
    SDL_Surface* levelSurface;//the surface of the level indicator
    
    int xScore, yScore;//score keeper offsets
    SDL_Surface* scoreSurface;//the score keeper surface
    
    Block playerBlocks[ TOTAL_BLOCKS ];//the player's block set
    SDL_Rect playerRows[ TOTAL_ROWS ];// the player's row set
    SDLKey keys[ LBKEY_TOTALKEYS ];//the player's key configuration
    Piece *playerPiece;//the player's piece
    
    public: 
    //ehh... I'm sick of commenting for tonight, these shouldn't be hard to figure out
    LazyBlocksPlayer();
    ~LazyBlocksPlayer();
    void handle_events( SDL_Event *event );
    void show_data( SDL_Surface* surface );
    void show_player_blocks( SDL_Surface* surface );
    void manage_piece();
    bool check_blocks();
    
    void show_next_piece( SDL_Surface* surface );
    void show_level( SDL_Surface* surface );
    void show_lines( SDL_Surface* surface );
    void show_score( SDL_Surface* surface );
    void get_new_piece();
    void shatter_rows();
    bool over_limit();
    
    int get_score();
    SDL_Surface* get_playSurface();
    void get_playOffsets( int &x, int &y );
};

//fileIO.cpp
//these should be self explanatory
void load_files();
void load_large_text();
void load_graphics();
void load_audio();

//main.cpp
//these should explain themselves too
void intro();
void title();
void show_controls();
void play_game();
void game_over( LazyBlocksPlayer* player );
void high_scores( int thisScore );
void credits();
