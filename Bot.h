#ifndef BOT
#define BOT

#include <iostream>
#include <vector>
#include <tuple>

using namespace std;
const char defaultChar = ' ';
using GameBoard = vector<vector<vector<char>>>;
using PossibleMoves = vector<vector<vector<double>>>;

class Bot
{
public:
    Bot();

    void setBoardState(const tuple<int, int, int> & playerInput);
    tuple<int, int, int> getMove();

    ~Bot();

private:
    tuple<int, int, int> findBestScore();
    double getScore();
    double enemyScore();
    GameBoard gameBoard_;
    PossibleMoves allMoves_;
};

#endif