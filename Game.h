#ifndef GAME
#define GAME

#include <iostream>
#include <tuple>
#include "Board.h"
#include "Bot.h"
#include "Logic.h"

using namespace std;
const char pl1 = 'X'; // the piece of player one
const char pl2 = 'O'; // the piece of player two
const char defaultChar = ' ';
const char winChar = 'W';

/**
 * @brief Class used to run a game of 3d 4x4x4 tic tac toe
 *
 */
class Game
{
public:
    /**
     * @brief Construct a new Game object
     *
     */
    Game();

    /**
     * @brief Starts a game of 3d 4x4x4 tic tac toe, either with 2 players or a bot
     *
     * @param twoPlayer false if the player is playing a bot. If playing with a bot, the player is always 'X'
     * @param xFirst true if 'X' moves first (or the char of pl1)
     */
    void startGame(const bool twoPlayer, const bool xFirst = true);

    /**
     * @brief Destroy the Game object
     *
     */
    ~Game();

private:
    /**
     * @brief Runs the game and calls all other functions
     *
     */
    void gameLoop();

    /**
     * @brief Display the current state of the board
     *
     */
    void showBoard();

    /**
     * @brief Get the Input object gets and sanitises the user's input / gets the bot's input
     *
     */
    void getInput();

    /**
     * @brief when playing with a bot, gets the bots next move and plays it
     *
     */
    void botMove();

    /**
     * @brief Find if the game has been won. If it has, the winning pieces are changed to another symbol
     *
     * @param piece the char representing one of the players/bot
     * @return true if the given piece has won
     * @return false otherwise
     */
    bool checkWin(const char piece);

    /**
     * @brief Displays the board and a winning message at the end of the game
     *
     */
    void displayWin();

    /**
     * @brief Displays the board and a drawing message at the end of the game
     *
     */
    void displayDraw();

    Board gameBoard_;                       // stores the moves that have been played
    Logic gameLogic_;                       // used to find out if the game is over/won
    Bot opponentAi_;                        // stores the bot to play against
    bool xTurn_;                            // if it is X's turn or O's turn
    bool useBot_;                           // if the opponent is a bot / player
    char win_;                              // stores which player/bot has one
    vector<tuple<int, int, int>> allInput_; // stores all of the user's inputs
};

#endif

/*
TODO: make it easier to see what the opponent just moved, against the bot or a player
maybe add the ability to undo a move?

TODO: make it easier to restart a game without rerunning the code?

*/