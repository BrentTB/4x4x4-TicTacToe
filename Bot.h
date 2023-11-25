#ifndef BOT
#define BOT

#include <iostream>
#include <vector>
#include <tuple>
#include "Logic.h"

using namespace std;
using GameBoard = vector<vector<vector<char>>>;
using PossibleMoves = vector<vector<vector<double>>>;

const char playerC = 'p';
const char botC = 'b';
const char defaultC = 'd';

class Bot
{
public:
    /**
     * @brief Construct a new Bot object
     *
     * @param playerChar the char used to represent the player
     * @param botChar the char used to represent the bot
     * @param defaultChar the char used to represent an empty square
     */
    Bot();

    /**
     * @brief Set the Board State object based on the player's move
     *
     * @param playerInput the input from the player in the last turn
     */
    void setBoardState(const tuple<int, int, int> &playerInput);

    /**
     * @brief Get the bot's move
     *
     * @return tuple<int, int, int> the board coordinates of the bot's move
     */
    tuple<int, int, int> getMove();

    /**
     * @brief Destroy the Bot object
     *
     */
    ~Bot();

private:
    /**
     * @brief adds score to moves that allow the bot to win/get closer to winning
     *
     */
    void botScore();

    /**
     * @brief adds score to moves that block the player's moves
     *
     */
    void playerScore();

    /**
     * @brief goes through all move's scores and finds the highest score
     *
     * @return tuple<int, int, int> the board coordinates of the bot's move
     */
    tuple<int, int, int> findBestScore();

    GameBoard gameBoard_;
    PossibleMoves allMoves_;
    Logic gameLogic_;
};

#endif

// TODO: make the score functions neater / reuse code