#ifndef LOGIC
#define LOGIC

#include <vector>
#include <tuple>
#include "Board.h"

using namespace std;

using GameBoard = vector<vector<vector<char>>>;
using AllMoves = vector<vector<tuple<int, int, int>>>;

class Logic
{
public:
    Logic();

    AllMoves &fourInARow();

    /**
     * @brief Checks if the game is drawn, as there are no default characters
     *
     * @return true if all squares are fill
     * @return false otherwise
     */
    bool checkDraw(const Board &gameBoard, const char defaultChar);

private:
    AllMoves allMoves_;
};

#endif