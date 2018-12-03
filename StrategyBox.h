#ifndef STRATEGY_BOX_H
#define STRATEGY_BOX_H
#include <iostream>
#include <vector>
#include "Deck.h"
#include "Player.h"
#include "Strategy.h"
using namespace std;

class StrategyBox 
{
public:
	StrategyBox();
	StrategyBox(Strategy *initStrategy);
	void setStrategyBox(Strategy *newStrategy);
	void execute(vector <Player*> allPlayers, Deck* deckPtr, int armyQty_startup,int playerNum);
private:
	Strategy *strategy;
};
#endif