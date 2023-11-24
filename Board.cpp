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
    // print the board labels
    cout << "      ";
    for (auto j = 1; j < 5; j++)
    {
        cout <<j*100<<"   "<<spc<<" ";
    }
    cout << endl << endl;

    //print the column labels
    cout << "    ";
    for (auto j = 1; j < 5; j++)
    {
        for (auto i = 1; i < 5; i++)
        {

            cout <<i;
            if(i != 4)
            cout << " ";
        
        }
            cout << spc;
    }
    endd;

    // print all the boards
    for (auto j = 0; j < 4; j++)
    {
        // print the row labels
        cout << (j+1)*10 << "  ";

        // print one board
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
            cout << spc;
        }
        cout << endl << "    ";
        for (auto i = 0; i < 4; i++)
        {
            if (j != 3)
            {
                for (auto k = 0; k < 7; k++)
                {
                    cout << "-";
                }
                cout << spc;
            }
        }
        endd;
    }
    endd;
    endd;
}

void Board::placePiece(char piece, int board, int row, int col)
{


    if (board < 0 || board > 3 || row < 0 || row > 3 || col < 0 || col > 3 )
    throw InvalidSpot();

    if (gameBoard_[board][row][col] != defaultChar)
        throw UsedSpot();

    gameBoard_[board][row][col] = piece;
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
