#include "Bot.h"

Bot::Bot() : gameBoard_(4, vector<vector<char>>(4, vector<char>(4, defaultC))),
                                                            allMoves_(4, vector<vector<double>>(4, vector<double>(4, 0))),
                                                            gameLogic_(){};

void Bot::setBoardState(const tuple<int, int, int> &playerInput)
{
    gameBoard_[get<0>(playerInput)][get<1>(playerInput)][get<2>(playerInput)] = playerC;
}

tuple<int, int, int> Bot::getMove()
{
    for (auto i = 0; i < 4; i++)
    {
        for (auto j = 0; j < 4; j++)
        {
            for (auto k = 0; k < 4; k++)
            {
                /*
                each position has a starting point value based on where it is

                board 1 and 4:  corner > edges > middle
                                  100     50       10
                board 2 and 3:  middle > edges > corner
                */
                if ((j == 0 || j == 3) && (k == 0 || k == 3))
                    allMoves_[i][j][k] = (i == 0 || i == 3) ? 100 : 10;
                else if (j == 0 || j == 3 || k == 0 || k == 3)
                    allMoves_[i][j][k] = 50;
                else
                    allMoves_[i][j][k] = (i == 0 || i == 3) ? 10 : 100;

                // the bot can't move somewhere that has a piece
                if (gameBoard_[i][j][k] != defaultC)
                    allMoves_[i][j][k] = INT32_MIN;
            }
        }
    }
    botScore();
    playerScore();

    auto move = findBestScore();
    gameBoard_[get<0>(move)][get<1>(move)][get<2>(move)] = botC;

    return move;
}

void Bot::botScore()
{
    auto combinations = gameLogic_.fourInARow();

    vector<vector<vector<bool>>> twoInARow(4, vector<vector<bool>>(4, vector<bool>(4, false)));
    for (auto moves : combinations)
    {
        int numInARow = 0;
        vector<tuple<int, int, int>> empty;
        for (auto move : moves)
        {
            if (gameBoard_[get<0>(move)][get<1>(move)][get<2>(move)] == botC)
                numInARow++;
            else if (gameBoard_[get<0>(move)][get<1>(move)][get<2>(move)] == playerC)
                numInARow = -10;
            else
                empty.push_back({get<0>(move), get<1>(move), get<2>(move)});
        }
        // if there is a winning move, nothing else matters, play that move
        if (numInARow == 3)
        {
            for (auto pos : empty)
            {
                allMoves_[get<0>(pos)][get<1>(pos)][get<2>(pos)] += INT32_MAX;
            }
        }
        else if (numInARow == 2)
        {
            for (auto pos : empty)
            {
                allMoves_[get<0>(pos)][get<1>(pos)][get<2>(pos)] += 50;
                if (!twoInARow[get<0>(pos)][get<1>(pos)][get<2>(pos)])
                {
                    twoInARow[get<0>(pos)][get<1>(pos)][get<2>(pos)] = true;
                }
                else
                {
                    allMoves_[get<0>(pos)][get<1>(pos)][get<2>(pos)] += INT16_MAX * 100;
                }
            }
        }

        else if (numInARow == 1)
        {
            for (auto pos : empty)
            {
                allMoves_[get<0>(pos)][get<1>(pos)][get<2>(pos)] += 20;
            }
        }
    }
}
void Bot::playerScore()
{
    // TODO next is if one empty square is in line with 2 sets of 2, it must be blocked. if not, the bot can easily be beaten by a little more complex of a plot
    auto combinations = gameLogic_.fourInARow();

    vector<vector<vector<bool>>> twoInARow(4, vector<vector<bool>>(4, vector<bool>(4, false)));

    for (auto moves : combinations)
    {
        int numInARow = 0;
        vector<tuple<int, int, int>> empty;
        for (auto move : moves)
        {
            if (gameBoard_[get<0>(move)][get<1>(move)][get<2>(move)] == playerC)
                numInARow++;
            else if (gameBoard_[get<0>(move)][get<1>(move)][get<2>(move)] == botC)
                numInARow = -10;
            else
                empty.push_back({get<0>(move), get<1>(move), get<2>(move)});
        }
        // the enemy winning is bad, but if a certain move lets you win, then this does not matter. Thus this must be lower, but less than the score added for winning
        if (numInARow == 3)
        {
            for (auto pos : empty)
            {
                allMoves_[get<0>(pos)][get<1>(pos)][get<2>(pos)] += INT16_MAX * 200;
            }
        }
        else if (numInARow == 2)
        {
            for (auto pos : empty)
            {
                allMoves_[get<0>(pos)][get<1>(pos)][get<2>(pos)] += 40;
                if (!twoInARow[get<0>(pos)][get<1>(pos)][get<2>(pos)])
                {
                    twoInARow[get<0>(pos)][get<1>(pos)][get<2>(pos)] = true;
                }
                else
                {
                    allMoves_[get<0>(pos)][get<1>(pos)][get<2>(pos)] += INT16_MAX * 50;
                }
            }
        }
    }
}

tuple<int, int, int> Bot::findBestScore()
{
    // TODO; for multiple moves of the same score, choose a random one. This lets the game be more erratic, and doesnt make the bot predicatble
    double bestScore = INT32_MIN;

    vector<tuple<int, int, int>> allBestMoves;

    for (auto i = 0; i < 4; i++)
    {
        for (auto j = 0; j < 4; j++)
        {
            for (auto k = 0; k < 4; k++)
            {
                if (allMoves_[i][j][k] > bestScore)
                {
                    bestScore = allMoves_[i][j][k];
                    allBestMoves.clear();
                    allBestMoves.push_back({i, j, k});
                }
                else if (allMoves_[i][j][k] == bestScore)
                {
                    allBestMoves.push_back({i, j, k});
                }
            }
        }
    }
    int index = rand() % allBestMoves.size();
    return allBestMoves[index];
}

Bot::~Bot(){};