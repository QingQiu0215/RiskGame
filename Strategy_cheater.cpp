#include <iostream>
#include <time.h>
#include <cstdlib>
#include <algorithm> 
#include "Strategy_cheater.h"
#include "Player.h"
using namespace std;

//************************************************************************************************************************
//*******************************The following are part 2-Phase observer**************************************************
//************************************************************************************************************************
class Subject5 {
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
	Subject5 *model;
	string phaseName;
public:
	Observer(Subject5 *sub, string str) {
		model = sub;
		phaseName = str;
		// 4. Observers register themselves with the Subject
		model->attach(this);
	}
	virtual void update() = 0;
protected:
	Subject5 *getSubject() {
		return model;
	}
	string getDivisor() {
		return phaseName;
	}
};

void Subject5::notify() {
	// 5. Publisher broadcasts
	for (int i = 0; i < views.size(); i++)
		views[i]->update();
}

class ReinforceObserver : public Observer {
public:
	ReinforceObserver(Subject5 *sub, string str) : Observer(sub, str) {}
	void update() {
		// 6. "Pull" information of interest
		if (getSubject()->getVal() == "Reinforcement")
			cout << "********************************This is the " << getSubject()->getVal() << " phase.************************************" << endl;
	}
};

class AttackObserver : public Observer {
public:
	AttackObserver(Subject5 *sub, string str) : Observer(sub, str) {}
	void update() {
		// 6. "Pull" information of interest
		if (getSubject()->getVal() == "Attack")
			cout << "*******************************This is the " << getSubject()->getVal() << " phase.***********************************" << endl;
	}
};
class FortifyObserver : public Observer {
public:
	FortifyObserver(Subject5 *sub, string str) : Observer(sub, str) {}
	void update() {
		// 6. "Pull" information of interest
		if (getSubject()->getVal() == "Fortify")
			cout << "*****************************This is the " << getSubject()->getVal() << " phase.***********************************" << endl;
	}
};


void Strategy_cheater::execute(vector <Player*> allPlayers, Deck* deckPtr, int armyQty_startup, int playerNum)
{
	Subject5 subj;
	new ReinforceObserver(&subj, "Reinforcement"); // 7. Client configures the number and
	new AttackObserver(&subj, "Attack"); //    type of Observers
	new FortifyObserver(&subj, "Fortify");
	cout << "**********************************************Player" << playerNum << "*****************************************************" << endl;
	subj.setVal("Reinforcement");
	reinforce(allPlayers, deckPtr, armyQty_startup, playerNum);

	cout << "**********************************************Player" << playerNum << "***************************************************" << endl;
	subj.setVal("Attack");
	attack(allPlayers, deckPtr, playerNum);

	cout << "**********************************************Player" << playerNum << "***************************************************" << endl;
	subj.setVal("Fortify");
	fortify(allPlayers, playerNum);
}
//***********************************************************************************************************
//**********************************Part2 end here***********************************************************
//***********************************************************************************************************


//start reinforce phase
void Strategy_cheater::reinforce(vector <Player*> allPlayers, Deck* deckPtr, int armyQty_startup, int playerNum)
{
	makeArmyQty_numberOfCountry(allPlayers, playerNum);
	makeArmyQty_continentValue(allPlayers, playerNum);
	makeArmyQty_exchangeCard(allPlayers, playerNum);
	makeReinforcementArmyQty(allPlayers, playerNum);
	distributeArmy_reinforcement(allPlayers, armyQty_startup, playerNum);
}
//number of countries owned on the map, divided by 3(round down), with a minimum of 3
void Strategy_cheater::makeArmyQty_numberOfCountry(vector <Player*> allPlayers, int playerNum)
{
	int countryNum = 0;
	for (int i = 0; i < (allPlayers[playerNum - 1]->getMapPtr()->getCountry()).size(); i++)
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
void Strategy_cheater::makeArmyQty_continentValue(vector <Player*> allPlayers, int playerNum)
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
			bool bool2 = allPlayers[playerNum - 1]->getMapPtr()->getCountry()[j]->getPlayerNum() == playerNum;
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
//Armies result in card exchange, if possible. If a player owns more than 5 cards, it must exchange cards.
void Strategy_cheater::makeArmyQty_exchangeCard(vector <Player*> allPlayers, int playerNum)
{
	int size = allPlayers[playerNum - 1]->getPlayerHand().size();
	if (size >= 5)
	{
		cout << "Player" << playerNum << " exchanges all its cards for armies." << endl;
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
		cout << "Player" << 2 << " cannot exchange cards." << endl;
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
			cout << "Player" << playerNum << " cannot exchange cards." << endl;
			cout << "Because the player owns three cards of different sorts or the same sorts, he can exchange them for armies. " << endl;
		}
		else
		{
			cout << "Player" << playerNum << " exchanges all its cards for armies." << endl;
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
void Strategy_cheater::makeReinforcementArmyQty(vector <Player*> allPlayers, int playerNum)
{
	int qty = allPlayers[playerNum - 1]->getArmyQty_numberOfCountry() +
		allPlayers[playerNum - 1]->getArmyQty_continentValue() +
		allPlayers[playerNum - 1]->getArmyQty_exchangeCard();
	allPlayers[playerNum - 1]->setReinforcementArmyQty(allPlayers[playerNum - 1]->getReinforcementArmyQty() + qty);
}

//distribute armies for a specific player.
void Strategy_cheater::distributeArmy_reinforcement(vector <Player*> allPlayers, int armyQty_startup, int playerNum)
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
	while (allPlayers[playerNum - 1]->getReinforcementArmyQty() > 0)
	{
		for (int i = 0; i < (allPlayers[playerNum - 1]->getMapPtr()->getCountry()).size(); i++)
		{
			if ((allPlayers[playerNum - 1]->getMapPtr()->getCountry())[i]->getPlayerNum() == playerNum)
			{
				(allPlayers[playerNum - 1]->getMapPtr()->getCountry())[i]->setNumberOfArmies((allPlayers[playerNum - 1]->getMapPtr()->getCountry())[i]->getNumOfArmies() + 1);
				allPlayers[playerNum - 1]->setReinforcementArmyQty(allPlayers[playerNum - 1]->getReinforcementArmyQty() - 1);
				if (allPlayers[playerNum - 1]->getReinforcementArmyQty() == 0)
					break;
			}
		}
	}


	int index_largestArmyQty = findCountryIndex_largestArmyQty(allPlayers, playerNum);
	(allPlayers[playerNum - 1]->getMapPtr()->getCountry())[index_largestArmyQty]->setNumberOfArmies((allPlayers[playerNum - 1]->
		getMapPtr()->getCountry())[index_largestArmyQty]->getNumOfArmies() + armyQtytoDistribute);

	allPlayers[playerNum - 1]->setReinforcementArmyQty(0);
	cout << "Player" << playerNum << " distributed armies for the specific country: " << endl;
	int size = (allPlayers[playerNum - 1]->getMapPtr()->getCountry()).size();
	//double the number of armies on all its countries.
	for (int i = 0; i < size; i++)
	{
		if (allPlayers[playerNum - 1]->getMapPtr()->getCountry()[i]->getPlayerNum() == playerNum)
		{
			(allPlayers[playerNum - 1]->getMapPtr()->getCountry())[i]->setNumberOfArmies(
				(allPlayers[playerNum - 1]->getMapPtr()->getCountry())[i]->getNumOfArmies() *2);		
		}
	}


	//displayMyCountry(allPlayers, playerNum);
}
int Strategy_cheater::findCountryIndex_largestArmyQty(vector <Player*> allPlayers, int playerNum)
{
	int size = allPlayers[playerNum - 1]->getMapPtr()->getTotalNumOfCountry();
	int maxQtyOfArmy = 0;
	for (int i = 0; i < size; i++)
	{
		if ((allPlayers[playerNum - 1]->getMapPtr()->getCountry())[i]->getNumOfArmies() > maxQtyOfArmy && (allPlayers[playerNum - 1]->getMapPtr()->getCountry())[i]->getPlayerNum() == playerNum)
			maxQtyOfArmy = (allPlayers[playerNum - 1]->getMapPtr()->getCountry())[i]->getNumOfArmies();
	}
	for (int i = 0; i < size; i++)
	{
		if ((allPlayers[playerNum - 1]->getMapPtr()->getCountry())[i]->getPlayerNum() == playerNum && (allPlayers[playerNum - 1]->getMapPtr()->getCountry())[i]->getNumOfArmies() == maxQtyOfArmy)
			return i;
	}
}

string Strategy_cheater::findCountryName_largestArmyQty(vector <Player*> allPlayers, int playerNum)
{
	int index = findCountryIndex_largestArmyQty(allPlayers, playerNum);
	return (allPlayers[playerNum - 1]->getMapPtr()->getCountry())[index]->getCountry();
}


void Strategy_cheater::displayMyCountry(vector <Player*> allPlayers, int playerNum)
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
void Strategy_cheater::attack(vector <Player*> allPlayers, Deck* deckPtr, int playerNum)
{
	cout << "Player" << playerNum << " always attack until it cannot attack anymore" << endl;

	string attackerCountry = findCountryName_largestArmyQty(allPlayers, playerNum);
	//cout << "Player" << playerNum << " select the strongest country " << attackerCountry << " to attack:" << endl;
	//cout << "The " << attackerCountry << " has following neighbor countries(they belong to another players): " << endl;
	displayNeighborCountries(allPlayers, attackerCountry, playerNum);
	if (allPlayers[playerNum - 1]->getTemp_neighborCountries().size() == 0)
	{
		cout << "There is not any neighbor country to attack.The attack phase stop." << endl;
		return;
	}
	else
	{
		for (int i = 0; i < allPlayers[playerNum - 1]->getTemp_neighborCountries().size(); i++)
		{
			int index_defenderCountry = indexOfCountry(allPlayers, allPlayers[playerNum - 1]->getTemp_neighborCountries()[i], playerNum);
			int index_attackerCountry = findCountryIndex_largestArmyQty(allPlayers, playerNum);
			defenderNum = playerNum_defenderCountry(allPlayers, allPlayers[playerNum - 1]->getTemp_neighborCountries()[i], playerNum);
			cout << "The defender country has 0 army now. It is conquered by the attacker." << endl;
			allPlayers[defenderNum - 1]->getMapPtr()->getCountry()[index_defenderCountry]->setPlayerNum(playerNum);
			checkGameOver(allPlayers, playerNum);
		}
	}
	allPlayers[playerNum - 1]->clearTemp_neighborCountries();
	if (numOfsuccessfulConquer > 0)
	{
		deckPtr->draw(allPlayers[playerNum - 1]->getHandPtr());
		allPlayers[playerNum - 1]->setPlayerHand();
	}
	numOfsuccessfulConquer = 0;
	cout << "Now, player" << playerNum << " has the following cards in hand:" << endl;
	allPlayers[playerNum - 1]->displayMyHand();
}

//display the attacker's neighbor countries(belong to other players)
void Strategy_cheater::displayNeighborCountries(vector <Player*> allPlayers, string theAttackerCountry, int playerNum)
{
	int index = findCountryIndex_largestArmyQty(allPlayers, playerNum);
	int size = allPlayers[playerNum - 1]->getMapPtr()->getTotalNumOfCountry();

	for (int i = 0; i < size; i++)
	{
		if ((allPlayers[playerNum - 1]->getMapPtr()->getLoaderPtr()->getMapInfo_country()[i][0] == theAttackerCountry))
		{
			for (int j = allPlayers[playerNum - 1]->getMapPtr()->getLoaderPtr()->getMapInfo_country()[i].size() - 1; j > 3; j--)
			{
				int index_defender = indexOfCountry(allPlayers, allPlayers[playerNum - 1]->getMapPtr()->getLoaderPtr()->getMapInfo_country()[i][j], playerNum);
				if (allPlayers[playerNum - 1]->getMapPtr()->getCountry()[index]->getPlayerNum() != allPlayers[playerNum - 1]->getMapPtr()->getCountry()[index_defender]->getPlayerNum())
				{
					allPlayers[playerNum - 1]->fillTemp_neighborCountries(allPlayers[playerNum - 1]->getMapPtr()->getLoaderPtr()->getMapInfo_country()[i][j]);
					cout << allPlayers[playerNum - 1]->getMapPtr()->getLoaderPtr()->getMapInfo_country()[i][j] << ", ";
				}
			}
		}
	}
	cout << endl;
}
//help method for the method displayNeighborCountries()
int Strategy_cheater::indexOfCountry(vector <Player*> allPlayers, string countryName, int playerNum)
{
	int i;
	int size = allPlayers[playerNum - 1]->getMapPtr()->getTotalNumOfCountry();
	for (i = 0; i < size; i++)
	{
		if (allPlayers[playerNum - 1]->getMapPtr()->getCountry()[i]->getCountry() == countryName)
			return i;
	}
}

//get the player No. of the defender country
int Strategy_cheater::playerNum_defenderCountry(vector <Player*> allPlayers, string defenderCountry, int playerNum)
{
	int size = allPlayers[playerNum - 1]->getMapPtr()->getCountry().size();
	for (int i = 0; i < size; i++)
	{
		if (allPlayers[playerNum - 1]->getMapPtr()->getCountry()[i]->getCountry() == defenderCountry)
		{
			return allPlayers[0]->getMapPtr()->getCountry()[i]->getPlayerNum();
		}
	}
}

bool Strategy_cheater::checkGameOver(vector <Player*> allPlayers, int playerNum)
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

//start fortify armies.The player can decide go on or not.
//comment following codes because it will take a lot of time to run.
//actually, these following codes are important information for view.
void Strategy_cheater::fortify(vector <Player*> allPlayers, int playerNum)
{
	int size_totalCountry=0;
	int size = allPlayers[playerNum - 1]->getMapPtr()->getCountry().size();
	string sourceCountry;
	for (int i = 0; i < size; i++)
	{
		if (allPlayers[playerNum - 1]->getMapPtr()->getCountry()[i]->getPlayerNum() == playerNum)
		{
			sourceCountry = allPlayers[playerNum - 1]->getMapPtr()->getCountry()[i]->getCountry();
			cout << "Player" << playerNum << " select " << sourceCountry << " to fortify:" << endl;
			cout << "The " << sourceCountry << " has following neighbor countries(they belong to the player): " << endl;
			displayNeighborCountries_inFortification(allPlayers, sourceCountry, playerNum);
			if (allPlayers[playerNum - 1]->getTemp_neighborCountries_inFortification().size() != 0)
			{
				allPlayers[playerNum - 1]->getMapPtr()->getCountry()[i]->setNumberOfArmies(
					allPlayers[playerNum - 1]->getMapPtr()->getCountry()[i]->getNumOfArmies() * 2);
			}
		    else 
				cout << "There are not any neighbor countries can be fortified." << endl;
			allPlayers[playerNum - 1]->clearTemp_neighborCountries_inFortification();
			//displayMyCountry(allPlayers, playerNum);
		}
	}

}
//display all the neighbor countries of the attacker country.
//meanwhile, store these neighbor countries into a vector.
void Strategy_cheater::displayNeighborCountries_inFortification(vector <Player*> allPlayers, string theAttackerCountry, int playerNum)
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
				if (allPlayers[playerNum - 1]->getMapPtr()->getCountry()[index]->getPlayerNum() != allPlayers[playerNum - 1]->
					getMapPtr()->getCountry()[index_defender]->getPlayerNum())//neighbors that belong to other players
				{
					allPlayers[playerNum - 1]->fillTemp_neighborCountries_inFortification(allPlayers[playerNum - 1]->getMapPtr()->getLoaderPtr()->getMapInfo_country()[i][j]);
					cout << allPlayers[1]->getMapPtr()->getLoaderPtr()->getMapInfo_country()[i][j] << ", ";
				}
			}
		}
	}
	cout << endl;
}
