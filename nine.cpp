/*
 * nine.cpp
 *
 *  Created on: Nov 13, 2015
 *      Author: eran
 */
//the main class that runs and manage the game

#include "nine.h"

int main()
{
	GameController *t1 = new GameController();
	t1->Game();
	delete(t1);
	return 0;
}
