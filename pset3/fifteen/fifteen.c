/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Masatoshi Nishiguchi
 * nishiguchi.masa@gmail.com
 *
 * Implements the Game of Fifteen (generalized to d x d).
 *
 * Usage: ./fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [MIN,MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// board's minimal dimension
#define MIN 3

// board's maximal dimension
#define MAX 9

// board, whereby board[i][j] represents row i and column j
int board[MAX][MAX];

// board's dimension
int d;

// position of empty space
int empty_row;
int empty_col;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void save(void);
void swap(int* a, int* b);


int main(int argc, string argv[])
{
    // greet player
    greet();

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < MIN || d > MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            MIN, MIN, MAX, MAX);
        return 2;
    }

    // initialize the board
    init();
    
    // initial position of empty space      
    empty_row = d - 1;  
    empty_col = d - 1;
            
    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // saves the current state of the board (for testing)
        save();

        // check for win
        if (won())
        {
            printf("You won! \n");
            usleep(500000);
            printf("Congratulations!!! \n\n");
            usleep(500000);
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep for animation's sake
        usleep(200000);
    }

    // that's all folks
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("GAME OF FIFTEEN\n");
    usleep(1000000);    // sleep for 1 seconds
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1,
 * (i.e., fills board with values but does not actually print them),
 * whereby board[i][j] represents row i and column j.
 */
void init(void)
{
    int num_tiles = (d * d) - 1;    // greatest number
    int n = num_tiles;              // counter
    
    // assign a number to each tile in descending order
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {           
            board[i][j] = n;            
            n = n - 1;
        }
    }
    
    // swap #2 and #1 if the board has an odd number of tiles
    if (num_tiles % 2 != 0)
        swap(&board[d-1][d-3], &board[d-1][d-2]); 
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // draw a line according to the size of board
    for (int k = 0; k < d; k++)
    {
        printf("====");
    }
    printf("==\n\n");
    
    // Prints the board in its current state
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if(board[i][j] != 0)
                printf("  %2i", board[i][j]);
            else
                printf("  __");
        }
        printf("\n\n");
    }
    
    // draw a line according to the size of board
    for (int k = 0; k < d; k++)
    {
        printf("====");
    }
    printf("==\n");
}

/**
* If tile borders empty space, moves tile and returns true, else
* returns false.
*/
/**
* If tile borders empty space, moves tile and returns true, else
* returns false.
*/
bool move(int tile)
{
    // initialize position of tile
    int row = INT_MIN;
    int col = INT_MIN; 
          
    // linear search for the position of tile
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == tile)
            {
                row = i;
                col = j;
            }
        }
    } 
    if (row < 0 || col < 0)
    {
        printf("tile cannot be located\n");
        usleep(1000000);    // sleep for 1 seconds
        return false;
    }

    // ensure that tile is adjacent to empty space
    if (row == empty_row)
    {
        if (col == (empty_col - 1) || col == (empty_col + 1))
        {
            // swap tile and empty space
            swap(&board[row][col], &board[empty_row][empty_col]);

            //update the position of empty space
            empty_row = row;
            empty_col = col; 

            return true;
        }
    }
    else if (col == empty_col)
    {
        if (row == (empty_row - 1) || row == (empty_row + 1))
        {
            // swap tile and empty space
            swap(&board[row][col], &board[empty_row][empty_col]);

            //update the position of empty space
            empty_row = row;
            empty_col = col; 

            return true;
        }
    }
   
    // unsuccessful because the conditions are NOT met above
    return false;
}

/**
* Returns true if game is won (i.e., board is in winning configuration),
* else false.
*/
bool won(void)
{
    // count from 1 up through d*d
    // and ensure that the count matches each tile's value    
    while((board[0][0] == 1) && (board[d-1][d-1] == 0)) 
    {
        int count = 1;
    
        for (int i = 0 ; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                if (board[i][j] == count)
                {
                    count++;
                }
                else if (count == (d * d))
                {
                    return true;
                }
                    else
                    {
                        goto not_won_yet;
                    }
            }
        }     
    } 
         
    // NOT in winning configuration
    not_won_yet:
        return false; 
} 

/**
 * Saves the current state of the board to disk (for testing).
 */
void save(void)
{
    // log
    const string log = "log.txt";

    // delete existing log, if any, before first save
    static bool saved = false;
    if (!saved)
    {
        unlink(log);
        saved = true;
    }

    // open log
    FILE* p = fopen(log, "a");
    if (p == NULL)
    {
        return;
    }

    // log board
    fprintf(p, "{");
    for (int i = 0; i < d; i++)
    {
        fprintf(p, "{");
        for (int j = 0; j < d; j++)
        {
            fprintf(p, "%i", board[i][j]);
            if (j < d - 1)
            {
                fprintf(p, ",");
            }
        }
        fprintf(p, "}");
        if (i < d - 1)
        {
            fprintf(p, ",");
        }
    }
    fprintf(p, "}\n");

    // close log
    fclose(p);
}

/**
 * swap function
 */
void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
