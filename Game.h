#ifndef GAME.h
#define GAME .h

#include <bits/stdc++.h>
#include "Board.h"
#include "Bot.h"

using namespace std;

class Game
{
public:
    Game();

    void startGame(bool twoPlayer);

    ~Game();

private:
    void gameLoop();
    void move();


    Board gameBoard_;
    Bot opponent_;
    bool xTurn_;
    bool useBot_;
    char win_;
};

#endif