#ifndef GAME
#define GAME

#include <iostream>
#include <tuple>
#include "Board.h"
#include "Bot.h"

using namespace std;

/**
 * @brief Class used to run a game of 3d 4x4 tic tac toe
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
     * @brief Starts a game of 3d 4x4 tic tac toe, either with 2 players or a bot
     *
     * @param twoPlayer false if the player is playing a bot. If playing with a bot, the player is always 'X'
     * @param xFirst true if 'X' moves first
     */
    void startGame(const bool twoPlayer, const bool xFirst=true);

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
     * @brief Checks if the game is drawn, as there are no default characters
     * 
     * @return true if all squares are fill
     * @return false otherwise
     */
    bool checkDraw();

    /**
     * @brief Takes in four pieces and returns if all of them belong to the same side
     *
     * @param piece the player/bot's char to be checked
     * @param moves a vector of the grid squares to be checked
     * @return true if all of the board places indicated by moves are fulled by the piece's char
     * @return false otherwise
     */
    bool checkPiece(const char piece, vector<tuple<int, int, int>> &moves);

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

    Board gameBoard_;            // stores the moves that have been played
    Bot opponentAi_;               // stores the bot to play against
    bool xTurn_;                 // if it is X's turn or O's turn
    bool useBot_;                // if the opponent is a bot / player
    char win_;                   // stores which player/bot has one
    tuple<int, int, int> input_; // stores the user / bots input
};

#endif