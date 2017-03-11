/*
 * GameController.h
 *
 *  Created on: Nov 13, 2015
 *      Author: eran
 */

#ifndef GAMECONTROLLER_H_
#define GAMECONTROLLER_H_
#include "nine.h"
#include <cstring>
#include <stdlib.h>
int ParsePostoInt(const std::string &s);//checks if the dots is legal and convert it to pos
class GameController {
private:
		int White_pos; //the current position of white
		int Black_pos; //the current position of black
		std::string White_name; //stores the name of the player
		std::string Black_name; //stores the name of the player
		Node::Player currentTurn; //who is currenty playing
		Node::Player winner; //who won the game!
public:
	enum GameStatus {
			WHITE_WINS,
			BLACK_WINS,
			GAME_OVER,
			PLAYING
			};
	Board *myGame; //my Board for the game
	std::string userInput; //used for user input during the game
	GameController(); //calling the Board Constructor
	GameStatus status;
	void changePlayer();//change player
	void writecurrentPos(int pos,Node::Player player);//writes the current player position on board
	void movePlayer();//move player(phase2)
	void eatPlayer(Node::Player player);//eats the opponent player
	void endGame();//ends the game from anypoint using "quit" syntax
	void declareAndQuit(); //declare the winner and stop the program
	void Game(); //gets info from users and start the 2 phases of game
	void GamePhase1(); //the first phase of the game (position phase)
	void GamePhase2(); //the second phase of game(play's phase)
	void sixMovesonly(); //for testing method only!
};

#endif /* GAMECONTROLLER_H_ */
