//-----------------------------------
//Written by:Qing Qiu, 40022237
//For COMP 345 Fall 2018
//-----------------------------------
#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
using namespace std;
#include <vector>
#include "MapLoader.h"
#include "Map.h"
#include "CountryNode.h"
#include "ContinentNode.h"
#include "Dice.h"
#include "Hand.h"

class Player
{
public:
	Player(Map* map, int newplayerNum);
	Player();
	int getPlayerNum();
	int getStartupArmyQty();
	int getArmyQty_numberOfCountry();
	int getArmyQty_continentValue();
	int getArmyQty_exchangeCard();
	int getReinforcementArmyQty();
	Map* getMapPtr();
	void setPlayerNum(int i);
	void setStartupArmyQty(int troop);
	void setArmyQty_numberOfCountry(int playerNumber);
	void setArmyQty_continentValue(int playerNumber);
	void setArmyQty_exchangeCard(int newArmyQty_exchangeCard);
	void setReinforcementArmyQty(int newReinforcementArmyQty);
	vector<string> getTemp_neighborCountries();
	void clearTemp_neighborCountries();
	vector<string> getTemp_neighborCountries_inFortification();
	void clearTemp_neighborCountries_inFortification();
	vector<int> getDiceArray();
	void setDiceArray();
	void clearDiceArray();
	void fillTemp_neighborCountries(string countryName);
	void fillTemp_neighborCountries_inFortification(string countryName);
	vector<Card> getPlayerHand();
	void setPlayerHand();
	void exchange(int index);

	Dice* getMyDicePtr();
	Hand* getHandPtr();
	void displayMyHand();

	string getPlayerName();
	void setPlayerName(string newPlayerName);
	~Player();
private:
	int playerNumber;

	int startupArmyQty;
	int armyQty_numberOfCountry;
	int armyQty_continentValue;
	int armyQty_exchangeCard;
	int reinforcementArmyQty;

	vector<string> temp_neighborCountries;
	vector<string> temp_neighborCountries_inFortification;
	vector<int> diceArray;

	Map* mapPtr = nullptr;
	Dice* myDicePtr;
	Hand* handPtr = nullptr;
	vector<Card> playerHand;
	int playerNum;
	string playerName;
};

#endif

