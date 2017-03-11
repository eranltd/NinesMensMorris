/*
 * Board.cpp
 *
 *  Created on: Nov 13, 2015
 *      Author: eran
 *      This class is the game board.
 */
#include "Board.h"
#include "Node.h"
class Node;
using namespace std;
/*That Function initialize the game board
 * creates empty dots and link them to each other*/
void Board::initialize() {
	Board::unusedDots[Node::WHITE] = 9; //reset the number of turns at the position stage
	Board::unusedDots[Node::BLACK] = 9; //reset the number of turns at the position stage
	Board::leftDots[Node::WHITE] = 0; //reset each player with 9 turns
	Board::leftDots[Node::BLACK] = 0; //reset each player with 9 turns
	/*Now sets dot by dot and link them*/

	for(int p=0;p<24;p++){
		Board::myBoard[p] = new Node(p); //Calling the constructor of each point.(no default constructor is exist)
	}
	//Linkin all the points(it is massy)
	myBoard[0]->down = myBoard[9];myBoard[0]->right = myBoard[1];
	myBoard[1]->left = myBoard[0];myBoard[1]->right = myBoard[2]; myBoard[1]->down = myBoard[4];
	myBoard[2]->left = myBoard[1];myBoard[2]->down = myBoard[14];
	myBoard[3]->right = myBoard[4];myBoard[3]->down = myBoard[10];
	myBoard[4]->up = myBoard[1];myBoard[4]->left = myBoard[3];myBoard[4]->right=myBoard[5];myBoard[4]->down = myBoard[7];
	myBoard[5]->left = myBoard[4];myBoard[5]->down=myBoard[13];
	myBoard[6]->right=myBoard[7];myBoard[6]->down=myBoard[11];
	myBoard[7]->up=myBoard[4];myBoard[7]->left=myBoard[6];myBoard[7]->right=myBoard[8];
	myBoard[8]->left=myBoard[7];myBoard[8]->down=myBoard[12];
	myBoard[9]->up=myBoard[0];myBoard[9]->down=myBoard[21];myBoard[9]->right=myBoard[10];
	myBoard[10]->left = myBoard[9]; myBoard[10]->right = myBoard[11]; myBoard[10]->up = myBoard[3]; myBoard[10]->down = myBoard[18];
	myBoard[11]->left = myBoard[10]; myBoard[11]->up = myBoard[6]; myBoard[11]->down = myBoard[15];
	myBoard[12]->right = myBoard[13]; myBoard[12]->up = myBoard[8]; myBoard[12]->down = myBoard[17];
	myBoard[13]->left = myBoard[12]; myBoard[13]->right = myBoard[14]; myBoard[13]->up = myBoard[5]; myBoard[13]->down = myBoard[20];
	myBoard[14]->left = myBoard[13]; myBoard[14]->up = myBoard[2]; myBoard[14]->down = myBoard[23];
	myBoard[15]->right = myBoard[16]; myBoard[15]->up = myBoard[11];
	myBoard[16]->left = myBoard[15]; myBoard[16]->right = myBoard[17]; myBoard[16]->down = myBoard[19];
	myBoard[17]->left = myBoard[16]; myBoard[17]->up = myBoard[12];
	myBoard[18]->right = myBoard[19]; myBoard[18]->up = myBoard[10];
	myBoard[19]->left = myBoard[18]; myBoard[19]->right = myBoard[20]; myBoard[19]->up = myBoard[16]; myBoard[19]->down = myBoard[22];
	myBoard[20]->left = myBoard[19]; myBoard[20]->up = myBoard[13];
	myBoard[21]->right = myBoard[22]; myBoard[21]->up = myBoard[9];
	myBoard[22]->left = myBoard[21]; myBoard[22]->right = myBoard[23]; myBoard[22]->up = myBoard[19];
	myBoard[23]->left = myBoard[22]; myBoard[23]->up = myBoard[14];

}
/*constructor : calls initialize function*/
Board::Board()
{
	Board::initialize();
}
//destrcutor
Board::~Board()
{
	for(int p=0;p<24;p++)
			delete(Board::myBoard[p]); //delete each point from Heap!
}
//That function Prints the Game Board
void Board::PrintBoard()
{
	cout << myBoard[0]->getPlayer() << " - - " << myBoard[1]->getPlayer()<< " - - " << myBoard[2]->getPlayer()<<endl<<endl;
	cout << "- " <<myBoard[3]->getPlayer()<<" - " <<myBoard[4]->getPlayer()<<" - "<<myBoard[5]->getPlayer() <<" -"<<endl<<endl;
	cout << "- - " <<myBoard[6]->getPlayer()<<' '<<myBoard[7]->getPlayer()<<' '<<myBoard[8]->getPlayer()<<" - -"<<endl<<endl;
	cout << myBoard[9]->getPlayer()<<' '<<myBoard[10]->getPlayer()<<' '<<myBoard[11]->getPlayer()<<" - "<<myBoard[12]->getPlayer()<<' '<<myBoard[13]->getPlayer()<<' '<<myBoard[14]->getPlayer()<<endl<<endl;
	cout << "- - " <<myBoard[15]->getPlayer()<<' '<<myBoard[16]->getPlayer()<<' '<<myBoard[17]->getPlayer()<<" - -"<<endl<<endl;
	cout << "- " <<myBoard[18]->getPlayer()<<" - " <<myBoard[19]->getPlayer()<<" - "<<myBoard[20]->getPlayer() <<" -"<<endl<<endl;
	cout << myBoard[21]->getPlayer() << " - - " << myBoard[22]->getPlayer()<< " - - " << myBoard[23]->getPlayer()<<endl<<endl;
}
//checks if the player has moves
bool Board::hasMove(Node::Player player)
{
	//we got the player color and now we will check his dots
	//if one of them has a neigbore dot empty
	//he can move
	//notice!that function has no position!
	//its checks all the player dots for available move
	int i=0;
	bool status = false;
	for(i=0;i<24;i++)
	{
		if(myBoard[i]->getPlayerRaw() == player)
		{
			//check 4 directions
			//if one of them is Neutral status will set to be true;
			if(myBoard[i]->up != NULL){
				if(myBoard[i]->up->getPlayerRaw() == Node::NEUTRAL) status = true;
			}
			if(myBoard[i]->down != NULL){
				if(myBoard[i]->down->getPlayerRaw() == Node::NEUTRAL) status = true;
			}
			if(myBoard[i]->right != NULL){
				if(myBoard[i]->right->getPlayerRaw() == Node::NEUTRAL) status = true;
			}
			if(myBoard[i]->left != NULL){
				if(myBoard[i]->left->getPlayerRaw() == Node::NEUTRAL) status = true;
			}
		}
	}
	return status;
	}
//That function set player color at a specific spot(Node's array is private)
void Board::setPlayer(int n,Node::Player x)
{
		if(n<24 && n>=0)
		{
			myBoard[n]->setPlayer(x);
		}
}
//gets the player at the n Node
std::string Board::getPlayer(int n)
{
				return Board::myBoard[n]->getPlayer();
}
//gets the player at the n Node(return Player)
Node::Player Board::getPlayerR(int n)
{
	return myBoard[n]->getPlayerRaw();
}
//checks if the player has a HorizontalTrio
bool Board::isVerticalTrio(int pos, Node::Player player){
	bool status = false;
	//Three options
	if(myBoard[pos]->up == NULL)
	{
		status = (myBoard[pos]->down->player == myBoard[pos]->down->down->player) && (myBoard[pos]->down->player == myBoard[pos]->player);
		//if it is true status will get 1(the dot is up)
	}
	if(myBoard[pos]->down == NULL){
		status = (myBoard[pos]->up->player == myBoard[pos]->up->up->player) && (myBoard[pos]->up->player == myBoard[pos]->player);
		//if it is true status will get 1(the dot is down)
	}
	if((myBoard[pos]->up != NULL)&&(myBoard[pos]->down != NULL)){
		status = (myBoard[pos]->up->player == myBoard[pos]->down->player) && (myBoard[pos]->up->player == myBoard[pos]->player);
	}//if it is true status will get 1(the dot is in the middle)



	return status;
}
//checks if the player has a VerticalTrio
bool Board::isHorizontalTrio(int pos, Node::Player player){
	bool status = false;
	//Three options
	if(myBoard[pos]->left == NULL)
	{
		status = (myBoard[pos]->right->player == myBoard[pos]->right->right->player) && (myBoard[pos]->right->player == myBoard[pos]->player);
		//if it is true status will get 1(the dot is on the left)
	}
	if(myBoard[pos]->right == NULL){
		status = (myBoard[pos]->left->player == myBoard[pos]->left->left->player) && (myBoard[pos]->left->player == myBoard[pos]->player);
		//if it is true status will get 1(the dot is on the right)
	}
	if((myBoard[pos]->right != NULL)&&(myBoard[pos]->left != NULL)){
		status = (myBoard[pos]->right->player == myBoard[pos]->right->player) && (myBoard[pos]->right->player == myBoard[pos]->player);
	}//if it is true status will get 1(the dot is in the middle)
	return status;
}
//checks if the player had trio
bool Board::isTrio(int pos, Node::Player player){
	if(isVerticalTrio(pos,player)==true)
	{
		return true;
	}
	else if(isHorizontalTrio(pos,player)==true){
		return true;
	}
	return false;
}
//checks if the move is legal(the point has the appropriate neighbore
bool Board::isNeighbor(int src,int dst)
{
	bool status = false;
	for(int i=0;i<24;i++)
	{
		if(myBoard[i]->getLocation() == src)
				{
					//check 4 directions
					//if one of them is the neighbore status will set to be true;
			if(myBoard[i]->up!=NULL)
			{
				if(myBoard[i]->up->getLocation() == dst) status = true;
			}
			if(myBoard[i]->down!=NULL)
			{
				if(myBoard[i]->down->getLocation() == dst) status = true;
			}
			if(myBoard[i]->right!=NULL)
			{
				if(myBoard[i]->right->getLocation() == dst) status = true;
			}
			if(myBoard[i]->left!=NULL)
			{
				if(myBoard[i]->left->getLocation() == dst) status = true;
			}
				}
	}
	return status;
}

