#include "Game.h"

Game::Game() : gameBoard_{}
{
}

void Game::startGame(const bool twoPlayer, const bool xFirst)
{
    useBot_ = !twoPlayer;
    xTurn_ = xFirst;
    win_ = defaultChar;
    input_ = make_tuple(-1, -1, -1);
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
            displayWin();
            break;
        }
        xTurn_ = !xTurn_;
        if(checkDraw())
        {
            displayDraw();
            break;
        }
    }
}

bool Game::checkWin(const char piece)
{
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
    for (auto i = 0; i < 4; i++)
    {
        for (auto j = 0; j < 2; j++)
        {
            // column is constant
            for (auto iter = 0; iter < 4; iter++)
            {
                moves[iter] = make_tuple(iter, abs(iter - 3 * j), i);
            }
            if (checkPiece(piece, moves))
                return true;

            // row is constant
            for (auto iter = 0; iter < 4; iter++)
            {
                moves[iter] = make_tuple(iter, i, abs(iter - 3 * j));
            }
            if (checkPiece(piece, moves))
                return true;

            // board is constant
            for (auto iter = 0; iter < 4; iter++)
            {
                moves[iter] = make_tuple(i, iter, abs(iter - 3 * j));
            }
            if (checkPiece(piece, moves))
                return true;
        }
    }

    return false;
}

bool Game::checkDraw()
{
    for (auto i = 0; i < 4; i++)
    {
        for (auto j = 0; j < 4; j++)
        {
            // checking every column
            for (auto k = 0; k < 4; k++)
            {
                if(gameBoard_.getPiece(i,j,k) == defaultChar)
                return false;
            }
        }
    }
    return true;
};

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

void Game::displayDraw()
{
    showBoard();
    cout << "GAME OVER" << endl;
    cout << "The game is a draw as all squares have been used without either player winning"<<endl;
}

void Game::showBoard()
{
    cout << "\033[2J\033[H";
    cout.flush();
    cout << "-> " << (xTurn_ ? 'X' : 'O') << " to move\n"
         << endl;
    gameBoard_.printBoard();
}

void Game::getInput()
{
    if (useBot_ && !xTurn_)
    {
        botMove();
        return;
    }

    cout << "-> Please enter your move in the following form: abc" << endl;
    cout << "  - a, b and c each represent a number from 1 to 4 inclusive" << endl;
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

void Game::botMove()
{
    // maybe add a small wait here with a message like 'thinking'
    if (get<0>(input_) != -1)
    {
        opponentAi_.setBoardState(input_);
    }
    auto move = opponentAi_.getMove();
    gameBoard_.placePiece('O', get<0>(move), get<1>(move), get<2>(move));
}
