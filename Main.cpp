#include <iostream>
#include "TicTacToe.h"

int main()
{
	bool isInPlay = true;
	instructions();

	playGame();

	while (isInPlay)
	{
		char answer;
		std::cout << "Would you like to play again? (y/n): ";
		std::cin >> answer;

		if (answer == 'y')
			playGame();
		else
			isInPlay = false;
	}
}