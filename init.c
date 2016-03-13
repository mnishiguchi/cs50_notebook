/**
 * init.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Masatoshi Nishiguchi
 * nishiguchi.masa@gmail.com
 *
 * Test program for init function of fifteen.c
 *
 * Usage: ./init d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [MIN,MAX]
 *
 */

#include <cs50.h>
#include <stdio.h>

// board's minimal dimension
#define MIN 2

// board's maximal dimension
#define MAX 10

// board, whereby board[i][j] represents row i and column j
int board[MAX][MAX];

// board's dimension
int d;

void swap(int* a, int* b);

int main(int argc, char* argv[])
{ 
    if (argc != 2)
    {
        printf("error!");
        return 1;
    }
    
    d = atoi(argv[1]);
    if (d < MIN || d > MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            MIN, MIN, MAX, MAX);
        return 2;
    }
     
    
    // fill the board with numbers in decending order
    int i, j;
    int num_tiles = (d * d) - 1;    // == greatest number on the board
    
    int number = num_tiles;
    for (i = 0; i < d; i++)
    {
        for (j = 0; j < d; j++)
        {           
            board[i][j] = number;
               
            number = number - 1;
        }
    }
    
    // swap 1 and 2 if the board has an odd number of tiles
    if (num_tiles % 2 != 0)
        swap(&board[d-1][d-3], &board[d-1][d-2]);
    
    // print the tiles
    for (i = 0; i < d; i++)
    {
        for (j = 0; j < d; j++)
        {
            if(board[i][j] != 0)
                printf(" %2i", board[i][j]);
            else
                printf("  _");
        }
        printf("\n");
    }
    return 0;
}

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

