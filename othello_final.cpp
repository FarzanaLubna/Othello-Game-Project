
#include <bits/stdc++.h>
#include <windows.h>
using namespace std;


#define LIGHTRED 12

// Smaller board for testing purposes.  Actual size is 8x8.
const int ROWS = 8;
const int COLS = 8;

// Discs
const char PLAYER1	= 'X';
const char PLAYER2 = 'O';


/****************************************************************************/

// Display the board to the screen.
// [in] board - Game board
void DisplayBoard(const char board[][COLS])
{
    cout << " ";
    for (int c = 0; c < COLS; c++)
        cout << c;
    cout << endl;

    for (int r = 0; r < ROWS; r++)
    {
        cout << r;
        for (int c = 0; c < COLS; c++)
            cout << board[r][c];
        cout << endl;
    }
}

/****************************************************************************/

// Place the disc on the board, flip the discs affected, and
// return the number of discs flipped.  Note if 0 is returned,
// the position moved is illegal, and the board is not changed.
// [in/out] board - Game board
// [in]	 row   - Row in board to move to
// [in]	 col   - Col in board to move to
// [in]	 disc  - Player's disc to be placed (X or O)
int PlaceDisc(char board[][COLS], int row, int col, char disc)
{
    int num_flipped = 0;

    if (board[row][col] != ' ')
        return 0;

    board[row][col] = disc;

    char opposing_disc;
    if (disc == PLAYER1)
        opposing_disc = PLAYER2;
    else
        opposing_disc = PLAYER1;

    // Do we have discs to the right to flip?
    int disc_pos = -1;
    for (int c = col + 1; c < COLS && board[row][c] != ' ' && disc_pos == -1; c++)
    {
        if (board[row][c] == disc)
            disc_pos = c;
    }

    // Make sure we found a disc and that it is at least 2 spots away
    if (disc_pos != -1 && disc_pos > col + 1)
    {
        // Flip discs to the right
        for (int c = col + 1; c < disc_pos; c++)
        {
            board[row][c] = disc;
            num_flipped++;
        }
    }

    // Do we have discs to the left to flip?
    disc_pos = -1;
    for (int c = col - 1; c >= 0 && board[row][c] != ' ' && disc_pos == -1; c--)
    {
        if (board[row][c] == disc)
            disc_pos = c;
    }

    //if (disc_pos > -1) cout << "left disc_pos = " << disc_pos << endl;

    // Make sure we found a disc and that it is at least 2 spots away
    if (disc_pos != -1 && disc_pos < col - 1)
    {
        // Flip discs to the left
        for (int c = col - 1; c > disc_pos; c--)
        {
            board[row][c] = disc;
            num_flipped++;
        }
    }

    // Do we have discs above to flip?
    disc_pos = -1;
    for (int r = row - 1; r >= 0 && board[r][col] != ' ' && disc_pos == -1; r--)
    {
        if (board[r][col] == disc)
            disc_pos = r;
    }

    // Make sure we found a disc and that it is at least 2 spots away
    if (disc_pos != -1 && disc_pos < row - 1)
    {
        // Flip discs above
        for (int r = row - 1; r > disc_pos; r--)
        {
            board[r][col] = disc;
            num_flipped++;
        }
    }

    // Do we have discs below to flip?
    disc_pos = -1;
    for (int r = row + 1; r < ROWS && board[r][col] != ' ' && disc_pos == -1; r++)
    {
        if (board[r][col] == disc)
            disc_pos = r;
    }

    // Make sure we found a disc and that it is at least 2 spots away
    if (disc_pos != -1 && disc_pos > row + 1)
    {
        // Flip discs below
        for (int r = row + 1; r < disc_pos; r++)
        {
            board[r][col] = disc;
            num_flipped++;
        }
    }

    // Do we have discs diagnally up-left to flip?
    disc_pos = -1;
    int c = col - 1;
    for (int r = row - 1; c >= 0 && r >= 0 && board[r][c] != ' ' && disc_pos == -1; r--)
    {
        if (board[r][c] == disc)
            disc_pos = r;
        c--;
    }

    // Make sure we found a disc and that it is at least 2 spots away
    if (disc_pos != -1 && disc_pos < row - 1)
    {
        c = col - 1;
        for (int r = row - 1; r > disc_pos; r--)
        {
            board[r][c] = disc;
            num_flipped++;
            c--;
        }
    }

    // Do we have discs diagnally up-right to flip?
    disc_pos = -1;
    c = col + 1;
    for (int r = row - 1; c < COLS && r >= 0 && board[r][c] != ' ' && disc_pos == -1; r--)
    {
        if (board[r][c] == disc)
            disc_pos = r;
        c++;
    }

    // Make sure we found a disc and that it is at least 2 spots away
    if (disc_pos != -1 && disc_pos < row - 1)
    {
        c = col + 1;
        for (int r = row - 1; r > disc_pos; r--)
        {
            board[r][c] = disc;
            num_flipped++;
            c++;
        }
    }

    // Do we have discs diagnally down-left to flip?
    disc_pos = -1;
    c = col - 1;
    for (int r = row + 1; c >= 0 && r < ROWS && board[r][c] != ' ' && disc_pos == -1; r++)
    {
        if (board[r][c] == disc)
            disc_pos = r;
        c--;
    }

    // Make sure we found a disc and that it is at least 2 spots away
    if (disc_pos != -1 && disc_pos > row + 1)
    {
        c = col - 1;
        for (int r = row + 1; r < disc_pos; r++)
        {
            board[r][c] = disc;
            num_flipped++;
            c--;
        }
    }

    // Do we have discs diagnally down-right to flip?
    disc_pos = -1;
    c = col + 1;
    for (int r = row + 1; c < COLS && r < ROWS && board[r][c] != ' ' && disc_pos == -1; r++)
    {
        if (board[r][c] == disc)
            disc_pos = r;
        c++;
    }

    // Make sure we found a disc and that it is at least 2 spots away
    if (disc_pos != -1 && disc_pos > row + 1)
    {
        c = col + 1;
        for (int r = row + 1; r < disc_pos; r++)
        {
            board[r][c] = disc;
            num_flipped++;
            c++;
        }
    }

    // Reset board if nothing was flipped... illegal move
    if (num_flipped == 0)
        board[row][col] = ' ';

    return num_flipped;
}


int dx[ 8 ] = { -1, -1, -1, 0, 0, 1, 1, 1};
int dy[ 8 ] = { -1, 0, 1, -1, 1, -1, 0, 1};
bool isOk( int x, int y )
{
    if( x < 0 || x >= 8 || y < 0 || y >= 8 ) return 0;
    return 1;
}
int MoveIsPossible(const char board[][COLS], char player)
{
    char temp[ 8 ][ 8 ];
    for( int i = 0 ; i < 8; i++ )
    {
        for( int j = 0 ; j < 8; j++ )
        {
            temp[ i ][ j ] = board[ i ][ j ];
        }
    }
    for( int i = 0 ; i < 8; i++ )
    {
        for( int j = 0 ; j < 8; j++ )
        {
            if( board[i][j] == player )
            {
                for( int k = 0 ; k < 8 ; k++ )
                {
                    int x = i + dx[ k ];
                    int y = j + dy[ k ];
                    if( isOk(x, y ) && board[ x ][ y ] != ' ' && board[ x ][ y ] != player )
                    {
                        for( int p = x, q = y ; isOk(p, q ) ; p += dx[ k ], q += dy[ k ] )
                        {
                            if( board[ p ][ q ] == ' ' && PlaceDisc(temp, p, q, player)) return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

/****************************************************************************/

// Get the human's move (if a legal move is possible) and place it on the board.
// [in/out] board - Game board
int GetHumanMove(char board[][COLS], char PLAYER)
{
    int row, col;
    bool illegal_move;

    // Make sure there is a legal move that can be made
    cout<<MoveIsPossible(board, PLAYER)<<"\n";
    if (MoveIsPossible(board, PLAYER))
    {
        do
        {
            illegal_move = false;

            cout << "Row? ";
            cin >> row;
            while (row < 0 || row >= ROWS)
            {
                cout << "Please select a row between 0 and " << (ROWS - 1) << ".\n";
                cout << "Row? ";
                cin >> row;
            }

            cout << "Col? ";
            cin >> col;
            while (col < 0 || col >= COLS)
            {
                cout << "Please select a column between 0 and " << (COLS - 1) << ".\n";
                cout << "Col? ";
                cin >> col;
            }
            if (board[row][col] != ' ')
            {
                cout << "Please select an empty row and column.\n";
                illegal_move = 1;
            }
            else
            {
                int discs_flipped = PlaceDisc(board, row, col, PLAYER);
                if (discs_flipped == 0)
                {
                    cout << "Illegal move.\n";
                    illegal_move = true;
                }
                else if (discs_flipped == 1)
                {
                    cout << "Flipped 1 disc.\n\n";
                    return 1;
                }
                else
                {
                    cout << "Flipped " << discs_flipped << " discs.\n\n";
                    return 1;
                }
            }
        }
        while (illegal_move);
    }
    else
    {
        return 0;
    }
}

void SaveBoard(char board[][COLS], char temp_board[][COLS])
{

    for( int i = 0; i < ROWS; i++)
    {
        for(int j =0; j < COLS; j++)
            temp_board[i][j]= board[i][j];
    }
}

void whoWin(char board[][COLS])
{
    DisplayBoard(board);
    int p1 = 0, p2 = 0;
    for( int i = 0 ; i < 8; i++ )
    {
        for( int j = 0 ; j < 8; j++ )
        {
            p1 += (board[ i ][ j ] == PLAYER1); // board[i][j] = 'X' value 1
            p2 += (board[ i ][ j ] == PLAYER2); // board[i][j] = 'O' value 1
        }
    }
    if( p1 > p2 )
    {
        printf("PLAYER1 Win\n");
    }
    else if( p1 < p2 )
    {
        printf("PLAYER2 Win\n");
    }
    else printf("Draw\n");
}


int main()
{

    //Run these two lines first
    HANDLE hcolor;
    hcolor = GetStdHandle (STD_OUTPUT_HANDLE);
    char board[ROWS][COLS];

    //Use this function to set your colors
    SetConsoleTextAttribute(hcolor, LIGHTRED);
    // Create a test configuration
    strncpy(board[0],"XXXXXXXX ", COLS);
    strncpy(board[1],"XXOXXXXX ", COLS);
    strncpy(board[2],"XXXXXXXX ", COLS);
    strncpy(board[3],"XXXXOOXX ", COLS);
    strncpy(board[4],"XXXXOXXX ", COLS);
    strncpy(board[5],"XXXXXOXX ", COLS);
    strncpy(board[6],"XXXXOO   ", COLS);
    strncpy(board[7],"XXX      ", COLS);

    printf("PLAYER1 %c\n", PLAYER1);
    printf("PLAYER2 %c\n", PLAYER2);
    bool mv = 1;
    cout << endl;
    while(true)
    {
        DisplayBoard(board);
        printf("PLAYER%d MOVE\n", mv+1);
        int x;
        if( mv == 0 ) x = GetHumanMove(board, PLAYER1);
        else x = GetHumanMove(board, PLAYER2);
        if( x == 0 )
        {
            whoWin(board);
            break;
        }
        mv = !mv;

    }
    return 0;

}
/*
XXXXXXXX
XXOXXXXX
XXXXXXXX
XXXXOOXX
XXXXOXXX
XXXXXOXX
XXXXOO
XXX
*/
