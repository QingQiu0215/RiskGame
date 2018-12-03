#include <iostream>
#include "Strategy.h"
#include "StrategyBox.h"
using namespace std;

StrategyBox::StrategyBox() {};

StrategyBox::StrategyBox(Strategy *initStrategy) 
{
	this->strategy = initStrategy;
}
void StrategyBox::setStrategyBox(Strategy *newStrategy)
{
	this->strategy = newStrategy;
}
void StrategyBox::execute(vector <Player*> allPlayers, Deck* deckPtr, int armyQty_startup,int playerNum) 
{
	return this->strategy->execute(allPlayers, deckPtr, armyQty_startup,playerNum);
}