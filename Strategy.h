#ifndef STRATEGY_H
#define STRATEGY_H

#include <iostream>
#include "Player.h"
#include "Deck.h"
using namespace std;

class Strategy
{
public:
	virtual void execute(vector <Player*> allPlayers, Deck* deckPtr, int armyQty_startup,int playerNum) = 0;
};

#endif