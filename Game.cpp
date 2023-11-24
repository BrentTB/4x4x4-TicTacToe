#include "Game.h"

Game::Game() : gameBoard_{}
{
}

void Game::startGame(const bool twoPlayer)
{
    useBot_ = !twoPlayer;
    xTurn_ = true;
    win_ = defaultChar;
    gameLoop();
}

Game::~Game() {}

void Game::gameLoop()
{
    while (win_ == defaultChar)
    {
        showBoard();
        getInput();
        if (checkWin(xTurn_ ? 'X' : 'O'))
        {
            win_ = xTurn_ ? 'X' : 'O';
        }
        xTurn_ = !xTurn_;
    }
    displayWin();
}

bool Game::checkWin(const char piece)
{
    // TODO: change the winning 4 to a different char or something so the player can see the win
    /*
    ways to win:
    4 in a row, column or board (equivalent to same column and board but different row)

    diagonals going from different row, col and board
    from same row but different col and board
    */

    // stores the board, row and column of each possible winning scenario

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
            if (checkPiece(piece, moves))
                return true;
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
            if (checkPiece(piece, moves))
                return true;

            // checking every row
            for (auto iter = 0; iter < 4; iter++)
            {
                moves[iter] = make_tuple(i, iter, j);
            }
            if (checkPiece(piece, moves))
                return true;

            // checking every board
            for (auto iter = 0; iter < 4; iter++)
            {
                moves[iter] = make_tuple(iter, j, i);
            }
            if (checkPiece(piece, moves))
                return true;
        }
    }

    // partially diagonal (2 variables change and one doesnt)

    return false;
}

bool Game::checkPiece(const char piece, vector<tuple<int, int, int>> &moves)
{
    for (auto move : moves)
    {
        if (gameBoard_.getPiece(get<0>(move), get<1>(move), get<2>(move)) != piece)
            return false;
    }

    for (auto &move : moves)
    {
        cout << get<0>(move) << " " << get<1>(move) << " " << get<2>(move) << " " << endl;
        gameBoard_.placeWinPiece(get<0>(move), get<1>(move), get<2>(move));
    }
    return true;
}

void Game::displayWin()
{
    showBoard();
    cout << "GAME OVER" << endl;
    cout << "The winner is: " << win_ << endl;
}

void Game::showBoard()
{
    cout << "\n\n\n\n-> " << (xTurn_ ? 'X' : 'O') << " to move\n"
         << endl;
    gameBoard_.printBoard();
}

void Game::getInput()
{
    cout << "-> Please enter your move in the following form: abc" << endl;
    cout << "  - a, b and c represent a number from 1 to 4" << endl;
    cout << "  - The first digit is the board (left board = 1)" << endl;
    cout << "  - The second digit is the row (top row = 1)" << endl;
    cout << "  - The third digit is the column (left column = 1)" << endl
         << endl;
    cout << "-> Please type 'exit' or 'e' to quit" << endl;

    string inp1;
    int board, row, col;

    cin >> inp1;

    if (isalpha(inp1[0]) && toupper(inp1[0]) == 'E')
    {
        cout << "Thank you for playing" << endl;
        exit(0);
    }
    try
    {
        auto val = stoi(inp1);
        board = val / 100 - 1;
        row = (val % 100) / 10 - 1;
        col = val % 10 - 1;

        gameBoard_.placePiece((xTurn_ ? 'X' : 'O'), board, row, col);
    }
    catch (invalid_argument &ex)
    {
        cout << "\n-> Please enter a valid location, 3 whole numbers\n"
             << endl;
        getInput();
        return;
    }
    catch (UsedSpot &ex)
    {
        cout << "\n-> Please enter a valid location, the chosen spot already has a piece\n"
             << endl;
        getInput();
        return;
    }
    catch (InvalidSpot &ex)
    {
        cout << "\n-> Please enter a valid location, each number must be between 1 and 4\n"
             << endl;
        getInput();
        return;
    }
    catch (exception &ex)
    {
        cout << "Unexpected error:\n"
             << ex.what() << endl;
        exit(1);
    }
}
