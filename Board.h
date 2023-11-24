#ifndef BOARD.h
#define BOARD .h

#include <bits/stdc++.h>

using namespace std;
using GameBoard = vector<vector<vector<char>>>;
#define endd cout << endl
#define defaultChar ' '

// exception class for if a chosen spot already has a piece
class UsedSpot
{
};

class Board
{
public:
    Board();

    void printBoard();

    void placePiece(char piece, int board, int row, int col);

    void printBoardVertical();

    ~Board();

private:
    GameBoard gameBoard_;
};

#endif