#ifndef BOARD
#define BOARD

// #include <bits/stdc++.h>
#include <iostream>
#include <vector>

using namespace std;
using GameBoard = vector<vector<vector<char>>>;
#define endd cout << endl
#define spc  "        "
const char defaultChar = ' ';

/**
 * @brief Exception class for if a chosen spot already has a piece
 * 
 */
class UsedSpot
{
};

/**
 * @brief Exception class for if a chosen spot is invalid / off the board
 * 
 */
class InvalidSpot
{
};

class Board
{
public:
    /**
     * @brief Construct a new Board object
     * 
     */
    Board();

    /**
     * @brief display the current board
     * 
     */
    void printBoard();

    void placePiece(char piece, int board, int row, int col);

    void printBoardVertical();

    ~Board();

private:
    GameBoard gameBoard_;
};

#endif