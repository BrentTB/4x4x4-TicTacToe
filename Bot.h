#ifndef BOT
#define BOT

#include <iostream>
#include <vector>
#include <tuple>

using namespace std;
using GameBoard = vector<vector<vector<char>>>;
using PossibleMoves = vector<vector<vector<double>>>;

class Bot
{
public:
    Bot(char pl1, char pl2, char defaultChar); // pl2 is the char the bot uses

    void setBoardState(const tuple<int, int, int> & playerInput);
    tuple<int, int, int> getMove();

    ~Bot();

private:
    tuple<int, int, int> findBestScore();
    double getScore();
    double enemyScore();
    GameBoard gameBoard_;
    PossibleMoves allMoves_;
    char pl1_;
    char pl2_;
    char defaultChar_;
};

#endif