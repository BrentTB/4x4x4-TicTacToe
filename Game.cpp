#include "Game.h"

Game::Game() : gameBoard_{}
{
}

void Game::startGame(bool twoPlayer)
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

    xTurn_ = !xTurn_;
    }
}

void Game::showBoard()
{
    cout << endl<<endl<<endl<<endl;
    cout <<"-> "<<(xTurn_? 'X' : 'O')<< " to move"<<endl<<endl;;
    gameBoard_.printBoard();
}

void Game::getInput()
{
    cout << "-> Please enter your move in the following form: abc" << endl;
    cout << "  - a, b and c represent a number from 1 to 4" << endl;
    cout << "  - The first digit is the board (left board = 1)" << endl;
    cout << "  - The second digit is the row (top row = 1)" << endl;
    cout << "  - The third digit is the column (left column = 1)" << endl<<endl;
    cout << "-> Please type 'exit' or 'e' to quit" << endl;

    string inp1;
    int board,row,col;

    cin >> inp1;

    if(isalpha(inp1[0]) && toupper(inp1[0])=='E'){
    exit(0);
    }
    try{
        auto val = stoi(inp1);
        board = val/100-1;
        row = (val%100)/10-1;
        col = val%10-1;

        gameBoard_.placePiece((xTurn_? 'X' : 'O'), board, row, col);

    }catch (invalid_argument &ex)
    {
        cout << endl<<"-> Please enter a valid location, 3 whole numbers"<<endl<<endl;
        getInput();
        return;
    } catch(UsedSpot & ex)
    {
        cout << endl<<"-> Please enter a valid location, the chosen spot already has a piece"<<endl<<endl;
        getInput();
        return;
    }catch(InvalidSpot & ex)
    {
        cout << endl<<"-> Please enter a valid location, each number must be between 1 and 4"<<endl<<endl;
        getInput();
        return;
    }catch(exception &ex)
    {
        cout << "Unexpected error: "<<ex.what()<<endl;
        exit(1);
    }

}

void Game::move() {}
