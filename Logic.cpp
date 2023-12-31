#include "Logic.h"

Logic::Logic() : allMoves_()
{
}

AllMoves &Logic::fourInARow()
{

    if (allMoves_.size() != 0)
        return allMoves_;
    vector<tuple<int, int, int>> moves(4);

    // completely straight (one variable changes other 2 don't)
    for (auto i = 0; i < 4; i++)
    {
        for (auto j = 0; j < 4; j++)
        {
            // checking every column
            for (auto iter = 0; iter < 4; iter++)
            {
                moves[iter] = make_tuple(i, j, iter);
            }
            allMoves_.push_back(moves);

            // checking every row
            for (auto iter = 0; iter < 4; iter++)
            {
                moves[iter] = make_tuple(i, iter, j);
            }
            allMoves_.push_back(moves);

            // checking every board
            for (auto iter = 0; iter < 4; iter++)
            {
                moves[iter] = make_tuple(iter, j, i);
            }
            allMoves_.push_back(moves);
        }
    }

    // partially diagonal (2 variables change and one doesnt)
    for (auto i = 0; i < 4; i++)
    {
        for (auto j = 0; j < 2; j++)
        {
            // column is constant
            for (auto iter = 0; iter < 4; iter++)
            {
                moves[iter] = make_tuple(iter, abs(iter - 3 * j), i);
            }
            allMoves_.push_back(moves);

            // row is constant
            for (auto iter = 0; iter < 4; iter++)
            {
                moves[iter] = make_tuple(iter, i, abs(iter - 3 * j));
            }
            allMoves_.push_back(moves);

            // board is constant
            for (auto iter = 0; iter < 4; iter++)
            {
                moves[iter] = make_tuple(i, iter, abs(iter - 3 * j));
            }
            allMoves_.push_back(moves);
        }
    }

    // Completely diagonal (all 3 variables change)
    for (auto i = 0; i < 2; i++)
    {
        for (auto j = 0; j < 2; j++)
        {
            for (auto iter = 0; iter < 4; iter++)
            {
                moves[iter] = make_tuple(iter, abs(iter - 3 * i), abs(iter - 3 * j)); // 3*i - iter * (2*i-1)
            }
            allMoves_.push_back(moves);
        }
    }

    return allMoves_;
}

bool Logic::checkDraw(const Board &gameBoard, const char defaultChar)
{
    for (auto i = 0; i < 4; i++)
    {
        for (auto j = 0; j < 4; j++)
        {
            for (auto k = 0; k < 4; k++)
            {
                if (gameBoard.getPiece(i, j, k) == defaultChar)
                    return false;
            }
        }
    }
    return true;
}