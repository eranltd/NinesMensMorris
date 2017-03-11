/*
 * GameController.cpp
 *
 *  Created on: Nov 13, 2015
 *      Author: eran
 *      That Class resopnsible for "operating" the game"
 */
#include "GameController.h"
//creating empty board and init the vars
GameController::GameController() {
	this->myGame =  new Board();
	White_pos = 0; //the current position of white
	Black_pos = 0; //the current position of black
	White_name = "White";
	Black_name = "Black";
	currentTurn = Node::BLACK; //who is currently playing
	status = PLAYING;
	winner = Node::NEUTRAL;
}
//eats the rival player
void GameController::eatPlayer(Node::Player player)
{
	myGame->PrintBoard();
	string tempPoint;
	cout << "There is Three in sequence,remove the rival player!"<<endl<<"enter Cooardinate:"<<endl;
	cin >> tempPoint;
	int eatPos = ParsePostoInt(tempPoint);
	//if the input is outOfRange or the dot is occupied, try again
	while(eatPos == -1 || ((myGame->getPlayerR(eatPos)) == player))
	{
		cout << "Sorry,The Node does not belong to your rival"<<endl;
		cin >> tempPoint ;
		eatPos = ParsePostoInt(tempPoint);
	}
	myGame->setPlayer(eatPos,Node::NEUTRAL);
	myGame->decreaseLeftDots(player);
}
//checks if the dots is legal and convert it to pos(int),if it is illegal return -1;
void GameController::endGame()
{
	if(currentTurn == Node::WHITE)winner = Node::BLACK;
	else winner = Node::WHITE;
	delete(myGame);
	status=GAME_OVER;
}
void GameController::declareAndQuit(){

	/*END OF GAME declaring the winner*/
	if(winner == Node::WHITE)cout <<endl<< White_name<<"(White)" << " Won!"  <<endl;
	else cout <<endl<< Black_name<<"(Black)" << " Won!"  <<endl;
	/*prints the winner*/
	exit (EXIT_FAILURE);
}

//writes the current player position on board
void GameController::writecurrentPos(int pos,Node::Player player)
{
	if(player == Node::WHITE)White_pos=pos;
	else
		Black_pos=pos;
}
//changes the player after every move
void GameController::changePlayer(){
	if(this->currentTurn == Node::WHITE)this->currentTurn = Node::BLACK;
	else currentTurn = Node::WHITE;
	return;
}
//convert the user input to position on board
int ParsePostoInt(const std::string &s){
	string check="";
	check+=s;
	check[0]=towlower(check[0]); //convert uppercase to lower
	check[1]=towlower(check[1]); //for the number(not needed :)
	if(check.compare("a7") == 0)return 0;
	if(check.compare("d7") == 0)return 1;
	if(check.compare("g7") == 0)return 2;
	if(check.compare("b6") == 0)return 3;
	if(check.compare("d6") == 0)return 4;
	if(check.compare("f6") == 0)return 5;
	if(check.compare("c5") == 0)return 6;
	if(check.compare("d5") == 0)return 7;
	if(check.compare("e5") == 0)return 8;
	if(check.compare("a4") == 0)return 9;
	if(check.compare("b4") == 0)return 10;
	if(check.compare("c4") == 0)return 11;
	if(check.compare("e4") == 0)return 12;
	if(check.compare("f4") == 0)return 13;
	if(check.compare("g4") == 0)return 14;
	if(check.compare("c3") == 0)return 15;
	if(check.compare("d3") == 0)return 16;
	if(check.compare("e3") == 0)return 17;
	if(check.compare("b2") == 0)return 18;
	if(check.compare("d2") == 0)return 19;
	if(check.compare("f2") == 0)return 20;
	if(check.compare("a1") == 0)return 21;
	if(check.compare("d1") == 0)return 22;
	if(check.compare("g1") == 0)return 23;
	return (-1); //position is out of game!
}
//the Position phase
void GameController::GamePhase1(){
	myGame->PrintBoard();
	if(currentTurn == Node::WHITE)cout << White_name <<": ";
	else cout << Black_name <<": ";
	/*prints the player names turn by turn*/
	cin >> userInput ;
	if((userInput.compare("quit") == 0) || (userInput.compare("QUIT")==0)){endGame();return;}
	int pos = ParsePostoInt(userInput);
	//if the input is outOfRange or the dot is occupied, try again
	while(pos == -1 || ((myGame->getPlayerR(pos))!=Node::NEUTRAL))
	{
		cout << "Sorry,The Node is occupied / out of range"<<endl;
		cin >> userInput ;
		pos = ParsePostoInt(userInput);
	}
	/*************************************************/
	//put the dot
	myGame->setPlayer(pos,currentTurn);
	//write the current pos of player white\black
	writecurrentPos(pos,currentTurn);
	//decrease the unused dots counter per player
	myGame->decreaseunUsedDots(currentTurn);
	myGame->increaseLeftDots(currentTurn);
	//check if there is a mill
	if(myGame->isTrio(pos,currentTurn))
	{
		eatPlayer(currentTurn);
		myGame->PrintBoard();
	}
	//change turn
	changePlayer();
}
//the second phase of game
void GameController::GamePhase2()
{
	int src_pos = 0;
	int dst_pos = 0;
	cout <<endl<< "***Position stage***"<<endl;
	string src_dot = "a1";//2 chars length //sample
	string dst_dot = "a7";//2 chars length //sample
	myGame->PrintBoard();
	if(currentTurn == Node::WHITE)
	{
		cout << White_name <<": ";
	}
	else
	{
		cout << Black_name <<": ";
	}
	/*prints the player names turn by turn*/
	/***************************************************************/
	//if quit has been entered quit the game!
	/*checks the user input*/

	do{
		//as long the position is out of boundries \ illegal move
		//get into while
		getline(std::cin,userInput);
		//now we will break the user input into XX XX(seperated by space)
		src_dot[0] = userInput[0];
		src_dot[1] = userInput[1];
		dst_dot[0] = userInput[3];
		dst_dot[1] = userInput[4];
		//convert the char arrays to position(int)
		src_pos = ParsePostoInt(src_dot);
		dst_pos = ParsePostoInt(dst_dot);
		//quit
		if((userInput.compare("quit") == 0) || (userInput.compare("QUIT")==0)){
			endGame();
			return;
		}
		//quit
			if((src_pos == -1) || (dst_pos == -1))
			{
				cout <<"Please Try Again!"<<endl;
			}

	}while((src_pos == -1) || (dst_pos == -1) || userInput.length()>5);

	/****************************************************************/
	/****************************************************************/
	/****************************************************************/
	//lets check if the move is legal(the dot is not occupied)
	/*if not, return to phase2 again*/
	if((myGame->getPlayerR(src_pos) == Node::NEUTRAL))
	{
		cout <<endl<< "The Dot is not occupied by any player!" <<endl;
		return;
	}
	/*the point doesnt belong to you*/
	if((myGame->getPlayerR(src_pos) != currentTurn) && (myGame->getPlayerR(src_pos) != Node::NEUTRAL))
	{
		{
			cout <<endl<< "The Dot is doesn't belong to you!" <<endl;
			return;
		}
	}
	/*the DST point isn't empty*/
	if((myGame->getPlayerR(dst_pos) == Node::WHITE) ||(myGame->getPlayerR(dst_pos) == Node::BLACK))
	{
		{
			cout <<endl<< "The destination Dot is occupied by player!" <<endl;
			return;
		}
	}

	/*Enter check to see if the point is neigbore*/
	/*if not, return to phase2 again*/
	if((myGame->isNeighbor(src_pos,dst_pos) == false))
	{
		cout <<endl<< "The request dot is not adjacent" <<endl;
		return;
	}
	myGame->setPlayer(src_pos,Node::NEUTRAL);//Move the dot
	myGame->setPlayer(dst_pos,currentTurn);//Move the dot
	/*check if there is mill*/
	if(myGame->isTrio(dst_pos,currentTurn))
	{
		eatPlayer(currentTurn);
		myGame->PrintBoard();
	}
	//change turn
	changePlayer();
}
//the "main func"
void GameController::Game()
{
	status = PLAYING;
	cout << "Hi,Welcome to Nine Man's Morris" << endl <<endl;
	cout << "Please Enter the Black player name" <<endl;
	cout << "      Notice!the max Length is 16 characters with no spaces!"<<endl;
	cout << "      Example : LuciusVorenus" << endl;
	/*************************************************/
	std::getline(std::cin, Black_name);
	while(Black_name.find(" ")<16 || Black_name.length()>16 || Black_name.length()==0)
	{
		cout << "Sorry please try again :)";
		std::getline(std::cin, Black_name);
	}
	/*************************************************/
	cout << "Please Enter the White player name" <<endl;
	cout << "      Notice!the max Length is 16 characters with no spaces!"<<endl;
	cout << "      Example : LuciusVorenus" << endl;
	std::getline(std::cin, White_name);
	while(White_name.find(" ")<16 || White_name.length()>16 || White_name.length()== 0)
	{
		cout << "Sorry please try again :)";
		std::getline(std::cin, White_name);
	}
	/*************************************************/
	//as long as there is a dots to put and the input is different than "quit"
	//continue with phase1
	while(myGame->getUnusedDotsWhite() || myGame->getUnusedDotsBlack())
	{
		cout <<endl<< "The Black current dots on board:"<<myGame->getLeftDotsBlack()<<endl<<"The White current dots on board:"<<myGame->getLeftDotsWhite()<<endl;
		GamePhase1();
		if(status==GAME_OVER)
		{
			declareAndQuit(); //if the player enter QUIT
		}
	}
	/*Phase 1 of the game completed*/
	//lets sets the Black to be first
	currentTurn = (Node::BLACK);
	status = PLAYING;
	cout << "Position phase of the game completed,starting phase 2..." <<endl;
	for(int i=0;i<56;i++)
	{
		cout << ".";
	}
	cout<<endl;
	
	//as long as two player has eligble moves and 3 dots and up
	userInput.clear(); //clear the string
	//clean the buffer
	cin.clear();
	cin.ignore();
	while((myGame->getLeftDotsBlack()>=3) || (myGame->getLeftDotsWhite()>=3) || (myGame->hasMove(Node::WHITE)) || (myGame->hasMove(Node::BLACK)))
	{
		GamePhase2();
		if(status==GAME_OVER)
		declareAndQuit(); //if the player enter QUIT
	}

	if(myGame->hasMove(Node::WHITE)==false || myGame->getLeftDotsWhite()<3)
	{
		status = BLACK_WINS;
	}
	else
	{
		status = WHITE_WINS;
	}
	/*sets who won the game*/
	if(status == WHITE_WINS)winner = Node::WHITE;
	else winner = Node::BLACK;
	declareAndQuit();
}

void GameController::sixMovesonly()//for testing method only!
{
	this->GamePhase1();//testing
	this->GamePhase1();//testing
	this->GamePhase1();//testing
	this->GamePhase1();//testing
	this->GamePhase1();//testing
	this->GamePhase1();//testing
}
