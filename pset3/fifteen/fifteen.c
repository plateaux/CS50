/**
 * fifteen.c
 * Amir Kurtovic
 * amirkurtovic@gmail.com
 *
 * Implements the Game of Fifteen (generalized to d x d).
 *
 * Usage: ./fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [MIN,MAX]
 *
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

int board[MAX][MAX];

// board's dimension
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void save(void);

int main(int argc, string argv[])
{
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
            printf("You won!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(300000);
        }

        // sleep for animation's sake
        usleep(300000);
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
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1,
 * (i.e., fills board with values but does not actually print them),
 * whereby board[i][j] represents row i and column j.
 */
void init(void)
{
    int biggestTile = d*d -1;
    
    //for loop of rows
    for (int i = 0; i < d; i++)
    {
        //for loop of columns
        for (int j = 0; j<d; j++)
        {
            board[i][j] = biggestTile;
            biggestTile--;
        }
    }
    
    
    //Check for odd tiles and swap 1 & 2
    if (d*d % 2 != 0)
    {
        board[d-1][d-3] = 1;
        board[d-1][d-2] = 2;
     }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j<d; j++)
        {
            if(board[i][j]== 0)
            {
                printf("    |");
            }
            else
            {
                printf("%3i |", board[i][j]);
                
            }
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    bool legal = false;
    int tilePositionRow;
    int tilePositionColumn;
    int blankPositionRow;
    int blankPositionColumn;
 
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j<d; j++)
        {
            if(board[i][j]== tile)
            {
                tilePositionRow = i;
                tilePositionColumn = j;
            }
            
            if(board[i][j] == 0)
            {
                blankPositionRow = i;
                blankPositionColumn = j;
            }
        } 
    }
    
    //check if tile is left of blank tile
    if (tilePositionRow == blankPositionRow-1)
    {
        if (tilePositionColumn == blankPositionColumn)
        {
            legal = true;
            board[blankPositionRow][blankPositionColumn] = tile;
            board[tilePositionRow][tilePositionColumn]= 0;
            return true;
        }
    
    }
    
    //check if tile is right of blank tile
    if (tilePositionRow == blankPositionRow+1)
    {
        if (tilePositionColumn == blankPositionColumn)
        {
            legal = true;
            board[blankPositionRow][blankPositionColumn] = tile;
            board[tilePositionRow][tilePositionColumn]= 0;
            return true;
        }
    
    }
    
    //check if tile is below blank tile
    if (tilePositionColumn == blankPositionColumn-1)
    {
        if (tilePositionRow == blankPositionRow)
        {
            legal = true;
            board[blankPositionRow][blankPositionColumn] = tile;
            board[tilePositionRow][tilePositionColumn]= 0;
            return true;
        }
    
    }
    
    //check if tile is above blank tile
    if (tilePositionColumn == blankPositionColumn+1)
    {
        if (tilePositionRow == blankPositionRow)
        {
            legal = true;
            board[blankPositionRow][blankPositionColumn] = tile;
            board[tilePositionRow][tilePositionColumn]= 0;
            return true;
        }
    }

    return legal;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int smallestTile = 1;
    bool inOrder = true;
    
    while(inOrder)
    {
        //for loop of rows
        for (int i = 0; i < d; i++)
        {
            //for loop of columns
            for (int j = 0; j< d; j++)
            {
                if (board[i][j] == smallestTile)
                {
                    smallestTile++;
                    inOrder = true;
                }
                else
                {
                    inOrder = false;
                    return false;
                }
            }//end columns for loop
        }//end rows for loop
    }
    //return true if all checked and inOrder still true;
    return true;
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
