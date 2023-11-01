#include <stdio.h>
#include "MacUILib.h"

// PPA2 GOAL: 
//  Construct the game backbone where the player can control an object to move freely in the game board area with border wraparound behavior.

// Watch Briefing Video and Read Lab Manual before starting on the activity!

// PREPROCESSOR CONSTANTS DEFINITION HERE
/////////////////////////////////////////
#define BOARD_WIDTH 20
#define BOARD_LENGTH 10
#define BORDER_CHAR '#'
#define EMPTY_CHAR ' '


// GLOBAL VARIABLE DEFINITION HERE
/////////////////////////////////////////
int exitFlag; // Program Exiting Flag - old stuff
int gameSpeed= 100000;
int gameSpeedLev= 1;

// For storing the user input - from PPA1
char input;

// [TODO] : Define objPos structure here as described in the lab document

struct objPos
{
    int x;        // x-coordinate of an object
    int y;        // y-coordinate of an object
    char symbol;  // The ASCII symbol of the object to be drawn on the screen
};

struct objPos PlayerPos;

// [TODO] : Define the Direction enumeration here as described in the lab document
//          This will be the key ingredient to construct a simple Finite State Machine
//          For our console game backbone.

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

enum Direction direction;  // Direction of the player

// FUNCTION PROTOTYPING DEFINITION HERE
/////////////////////////////////////////
void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

// You may insert additional helper function prototypes below.
// 
// As a good practice, always insert prototype before main() and implementation after main()
// For ease of code management.



// MAIN PROGRAM LOOP
/////////////////////////////////////////
// This part should be intuitive by now.
// DO NOT TOUCH

int main(void)
{
    // Initialize the program
    Initialize();

    // Main game loop
    while (!exitFlag)  
    {
        // Get user input
        GetInput();

        // Run game logic
        RunLogic();

        // Draw the game screen
        DrawScreen();

        // Add a delay for controlling game speed
        LoopDelay();
    }

    // Cleanup before exiting
    CleanUp();
}


// INITIALIZATION ROUTINE
/////////////////////////////////////////
void Initialize(void)
{
    // Initialize the MacUILib
    MacUILib_init();
    MacUILib_clearScreen();

    // Initialize variables
    input = 0; // NULL
    exitFlag = 0;  // not exiting    
   
    // Initialize player object at the center of the game board at the beginning of the game
    PlayerPos.x = BOARD_WIDTH / 2; // x position midway
    PlayerPos.y = BOARD_LENGTH / 2; // Y position midway 
    PlayerPos.symbol = '@';

    direction = LEFT;
}


// INPUT PROCESSING ROUTINE
/////////////////////////////////////////
void GetInput(void)
{
    // Implement Asynchronous Input - non-blocking character read-in    
    if (MacUILib_hasChar()) {
        input = MacUILib_getChar();
    }
}



// PROGRAM LOGIC ROUTINE
/////////////////////////////////////////
void RunLogic(void)
{
    // Process the input by mapping WASD to the corresponding change in player object movement direction

    if (input != 0)  // if not null character
    {
        switch (input)
        {                      
            case ' ':  // exit using space bar
                exitFlag = 1;
                break;
            
            case 'D':
                if (direction!=LEFT)
                    direction = RIGHT; // 'D' key moves to the right
                    
                break;

            case 'A':
                if (direction!= RIGHT)
                    direction = LEFT; // 'A' key moves to the left 
                break;

            case 'W':
                if(direction!= DOWN)
                   direction = UP; // 'W' key moves up
                break;

            case 'S':
                if(direction!=UP)
                   direction = DOWN; // 'S' key moves down
                break;

            case '1':
                gameSpeed = 100000;
                gameSpeedLev = 1;
                break;

            case '2':
                gameSpeed = 40000;
                gameSpeedLev = 2;
                break;

            case '3':
                gameSpeed = 30000;
                gameSpeedLev = 3;
                break;

            case '4':
                gameSpeed = 20000;
                gameSpeedLev = 4;
                break;

            case '5':
                gameSpeed = 10000;
                gameSpeedLev = 5;
                break;
            default:
                break;    
        }
        input = 0;
    }

    // Update the player's location by 1 unit in the direction stored in the program
    // Heed the border wraparound
    switch (direction)
    {
        case UP:
            PlayerPos.y = (PlayerPos.y - 1 + BOARD_LENGTH) % BOARD_LENGTH;
            MacUILib_printf("\n");

            printf("Player Direction: UP");

            break;

        case DOWN:
            PlayerPos.y = (PlayerPos.y + 1) % BOARD_LENGTH;
            MacUILib_printf("\n");
            printf("Player Direction: DOWN");

            break;

        case LEFT:
            PlayerPos.x = (PlayerPos.x - 1 + BOARD_WIDTH) % BOARD_WIDTH;
            MacUILib_printf("\n");
            printf("Player Direction: LEFT");

            break;

        case RIGHT:
            PlayerPos.x = (PlayerPos.x + 1) % BOARD_WIDTH;
            MacUILib_printf("\n");
            printf("Player Direction: RIGHT");

            break;

        default:
            break;
    }
}


// SCREEN DRAWING ROUTINE
/////////////////////////////////////////
void DrawScreen(void)
{
    // Clear the current screen contents
    MacUILib_clearScreen();

    // Draw the game board and player object
    int y;
    for (y = 0; y < BOARD_LENGTH; y++) {
        int x;
        for (x = 0; x < BOARD_WIDTH; x++) {
            if (y == 0 || y == (BOARD_LENGTH - 1) || x == 0 || x == (BOARD_WIDTH - 1)) {
                // Draw the border
                MacUILib_printf("%c", BORDER_CHAR);
            } else if (x == PlayerPos.x && y == PlayerPos.y) {
                // Draw the player object
                MacUILib_printf("%c", PlayerPos.symbol);
            } else {
                // Draw empty space within the border
                MacUILib_printf("%c", EMPTY_CHAR);
            }
        }
        MacUILib_printf("\n");
    }

    // Print debugging messages    
    // Print the current state and speed of the game

    MacUILib_printf("Game Level: %d", gameSpeedLev);

}

// PROGRAM LOOP DELAYER ROUTINE
/////////////////////////////////////////
void LoopDelay(void)
{
    // Change the delaying constant to vary the movement speed.
    MacUILib_Delay(gameSpeed);
} 

// PROGRAM CLEANUP ROUTINE
/////////////////////////////////////////
// Recall from PPA1 - this is run only once at the end of the program
// for garbage collection and exit messages.
void CleanUp(void)
{
    MacUILib_uninit();
}
