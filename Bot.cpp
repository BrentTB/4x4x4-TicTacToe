#include "Bot.h"

Bot::Bot(char pl1, char pl2, char defaultChar) : gameBoard_(4, vector<vector<char>>(4, vector<char>(4, defaultChar))),
                                                 allMoves_(4, vector<vector<double>>(4, vector<double>(4, 0))),
                                                 pl1_(pl1), pl2_(pl2), defaultChar_(defaultChar){};

void Bot::setBoardState(const tuple<int, int, int> &playerInput)
{
    gameBoard_[get<0>(playerInput)][get<1>(playerInput)][get<2>(playerInput)] = pl1_;
}

tuple<int, int, int> Bot::getMove()
{
    for (auto i = 0; i < 4; i++)
    {
        for (auto j = 0; j < 4; j++)
        {
            for (auto k = 0; k < 4; k++)
            {
                // the bot can't move somewhere that has a piece
                if (gameBoard_[i][j][k] != defaultChar_)
                {
                    allMoves_[i][j][k] = INT32_MIN;
                    break;
                }
                // simulate playing the move
                gameBoard_[i][j][k] = pl2_;

                // the default score is zero, which can be added to and subtracted from
                allMoves_[i][j][k] = INT32_MIN;
                allMoves_[i][j][k] += getScore();
                allMoves_[i][j][k] -= enemyScore();

                // undo the move
                gameBoard_[i][j][k] = defaultChar_;
            }
        }
    }

    return findBestScore();
}

double Bot::getScore()
{
    double score = 0;
    /* corners of board 1 and 4 are best, and the middle of board 2 and 3
    the edges on board 1 and 4 and the edges of board 2 and 4 are then most valuable.
    Then the middle of board 1 and 4 and the corners of board 2 and 3 are the least valuable

    ie:
    board 1 and 4:
        corners > edges > middle
        100         50      10

    board 2 and 3:
        middle > edges > corner
    */

    for (auto i = 0; i < 4; i++)
    {
        for (auto j = 0; j < 4; j++)
        {
            for (auto k = 0; k < 4; k++)
            {
                if (gameBoard_[i][j][k] == 'O')
                {
                    if (i == 0 || i == 3)
                    {
                        if ((j == 0 || j == 3) && (k == 0 || k == 3))
                            score += 100;
                        else if (j == 0 || j == 3 || k == 0 || k == 3)
                            score += 50;
                        else
                            score += 10;
                    }
                    else
                    {
                        if ((j == 0 || j == 3) && (k == 0 || k == 3))
                            score += 10;
                        else if (j == 0 || j == 3 || k == 0 || k == 3)
                            score += 50;
                        else
                            score += 100;
                    }
                }
            }
        }
    }
    return score;
}

double Bot::enemyScore()
{
    // if the opponent can win, minus a lot -> if the opponent has 3 in a row that isnt blocked
    return 0;
}

tuple<int, int, int> Bot::findBestScore()
{
    int board = 0, row = 0, col = 0;
    double bestScore = INT32_MIN;

    for (auto i = 0; i < 4; i++)
    {
        for (auto j = 0; j < 4; j++)
        {
            for (auto k = 0; k < 4; k++)
            {
                if (allMoves_[i][j][k] >= bestScore)
                {
                    bestScore = allMoves_[i][j][k];
                    board = i;
                    row = j;
                    col = k;
                }
            }
        }
    }
    return {board, row, col};
}

Bot::~Bot(){};