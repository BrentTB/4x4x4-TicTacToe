#ifndef GAME
#define GAME

// #include <bits/stdc++.h>
#include <iostream>
#include "Board.h"
#include "Bot.h"

using namespace std;

// #define startLoop(a, b)                           \
//     for (auto i = 0; i < a; i++)                  \
//     {                                             \
//         for (auto j = 0; j < b; j++)              \
//         {                                         \
//             for (auto iter = 0; iter < 4; iter++) \
//             {
// #define endLoop \
//     }           \
//     }           \
    // }

class Game
{
public:
    Game();

    void startGame(const bool twoPlayer);

    /**
     * @brief Destroy the Game object
     *
     */
    ~Game();

private:
    void gameLoop();
    void showBoard();
    void getInput();
    bool checkWin(const char piece);
    bool checkPiece(const char piece, vector<tuple<int, int, int>> &moves);
    void displayWin();

    Board gameBoard_;
    Bot opponent_;
    bool xTurn_;
    bool useBot_;
    char win_;
    tuple<int, int, int> input_;
};

#endif