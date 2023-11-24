#include "Bot.h"

Bot::Bot() : gameBoard_(4, vector<vector<char>>(4, vector<char>(4,defaultChar))),
             allMoves_(4, vector<vector<double>>(4, vector<double>(4,0))){};

void Bot::setBoardState(const tuple<int, int, int> &playerInput)
{
    gameBoard_[get<0>(playerInput)][get<1>(playerInput)][get<2>(playerInput)] = 'X';
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
                if(gameBoard_[i][j][k] != defaultChar)
                {
                    allMoves_[i][j][k]=INT32_MIN;
                    break;
                }
                // simulate playing the move
                gameBoard_[i][j][k] = 'O';

                //the default score is zero, which can be added to and subtracted from
                allMoves_[i][j][k]=INT32_MIN;
                allMoves_[i][j][k]+=getScore();
                allMoves_[i][j][k]-=enemyScore();
            
                // undo the move
                gameBoard_[i][j][k] = defaultChar;
            }
        }
    }

    return findBestScore();
}

void Bot::getScore(){}

void Bot::enemyScore(){}

tuple<int, int, int> findBestScore()
{
    int board, row, col;
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