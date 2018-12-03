#include <iostream>
#include <time.h>
#include <algorithm> 
#include "Strategy_benevolentC.h"
#include "Player.h"
using namespace std;

//************************************************************************************************************************
//*******************************The following are part 2-Phase observer**************************************************
//************************************************************************************************************************
class Subject3 {
	// 1. "independent" functionality
	vector < class Observer * > views; // 3. Coupled only to "interface"
	string phase;
public:
	void attach(Observer *obs) {
		views.push_back(obs);
	}
	void setVal(string val) {
		phase = val;
		notify();
	}
	string getVal() {
		return phase;
	}
	void notify();
};

class Observer {
	// 2. "dependent" functionality
	Subject3 *model;
	string phaseName;
public:
	Observer(Subject3 *sub, string str) {
		model = sub;
		phaseName = str;
		// 4. Observers register themselves with the Subject
		model->attach(this);
	}
	virtual void update() = 0;
protected:
	Subject3 *getSubject() {
		return model;
	}
	string getDivisor() {
		return phaseName;
	}
};

void Subject3::notify() {
	// 5. Publisher broadcasts
	for (int i = 0; i < views.size(); i++)
		views[i]->update();
}

class ReinforceObserver : public Observer {
public:
	ReinforceObserver(Subject3 *sub, string str) : Observer(sub, str) {}
	void update() {
		// 6. "Pull" information of interest
		if (getSubject()->getVal() == "Reinforcement")
			cout << "********************************This is the " << getSubject()->getVal() << " phase.************************************" << endl;
	}
};

class AttackObserver : public Observer {
public:
	AttackObserver(Subject3 *sub, string str) : Observer(sub, str) {}
	void update() {
		// 6. "Pull" information of interest
		if (getSubject()->getVal() == "Attack")
			cout << "*******************************This is the " << getSubject()->getVal() << " phase.***********************************" << endl;
	}
};
class FortifyObserver : public Observer {
public:
	FortifyObserver(Subject3 *sub, string str) : Observer(sub, str) {}
	void update() {
		// 6. "Pull" information of interest
		if (getSubject()->getVal() == "Fortify")
			cout << "*****************************This is the " << getSubject()->getVal() << " phase.***********************************" << endl;
	}
};


void Strategy_benevolentC::execute(vector <Player*> allPlayers, Deck* deckPtr, int armyQty_startup, int playerNum)
{
	Subject3 subj;
	new ReinforceObserver(&subj, "Reinforcement"); // 7. Client configures the number and
	new AttackObserver(&subj, "Attack"); //    type of Observers
	new FortifyObserver(&subj, "Fortify");
	cout << "**********************************************Player"<< playerNum <<"***************************************************" << endl;
	subj.setVal("Reinforcement");
	reinforce(allPlayers, deckPtr, armyQty_startup, playerNum);

	cout << "**********************************************Player" << playerNum << "************************************************" << endl;
	subj.setVal("Attack");
	attack(allPlayers, deckPtr,playerNum);

	cout << "**********************************************Player" << playerNum << "*************************************************" << endl;
	subj.setVal("Fortify");
	fortify(allPlayers, playerNum);
}

//***********************************************************************************************************
//**********************************Part2 end here***********************************************************
//***********************************************************************************************************

//start reinforce phase
void Strategy_benevolentC::reinforce(vector <Player*> allPlayers, Deck* deckPtr, int armyQty_startup, int playerNum)
{
	makeArmyQty_numberOfCountry(allPlayers, playerNum);
	makeArmyQty_continentValue(allPlayers, playerNum);
	makeArmyQty_exchangeCard(allPlayers, playerNum);
	makeReinforcementArmyQty(allPlayers, playerNum);
	distributeArmy_reinforcement(allPlayers, armyQty_startup, playerNum);
}
//number of countries owned on the map, divided by 3(round down), with a minimum of 3
void Strategy_benevolentC::makeArmyQty_numberOfCountry(vector <Player*> allPlayers, int playerNum)
{
	int countryNum = 0;
	for (int i = 0; i < (allPlayers[playerNum-1]->getMapPtr()->getCountry()).size(); i++)
	{
		if ((allPlayers[playerNum - 1]->getMapPtr()->getCountry())[i]->getPlayerNum() == playerNum)
			countryNum++;
	}
	int temp = 0;
	temp = floor(countryNum / 3);
	temp > 3 ? (allPlayers[playerNum - 1]->setArmyQty_numberOfCountry(allPlayers[playerNum - 1]->getArmyQty_numberOfCountry() + temp))
		: (allPlayers[playerNum - 1]->setArmyQty_numberOfCountry(allPlayers[playerNum - 1]->getArmyQty_numberOfCountry() + 3));
}
//Continent-control value of all continents totally controlled by the player.
void Strategy_benevolentC::makeArmyQty_continentValue(vector <Player*> allPlayers, int playerNum)
{
	int temp_countryQtyInTheContinent;
	int count = 0;
	int sizeContinent = allPlayers[playerNum - 1]->getMapPtr()->getTotalNumOfContinent();
	int sizeCountry = allPlayers[playerNum - 1]->getMapPtr()->getCountry().size();
	for (int i = 0; i < sizeContinent; i++)
	{
		temp_countryQtyInTheContinent = allPlayers[playerNum - 1]->getMapPtr()->getLoaderPtr()->getContinentContainCountries()[i].size() - 1;
		for (int j = 0; j < sizeCountry; j++)
		{
			bool bool1 = allPlayers[playerNum - 1]->getMapPtr()->getCountry()[j]->getContinent() ==
				allPlayers[playerNum - 1]->getMapPtr()->getLoaderPtr()->getContinentContainCountries()[i][0];
			bool bool2 = allPlayers[playerNum - 1]->getMapPtr()->getCountry()[j]->getPlayerNum() == playerNum ;
			if (bool1&&bool2)
				count++;
		}
		if (count == temp_countryQtyInTheContinent)
		{
			int i;
			for (i = 0; i < sizeContinent; i++)
			{
				if (allPlayers[playerNum - 1]->getMapPtr()->getLoaderPtr()->getContinentContainCountries()[i][0] ==
					allPlayers[playerNum - 1]->getMapPtr()->getLoaderPtr()->getMapInfo_continent()[i][0])
					break;
			}
			int num = stoi(allPlayers[playerNum - 1]->getMapPtr()->getLoaderPtr()->getMapInfo_continent()[i][1]);
			allPlayers[playerNum - 1]->setArmyQty_continentValue(num);
		}
	}
}
//Armies resulting in card exchange, if possible. If a player owns more than 5 cards, it must exchange cards.
void Strategy_benevolentC::makeArmyQty_exchangeCard(vector <Player*> allPlayers, int playerNum)
{
	int size = allPlayers[playerNum - 1]->getPlayerHand().size();
	if (size >= 5)
	{
		cout << "Player" << playerNum  << " exchanges all its cards for armies." << endl;
		int count = size;
		for (int i = 0; i < size; i++)
		{
			allPlayers[playerNum - 1]->exchange(count - 1);
			int quantity = (i + 1) * 5;
			allPlayers[playerNum - 1]->setArmyQty_exchangeCard(allPlayers[playerNum - 1]->getArmyQty_exchangeCard() + quantity);
			count--;
		}
	}
	else if (size < 3)
	{
		cout << "Player" << playerNum  << " cannot exchange cards." << endl;
		cout << "Because the player owns three cards of different sorts or the same sorts, he can exchange them for armies. " << endl;
	}
	else
	{
		int count_duplicate = 0;
		for (int i = 0; i < size - 1; i++)
		{
			for (int j = 1; j < size; j++)
			{
				if (allPlayers[playerNum - 1]->getPlayerHand()[i].getType() == allPlayers[playerNum - 1]->getPlayerHand()[j].getType())
					count_duplicate++;
			}
		}

		if (size - count_duplicate < 3)
		{
			cout << "Player" << playerNum  << " cannot exchange cards." << endl;
			cout << "Because the player owns three cards of different sorts or the same sorts, he can exchange them for armies. " << endl;
		}
		else
		{
			cout << "Player" << playerNum  << " exchanges all its cards for armies." << endl;
			int count = size;
			for (int i = 0; i < size; i++)
			{
				allPlayers[playerNum - 1]->exchange(count - 1);
				int quantity = (i + 1) * 5;
				allPlayers[playerNum - 1]->setArmyQty_exchangeCard(allPlayers[playerNum - 1]->getArmyQty_exchangeCard() + quantity);
				count--;
			}
		}

	}
}
//get total quantity of armies in the reinforcement phase.
void Strategy_benevolentC::makeReinforcementArmyQty(vector <Player*> allPlayers, int playerNum)
{
	int qty = allPlayers[playerNum - 1]->getArmyQty_numberOfCountry() +
		allPlayers[playerNum - 1]->getArmyQty_continentValue() +
		allPlayers[playerNum - 1]->getArmyQty_exchangeCard();
	allPlayers[playerNum - 1]->setReinforcementArmyQty(allPlayers[playerNum - 1]->getReinforcementArmyQty() + qty);
}

//distribute armies for a specific player.
void Strategy_benevolentC::distributeArmy_reinforcement(vector <Player*> allPlayers, int armyQty_startup, int playerNum)
{
	int countryNum = 0;
	for (int i = 0; i < (allPlayers[playerNum - 1]->getMapPtr()->getCountry()).size(); i++)
	{
		if ((allPlayers[playerNum - 1]->getMapPtr()->getCountry())[i]->getPlayerNum() == playerNum)
			countryNum++;
	}
	if (countryNum == 0)
	{
		cout << "Player" << playerNum << " has not any country. " << endl;
		return;
	}
	//displayMyCountry(allPlayers, playerNum);
	armyQtytoDistribute = allPlayers[playerNum - 1]->getReinforcementArmyQty();
	int index_smallestArmyQty = findCountryIndex_smallestArmyQty(allPlayers,playerNum );
	(allPlayers[playerNum - 1]->getMapPtr()->getCountry())[index_smallestArmyQty]->setNumberOfArmies((allPlayers[playerNum - 1]->
		getMapPtr()->getCountry())[index_smallestArmyQty]->getNumOfArmies() + armyQtytoDistribute);

	allPlayers[playerNum - 1]->setReinforcementArmyQty(0);
	cout << "Player" << playerNum  << " distributed armies for "<< allPlayers[playerNum - 1]->getMapPtr()->getCountry()[index_smallestArmyQty]->getCountry() << endl;
	//displayMyCountry(allPlayers, playerNum);
}
int Strategy_benevolentC::findCountryIndex_smallestArmyQty(vector <Player*> allPlayers, int playerNum)
{
	int size = allPlayers[playerNum - 1]->getMapPtr()->getTotalNumOfCountry();
	int minQtyOfArmy = 100;
	for (int i = 0; i < size; i++)
	{
		if ((allPlayers[playerNum - 1]->getMapPtr()->getCountry())[i]->getNumOfArmies() < minQtyOfArmy && (allPlayers[playerNum - 1]->getMapPtr()->getCountry())[i]->getPlayerNum() == playerNum )
			minQtyOfArmy = (allPlayers[playerNum - 1]->getMapPtr()->getCountry())[i]->getNumOfArmies();
	}
	for (int j = 0; j < size; j++)
	{
		if ((allPlayers[playerNum - 1]->getMapPtr()->getCountry())[j]->getPlayerNum() == playerNum && (allPlayers[playerNum - 1]->getMapPtr()->getCountry())[j]->getNumOfArmies() == minQtyOfArmy)
			return j;
	}
}

void Strategy_benevolentC::displayMyCountry(vector <Player*> allPlayers, int playerNum)
{
	cout << "Player " << playerNum << " has the following countries(country name,continent name,player number, quantity of armies):" << endl;
	for (int i = 0; i < (allPlayers[playerNum - 1]->getMapPtr()->getCountry()).size(); i++)
	{
		if ((allPlayers[playerNum - 1]->getMapPtr()->getCountry())[i]->getPlayerNum() == playerNum)
			cout << (allPlayers[playerNum - 1]->getMapPtr()->getCountry())[i]->displayCountry();
	}
	cout << endl;
}
//***********************************************************************************************************
//**********************************The followings are Part5*************************************************
//***********************************************************************************************************

//start attack, the player can select as many as times it wants.
void Strategy_benevolentC::attack(vector <Player*> allPlayers, Deck* deckPtr, int playerNum)
{
	cout << "Player" << playerNum << " never attack." << endl;
}

bool Strategy_benevolentC::checkGameOver(vector <Player*> allPlayers, int playerNum)
{
	int size = allPlayers[playerNum - 1]->getMapPtr()->getTotalNumOfCountry();
	int playerNum1 = allPlayers[playerNum - 1]->getMapPtr()->getCountry()[0]->getPlayerNum();
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (allPlayers[playerNum - 1]->getMapPtr()->getCountry()[i]->getPlayerNum() == playerNum1)
			count++;
	}
	if (count == size)
	{
		cout << "Game over. Player" << playerNum1 << " conquered all the countries." << endl;
		cout << "********************************Game over******************************" << endl;
		return true;
	}
	return false;
}
//***********************************************************************************************************
//**********************************The followings are Part6*************************************************
//***********************************************************************************************************

//starting fortify armies.The player can decide go on or not.
void Strategy_benevolentC::fortify(vector <Player*> allPlayers, int playerNum)
{
	int index_targetCountry = findCountryIndex_smallestArmyQty(allPlayers, playerNum);
	string targetCountryName = (allPlayers[playerNum - 1]->getMapPtr()->getCountry())[findCountryIndex_smallestArmyQty(allPlayers, playerNum)]->getCountry();

	cout << "Player" << playerNum << " select " << targetCountryName << " to be fortified:" << endl;
	cout << "The " << targetCountryName << " has following neighbor countries(they belong to the player): " << endl;

	displayNeighborCountries_inFortification(allPlayers, targetCountryName, playerNum);
	if (allPlayers[playerNum - 1]->getTemp_neighborCountries_inFortification().size() == 0)
		cout << "There are not any neighbor countries can be source country." << endl;
	else
	{
		for (int i = 0; i < allPlayers[playerNum - 1]->getTemp_neighborCountries_inFortification().size(); i++)
		{
			int indexOfsourceCountry = indexOfCountry(allPlayers, allPlayers[playerNum - 1]->getTemp_neighborCountries_inFortification()[i], playerNum);
			if (allPlayers[playerNum - 1]->getMapPtr()->getCountry()[indexOfsourceCountry]->getNumOfArmies() > 1)
			{
				int armyNumInSouceCountry = allPlayers[playerNum - 1]->getMapPtr()->getCountry()[indexOfsourceCountry]->getNumOfArmies();
				allPlayers[playerNum - 1]->getMapPtr()->getCountry()[index_targetCountry]->setNumberOfArmies(
					allPlayers[playerNum - 1]->getMapPtr()->getCountry()[index_targetCountry]->getNumOfArmies() + armyNumInSouceCountry - 1);
				allPlayers[playerNum - 1]->getMapPtr()->getCountry()[indexOfsourceCountry]->setNumberOfArmies(1);
				break;
			}
		}
		allPlayers[playerNum - 1]->clearTemp_neighborCountries_inFortification();
		//displayMyCountry(allPlayers, playerNum );

	}
}

//display all the neighbor countries of the attacker country.
//meanwhile, store these neighbor countries into a vector.
void Strategy_benevolentC::displayNeighborCountries_inFortification(vector <Player*> allPlayers, string theAttackerCountry, int playerNum)
{
	int index;
	int size = allPlayers[playerNum - 1]->getMapPtr()->getTotalNumOfCountry();
	for (int i = 0; i < size; i++)
	{
		if (allPlayers[playerNum - 1]->getMapPtr()->getCountry()[i]->getCountry() == theAttackerCountry)
			index = i;
	}
	for (int i = 0; i < size; i++)
	{
		if ((allPlayers[playerNum - 1]->getMapPtr()->getLoaderPtr()->getMapInfo_country()[i][0] == theAttackerCountry))
		{
			for (int j = allPlayers[playerNum - 1]->getMapPtr()->getLoaderPtr()->getMapInfo_country()[i].size() - 1; j > 3; j--)
			{
				int index_defender = indexOfCountry(allPlayers, allPlayers[playerNum - 1]->getMapPtr()->getLoaderPtr()->getMapInfo_country()[i][j], playerNum);
				if (allPlayers[playerNum - 1]->getMapPtr()->getCountry()[index]->getPlayerNum() == allPlayers[playerNum - 1]->getMapPtr()->getCountry()[index_defender]->getPlayerNum())
				{
					allPlayers[playerNum - 1]->fillTemp_neighborCountries_inFortification(allPlayers[playerNum - 1]->getMapPtr()->getLoaderPtr()->getMapInfo_country()[i][j]);
					cout << allPlayers[playerNum - 1]->getMapPtr()->getLoaderPtr()->getMapInfo_country()[i][j] << ", ";
				}
			}
		}
	}
	cout << endl;
}
int Strategy_benevolentC::indexOfCountry(vector <Player*> allPlayers, string countryName, int playerNum)
{
	int i;
	int size = allPlayers[playerNum - 1]->getMapPtr()->getTotalNumOfCountry();
	for (i = 0; i < size; i++)
	{
		if (allPlayers[playerNum - 1]->getMapPtr()->getCountry()[i]->getCountry() == countryName)
			return i;
	}
}
//return the index of the target country.
int Strategy_benevolentC::index_targetCountry(vector <Player*> allPlayers, string targetCountry, int playerNum)
{
	int size = allPlayers[playerNum - 1]->getMapPtr()->getCountry().size();
	int i;
	for (i = 0; i < size; i++)
	{
		if (allPlayers[playerNum - 1]->getMapPtr()->getCountry()[i]->getCountry() == targetCountry)
		{
			return i;
		}
	}
}
//return the index of the source country.
int Strategy_benevolentC::index_sourceCountry(vector <Player*> allPlayers, string sourceCountry, int playerNum)
{
	int size = allPlayers[playerNum - 1]->getMapPtr()->getCountry().size();
	int i;
	for (i = 0; i < size; i++)
	{
		if (allPlayers[playerNum - 1]->getMapPtr()->getCountry()[i]->getCountry() == sourceCountry)
		{
			return i;
		}
	}
}