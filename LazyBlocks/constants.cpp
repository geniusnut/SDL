//Some Video Constants
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FRAMES_PER_SECOND 20
#define DEFAULT_CAPTION "Lazy Blocks"

//Block Dimensions
#define BLOCK_WIDTH 20
#define BLOCK_HEIGHT 20

//Labels for the LRect Arrays
#define BLOCK_CENTER 0
#define BLOCK_TOP 1
#define BLOCK_BOTTOM 2
#define BLOCK_LEFT 3
#define BLOCK_RIGHT 4

//Blocks status labels
#define BLOCK_IN_PLAY 'I'
#define BLOCK_STATIONARY 'S'
#define BLOCK_OUT_OF_PLAY 'O'
#define BLOCK_SHATTERED 's'

//Block/Row Constants
#define TOTAL_BLOCKS 200
#define FULL_ROW 10
#define TOTAL_ROWS 20

//Piece Types
#define PIECE_TYPE_SQUARE 0
#define PIECE_TYPE_TRIANGLE 1
#define PIECE_TYPE_LINE 2
#define PIECE_TYPE_FORWARDL 3
#define PIECE_TYPE_REVERSEL 4
#define PIECE_TYPE_FORWARDS 5
#define PIECE_TYPE_REVERSES 6
#define PIECE_TYPE_TYPES 7

//Sound effect labels
#define EFFECTS_CRASH 0
#define EFFECTS_DROP 1
#define EFFECTS_OVER_LIMIT 2
#define EFFECTS_ROTATION 3
#define EFFECTS_ROW 4
#define EFFECTS_SHIFT 5
#define EFFECTS_TETRA 6
#define EFFECTS_TRYAGAIN 7
#define EFFECTS_LEVEL_UP 8
#define EFFECTS_PAUSE 9

//Key Index Constants
#define LBKEY_UP 0
#define LBKEY_DOWN 1
#define LBKEY_LEFT 2
#define LBKEY_RIGHT 3
#define LBKEY_ACTION_1 4
#define LBKEY_ACTION_2 5
#define LBKEY_PAUSE 6
#define LBKEY_TOTALKEYS 7

//Default Keys
#define DEFAULT_UP SDLK_UP
#define DEFAULT_DOWN SDLK_DOWN
#define DEFAULT_LEFT SDLK_LEFT
#define DEFAULT_RIGHT SDLK_RIGHT
#define DEFAULT_ACTION_1 SDLK_z
#define DEFAULT_ACTION_2 SDLK_x
#define DEFAULT_PAUSE SDLK_RETURN
