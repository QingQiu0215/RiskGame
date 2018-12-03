//-----------------------------------
//Written by:Qing Qiu, 40022237
//For COMP 345 Fall 2018
//-----------------------------------
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm> 
using namespace std;
#include "Player.h"

Player::Player(Map* selectedMap, int newplayerNum)
{
	playerNumber = 0;
	startupArmyQty = 0;
	mapPtr = selectedMap;
	myDicePtr = new Dice();//create a Dice object and a pointer to point it
	handPtr = new Hand();//create a Hand object and a pointer to point it
	playerNum = newplayerNum;
}
Player::Player()
{
	playerNumber = 0;
	startupArmyQty = 0;
}
int Player::getPlayerNum()
{
	return playerNumber;
}
void Player::setPlayerNum(int newplayerNumber)
{
	playerNumber = newplayerNumber;
}

void Player::setStartupArmyQty(int troop)
{
	startupArmyQty = troop;
}
void Player::setArmyQty_numberOfCountry(int newArmyQty_numberOfCountry)
{
	armyQty_numberOfCountry = newArmyQty_numberOfCountry;
}
void Player::setArmyQty_continentValue(int newArmyQty_continentValue)
{
	armyQty_continentValue = newArmyQty_continentValue;
}
void Player::setArmyQty_exchangeCard(int newArmyQty_exchangeCard)
{
	armyQty_exchangeCard = newArmyQty_exchangeCard;
}
void Player::setReinforcementArmyQty(int newReinforcementArmyQty)
{
	reinforcementArmyQty = newReinforcementArmyQty;
}

int Player::getStartupArmyQty()
{
	return startupArmyQty;
}
int Player::getArmyQty_numberOfCountry()
{
	return armyQty_numberOfCountry;
}
int Player::getArmyQty_continentValue()
{
	return armyQty_continentValue;
}
int Player::getArmyQty_exchangeCard()
{
	return armyQty_exchangeCard;
}
int Player::getReinforcementArmyQty()
{
	return reinforcementArmyQty;
}
//display all the cards in my hand
void Player::displayMyHand()
{
	int handQty = playerHand.size();
	if (handQty == 0)
		cout << "Your hand is empty." << endl;
	else
	{
		for (int i = 0; i < handQty; i++)
		{
			cout << playerHand[i].getType() << ",";
		}
		cout << endl;
	}
}
vector<string> Player::getTemp_neighborCountries()
{
	return temp_neighborCountries;
}
vector<string> Player::getTemp_neighborCountries_inFortification()
{
	return temp_neighborCountries_inFortification;
}
//clear the vector because it should be empty for storing neighbor countries for the next turn
void Player::clearTemp_neighborCountries()
{
	temp_neighborCountries.clear();
}
void Player::clearTemp_neighborCountries_inFortification()
{
	temp_neighborCountries_inFortification.clear();
}

Map* Player::getMapPtr()
{
	return mapPtr;
}
Hand* Player::getHandPtr()
{
	return handPtr;
}
Dice* Player::getMyDicePtr()
{
	return myDicePtr;
}
vector<int> Player::getDiceArray()
{
	return diceArray;
}
//copy the dice vector from Dice to the player and sort all elements in descending order.
void Player::setDiceArray()
{
	vector<int> temp;
	for (int i = 0; i < myDicePtr->getRollArray().size(); i++)
	{
		temp.push_back(myDicePtr->getRollArray()[i]);
	}
	sort(temp.begin(), temp.end());
	for (int i = temp.size() - 1; i >= 0; i--)
	{
		diceArray.push_back(temp[i]);
	}
}
void Player::clearDiceArray()
{
	diceArray.clear();
}
//push a neighbor into the temp vector
void Player::fillTemp_neighborCountries(string countryName)
{
	temp_neighborCountries.push_back(countryName);
}
void Player::fillTemp_neighborCountries_inFortification(string countryName)
{
	temp_neighborCountries_inFortification.push_back(countryName);
}
vector<Card> Player::getPlayerHand()
{
	return playerHand;
}
//copy a hand from Hand object to this player and clean the vector in Hand object
void Player::setPlayerHand()
{
	for (int i = 0; i < handPtr->size(); i++)
	{
		playerHand.push_back(handPtr->getHand()[i]);
	}
	handPtr->clearHand();
}
//exchange a card in the reinforcement phase
void Player::exchange(int index)
{
	if (index >= playerHand.size())
	{
		cout << "wrong number!" << endl;
	}
	else
	{
		playerHand.erase(playerHand.begin() + index);//delete the card in the hand
	}
}

string Player::getPlayerName()
{
	return playerName;
}
void Player::setPlayerName(string newPlayerName)
{
	playerName = newPlayerName;
}
Player::~Player()
{
	delete mapPtr;
	delete handPtr;
}


