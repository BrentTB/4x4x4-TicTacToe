#ifndef LOGIC
#define LOGIC

#include <vector>
#include <tuple>
#include "Board.h"

using namespace std;

using GameBoard = vector<vector<vector<char>>>;
using AllMoves = shared_ptr<vector<vector<tuple<int, int, int>>>>;

class Logic
{
public:
    Logic(char pl1, char pl2, char defaultChar);

    AllMoves fourInARow();

    /**
     * @brief Checks if the game is drawn, as there are no default characters
     *
     * @return true if all squares are fill
     * @return false otherwise
     */
    bool checkDraw(const Board& gameBoard);

private:
    AllMoves allMoves_;
    char pl1_;
    char pl2_;
    char defaultChar_;
};

#endif