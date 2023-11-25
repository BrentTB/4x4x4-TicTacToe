#include "Logic.h"

Logic::Logic(char pl1, char pl2, char defaultChar) : allMoves_(), pl1_(pl1), pl2_(pl2), defaultChar_(defaultChar)
{
}

AllMoves Logic::fourInARow()
{

    cout << "1a" << endl;
    if (allMoves_->size() != 0)
        return allMoves_;
    cout << "2a" << endl;
    vector<tuple<int, int, int>> moves(4);

    // Completely diagonal (all 3 variables change)
    for (auto i = 0; i < 2; i++)
    {
        for (auto j = 0; j < 2; j++)
        {
            for (auto iter = 0; iter < 4; iter++)
            {
                moves[iter] = make_tuple(iter, abs(iter - 3 * i), abs(iter - 3 * j));
            }
            cout << "3a" << endl;
            allMoves_->push_back(moves);
            cout << "4a" << endl;
        }
    }

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
            allMoves_->push_back(moves);

            // checking every row
            for (auto iter = 0; iter < 4; iter++)
            {
                moves[iter] = make_tuple(i, iter, j);
            }
            allMoves_->push_back(moves);

            // checking every board
            for (auto iter = 0; iter < 4; iter++)
            {
                moves[iter] = make_tuple(iter, j, i);
            }
            allMoves_->push_back(moves);
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
            allMoves_->push_back(moves);

            // row is constant
            for (auto iter = 0; iter < 4; iter++)
            {
                moves[iter] = make_tuple(iter, i, abs(iter - 3 * j));
            }
            allMoves_->push_back(moves);

            // board is constant
            for (auto iter = 0; iter < 4; iter++)
            {
                moves[iter] = make_tuple(i, iter, abs(iter - 3 * j));
            }
            allMoves_->push_back(moves);
        }
    }

    return allMoves_;
}

bool Logic::checkDraw(const Board &gameBoard)
{
    for (auto i = 0; i < 4; i++)
    {
        for (auto j = 0; j < 4; j++)
        {
            // checking every column
            for (auto k = 0; k < 4; k++)
            {
                if (gameBoard.getPiece(i, j, k) == defaultChar_)
                    return false;
            }
        }
    }
    return true;
}