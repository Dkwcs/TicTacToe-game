
#include <iostream>
#include "TicTacToeGame.h"

int main()
{
	std::unique_ptr<TicTacToeGame> ticTacToeGame = std::make_unique<TicTacToeGame>();
	ticTacToeGame->start();
}
