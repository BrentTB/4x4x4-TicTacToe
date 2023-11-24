#ifndef GAME
#define GAME

// #include <bits/stdc++.h>
#include <iostream>
#include "Board.h"
#include "Bot.h"

using namespace std;

class Game
{
public:
    Game();

    void startGame(bool twoPlayer);

    /**
     * @brief Destroy the Game object
     *
     */
    ~Game();

private:
    void gameLoop();
    void showBoard();
    void getInput();
    void move();

    Board gameBoard_;
    Bot opponent_;
    bool xTurn_;
    bool useBot_;
    char win_;
    tuple<int, int, int> input_;
};

#endif