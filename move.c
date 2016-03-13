/**
 * codes on main function
 *
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
        usleep(500000);
    }
 */
 

 /**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{   
    // position of tile
    int row;    
    int col;
    
    // linear search for the position of tile
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == tile)
            {
                row = i;
                col = j;
                printf("row: %i, col: %i\n\n", row, col);
                break;
            }
        }
    }
    
    while ((0 <= row && row < d) && (0 <= col && col < d))
    {
        if(row == empty_row)
        {
            if(col == (empty_col - 1) | col == (empty_col + 1))
            {
                break;       
            }
            else
            {
                printf("false empty r: %i, empty c: %i\n\n", empty_row, empty_col);
                usleep(2000000);    // sleep for 2 seconds
                return false;
            }
        }
        
        if(col == empty_col)
        {
            if(row == (empty_row - 1) | row == (empty_row + 1))
            {
                break;       
            }
            else
            {
                printf("false empty r: %i, empty c: %i\n\n", empty_row, empty_col);
                usleep(2000000);    // sleep for 2 seconds
                return false;
            }
        }
    } 
    // swap tile and empty space
    swap(&board[row][col], &board[empty_row][empty_col]);
                
    //update the position of empty space
    empty_row = row;
    empty_col = col;
    return true;  
}
