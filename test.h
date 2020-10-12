#include <algorithm>
#include <iostream>
using namespace std;
#define X_piece_number 8
#define O_piece_number 0
#define Empty_piece_number -1
#define PLAYER_PIECE X_piece_number
#define AI_piece O_piece_number
namespace GameEngine
{
    class thinker
    {
    public:
        thinker(int playerPiece);
        void checkForOptimalSolutionToPlace(int (*gridArray)[3][3]);
        int minimax(int board[3][3], int depth, bool isMax);
        int evaluate(int b[3][3]);
        bool isMovesLeft(int board[3][3]);

    private:
        int maxPlayer;
        int minPlayer;
    };
    thinker::thinker(int playerPiece)
    {
        if (O_piece_number == playerPiece)
        {
            this->maxPlayer = X_piece_number;
            this->minPlayer = playerPiece;
        }
        else
        {
            this->maxPlayer = O_piece_number;
            this->minPlayer = playerPiece;
        }
    }

bool thinker::isMovesLeft(int board[3][3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == Empty_piece_number)
                return true;
    return false;
}

int thinker::evaluate(int b[3][3])
{
    // Checking for Rows for X or O victory.
    for (int row = 0; row < 3; row++)
    {
        if (b[row][0] == b[row][1] &&
            b[row][1] == b[row][2])
        {
            if (b[row][0] == maxPlayer)
                return +10;
            else if (b[row][0] == minPlayer)
                return -10;
        }
    }

    // Checking for Columns for X or O victory.
    for (int col = 0; col < 3; col++)
    {
        if (b[0][col] == b[1][col] &&
            b[1][col] == b[2][col])
        {
            if (b[0][col] == maxPlayer)
                return +10;

            else if (b[0][col] == minPlayer)
                return -10;
        }
    }

    // Checking for Diagonals for X or O victory.
    if (b[0][0] == b[1][1] && b[1][1] == b[2][2])
    {
        if (b[0][0] == maxPlayer)
            return +10;
        else if (b[0][0] == minPlayer)
            return -10;
    }

    if (b[0][2] == b[1][1] && b[1][1] == b[2][0])
    {
        if (b[0][2] == maxPlayer)
            return +10;
        else if (b[0][2] == minPlayer)
            return -10;
    }

    // Else if none of them have won then return 0
    return 0;
}

int thinker::minimax(int board[3][3], int depth, bool isMax)
{
    int score = evaluate(board);

    // If Maximizer has won the game return his/her
    // evaluated score
    if (score == 10)
        return score;

    // If Minimizer has won the game return his/her
    // evaluated score
    if (score == -10)
        return score;

    // If there are no more moves and no winner then
    // it is a tie
    if (isMovesLeft(board) == false)
        return 0;

    // If this maximizer's move
    if (isMax)
    {
        int best = -1000;

        // Traverse all cells
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                // Check if cell is empty
                if (board[i][j] == Empty_piece_number)
                {
                    // Make the move
                    board[i][j] = maxPlayer;

                    // Call minimax recursively and choose
                    // the maximum value
                    best = max(best, minimax(board, depth + 1, !isMax));

                    // Undo the move
                    board[i][j] = Empty_piece_number;
                }
            }
        }
        return best;
    }

    // If this minimizer's move
    else
    {
        int best = 1000;

        // Traverse all cells
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                // Check if cell is empty
                if (board[i][j] == Empty_piece_number)
                {
                    // Make the move
                    board[i][j] = minPlayer;

                    // Call minimax recursively and choose
                    // the minimum value
                    best = min(best, minimax(board, depth + 1, !isMax));

                    // Undo the move
                    board[i][j] = Empty_piece_number;
                }
            }
        }
        return best;
    }
}

void thinker:: checkForOptimalSolutionToPlace(int (*gridArray)[3][3])
{
    int board[3][3];
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                board[i][j] = (*gridArray)[i][j];
            }
        }
    int bestVal = -1000, row=0, col=0;

    // Traverse all cells, evaluate minimax function for
    // all empty cells. And return the cell with optimal
    // value.
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // Check if cell is empty
            if (board[i][j] == Empty_piece_number)
            {
                // Make the move
                board[i][j] = maxPlayer;

                // compute evaluation function for this
                // move.
                int moveVal = minimax(board, 0, false);

                // Undo the move
                board[i][j] = Empty_piece_number;

                // If the value of the current move is
                // more than the best value, then update
                // best/
                if (moveVal > bestVal)
                {
                    row = i;
                    col = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    //cout<<"The value of the best Move is : "<<bestVal<<endl;
    (*gridArray)[row][col] = AI_piece;
}
}

int main()
{
    GameEngine::thinker ai(PLAYER_PIECE);
    int ar[3][3] = {{8, 0, -1}, {8, 0, -1}, {0, -1, -1}};
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::cout << ar[i][j] << " ";
        }
        cout << endl;
    }
    cout<<endl;
    ai.checkForOptimalSolutionToPlace(&ar);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::cout << ar[i][j] << " ";
        }
        cout<<endl;
    }
    std::cout << std::endl
                  << "completed";
}