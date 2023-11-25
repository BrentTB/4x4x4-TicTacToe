#include "Game.h"

Game::Game() : gameBoard_(defaultChar, winChar), gameLogic_(pl1, pl2, defaultChar), opponentAi_(pl1, pl2, defaultChar)
{
    srand(0);
    // srand(time(0));
}

void Game::startGame(const bool twoPlayer, const bool xFirst)
{
    useBot_ = !twoPlayer;
    xTurn_ = xFirst;
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

        if (checkWin(xTurn_ ? pl1 : pl2))
        {
            win_ = xTurn_ ? pl1 : pl2;
            displayWin();
            break;
        }
        xTurn_ = !xTurn_;
        if (gameLogic_.checkDraw(gameBoard_))
        {
            displayDraw();
            break;
        }
    }
}

bool Game::checkWin(const char piece)
{
    auto combinations = gameLogic_.fourInARow();

    for (auto moves : combinations)
    {
        bool win = true;
        for (auto move : moves)
        {
            if (gameBoard_.getPiece(get<0>(move), get<1>(move), get<2>(move)) != piece)
                win = false;
        }
        if (!win)
            continue;

        for (auto &move : moves)
        {
            gameBoard_.placeWinPiece(get<0>(move), get<1>(move), get<2>(move));
        }
        return true;
    }
    return false;
}

void Game::displayWin()
{
    showBoard();
    cout << "GAME OVER" << endl;
    cout << "The winner is: " << win_ << endl;

    for (auto x : allInput_)
    {
        cout << (get<0>(x) + 1) << (get<1>(x) + 1) << (get<2>(x) + 1) << endl;
    }
}

void Game::displayDraw()
{
    showBoard();
    cout << "GAME OVER" << endl;
    cout << "The game is a draw as all squares have been used without either player winning" << endl;
}

void Game::showBoard()
{
    // cout << "\033[2J\033[H";
    // cout.flush();
    cout << "-> " << (xTurn_ ? pl1 : pl2) << " to move\n"
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

        gameBoard_.placePiece((xTurn_ ? pl1 : pl2), board, row, col);
        allInput_.push_back({board, row, col});
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
    if (allInput_.size() != 0)
    {
        opponentAi_.setBoardState(allInput_.back());
    }
    auto move = opponentAi_.getMove();
    gameBoard_.placePiece('O', get<0>(move), get<1>(move), get<2>(move));
}
