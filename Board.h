#ifndef BOARD
#define BOARD

#include <iostream>
#include <vector>

using namespace std;
using GameBoard = vector<vector<vector<char>>>;
#define endd cout << endl
#define spc "        "
const char defaultChar = ' ';
const char winChar = 'W';

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

/**
 * @brief Class that represents the board of a 3d 4x4 tic tac toe game
 *
 */
class Board
{
public:
    /**
     * @brief Construct a new Board object
     *
     */
    Board();

    /**
     * @brief Display the current board in the terminal
     *
     */
    void printBoard();

    /**
     * @brief places a specified 'winning' piece at the specified square, regardless of if that square is occupied or not
     *
     * @param board indicates the board
     * @param row indicates the row
     * @param col indicates the column
     */
    void placeWinPiece(int board, int row, int col);

    /**
     * @brief places the given piece at the specified square, if the location given is valid
     *
     * @param piece the char of the piece being placed
     * @param board indicates the board
     * @param row indicates the row
     * @param col indicates the column
     */
    void placePiece(char piece, int board, int row, int col);

    /**
     * @brief Get the piece at the location specified
     *
     * @param board indicates the board
     * @param row indicates the row
     * @param col indicates the column
     * @return char the piece at the given location
     */
    char getPiece(int board, int row, int col);

    /**
     * @brief Destroy the Board object
     *
     */
    ~Board();

private:
    GameBoard gameBoard_; // stores the 4x4x4 game board
};

#endif