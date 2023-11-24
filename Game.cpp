#include "Game.h"

Game::Game(): gameBoard_{}
{
}

void Game::startGame(bool twoPlayer)
{
    useBot_ = !twoPlayer;
    xTurn_=true;
    win_=defaultChar;
    gameLoop();
}

Game::~Game(){}

Game::gameLoop()
{




}
void Game::move(){}
