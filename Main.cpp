#include <iostream>
#include "TicTacToe.h"

int main()
{

	instructions();

	playGame();

	char answer;
	std::cout << "Would you like to play again? (y/n): ";
	std::cin >> answer;

	if (answer == 'y')
		playGame();

	// TODO: Implement a loop to enable play again function

}