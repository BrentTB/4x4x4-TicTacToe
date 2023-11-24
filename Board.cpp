#include "Board.h"

Board::Board()
{
    gameBoard_.resize(4);
    for (auto i = 0; i < 4; i++)
    {
        gameBoard_[i].resize(4);
        for (auto j = 0; j < 4; j++)
        {
            gameBoard_[i][j].resize(4);
            for (auto k = 0; k < 4; k++)
            {
                // gameBoard_[i][j][k] = i + '0';
                gameBoard_[i][j][k] = defaultChar;
            }
        }
    }
}

void Board::printBoard()
{
    for (auto j = 0; j < 4; j++)
    {
        for (auto i = 0; i < 4; i++)
        {
            for (auto k = 0; k < 4; k++)
            {
                cout << gameBoard_[i][j][k];
                if (k != 3)
                {
                    cout << "|";
                }
            }
            cout << "\t\t";
        }
        endd;
        for (auto i = 0; i < 4; i++)
        {
            if (j != 3)
            {
                for (auto k = 0; k < 7; k++)
                {
                    cout << "-";
                }
                cout << "\t\t";
            }
        }
        endd;
    }
    endd;
    endd;
}

void Board::placePiece(char piece, int board, int row, int col)
{

    if (gameBoard_[board][row][piece] != defaultChar)
        throw UsedSpot();
}

void Board::printBoardVertical()
{
    for (auto i = 0; i < 4; i++)
    {
        for (auto j = 0; j < 4; j++)
        {
            for (auto k = 0; k < 4; k++)
            {
                cout << gameBoard_[i][j][k];
                if (k != 3)
                {
                    cout << "|";
                }
            }
            endd;
            if (j != 3)
            {
                for (auto k = 0; k < 7; k++)
                {
                    cout << "-";
                }
                endd;
            }
        }
        endd;
        endd;
    }
}

Board::~Board(){};
