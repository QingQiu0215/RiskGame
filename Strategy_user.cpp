#include <iostream>
#include <time.h>
#include <algorithm> 
#include "Strategy_user.h"
#include "Player.h"
using namespace std;

//************************************************************************************************************************
//*******************************The following are part 2-Phase observer**************************************************
//************************************************************************************************************************
class Subject1 {
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
	Subject1 *model;
	string phaseName;
public:
	Observer(Subject1 *sub, string str) {
		model = sub;
		phaseName = str;
		// 4. Observers register themselves with the Subject
		model->attach(this);
	}
	virtual void update() = 0;
protected:
	Subject1 *getSubject() {
		return model;
	}
	string getDivisor() {
		return phaseName;
	}
};

void Subject1::notify() {
	// 5. Publisher broadcasts
	for (int i = 0; i < views.size(); i++)
		views[i]->update();
}

class ReinforceObserver : public Observer {
public:
	ReinforceObserver(Subject1 *sub, string str) : Observer(sub, str) {}
	void update() {
		// 6. "Pull" information of interest
		if (getSubject()->getVal() == "Reinforcement")
			cout << "********************************This is the " << getSubject()->getVal() << " phase.************************************" << endl;
	}
};

class AttackObserver : public Observer {
public:
	AttackObserver(Subject1 *sub, string str) : Observer(sub, str) {}
	void update() {
		// 6. "Pull" information of interest
		if (getSubject()->getVal() == "Attack")
			cout << "*******************************This is the " << getSubject()->getVal() << " phase.***********************************" << endl;
	}
};
class FortifyObserver : public Observer {
public:
	FortifyObserver(Subject1 *sub, string str) : Observer(sub, str) {}
	void update() {
		// 6. "Pull" information of interest
		if (getSubject()->getVal() == "Fortify")
			cout << "*****************************This is the " << getSubject()->getVal() << " phase.***********************************" << endl;
	}
};


void Strategy_user::execute(vector <Player*> allPlayers, Deck* deckPtr, int armyQty_startup,int playerNum)
{
	Subject1 subj;
	new ReinforceObserver(&subj, "Reinforcement"); // 7. Client configures the number and
	new AttackObserver(&subj, "Attack"); //    type of Observers
	new FortifyObserver(&subj, "Fortify");
	cout << "**********************************************Player"<< playerNum <<"***************************************************" << endl;
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
//**********************************Part2 is end here********************************************************
//***********************************************************************************************************

//start reinforce phase
void Strategy_user::reinforce(vector <Player*> allPlayers, Deck* deckPtr, int armyQty_startup, int playerNum)
{
	makeArmyQty_numberOfCountry(allPlayers, playerNum);
	makeArmyQty_continentValue(allPlayers, playerNum);
	makeArmyQty_exchangeCard(allPlayers, playerNum);
	makeReinforcementArmyQty(allPlayers, playerNum);
	distributeArmy_reinforcement(allPlayers, armyQty_startup, playerNum);
}
//number of countries owned on the map, divided by 3(round down), with a minimum of 3
void Strategy_user::makeArmyQty_numberOfCountry(vector <Player*> allPlayers, int playerNum)
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
void Strategy_user::makeArmyQty_continentValue(vector <Player*> allPlayers, int playerNum)
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
//Armies resulting in card exchange, if possible. If a player owns more than 5 cards, it must exchange cards.
void Strategy_user::makeArmyQty_exchangeCard(vector <Player*> allPlayers, int playerNum)
{
	int size = allPlayers[playerNum - 1]->getPlayerHand().size();
	if (size >= 5)
	{
		cout << "Player" << playerNum << " must exchange three of cards for armies." << endl;
		for (int i = 0; i < 3; i++)
		{
			allPlayers[playerNum - 1]->exchange(size - 1);
			int quantity = (i + 1) * 5;
			allPlayers[playerNum - 1]->setArmyQty_exchangeCard(allPlayers[playerNum - 1]->getArmyQty_exchangeCard() + quantity);
		}
	}
	else if (size < 3)
	{
		cout << "Player" << playerNum << " cannot exchange cards." << endl;
		cout << "Because the player owns three cards of different sorts or the same sorts, he can exchange them for armies. " << endl;
	}
	else
	{
		int count = 0;
		for (int i = 0; i < size - 1; i++)
		{
			for (int j = 1; j < size; j++)
			{
				if (allPlayers[playerNum - 1]->getPlayerHand()[i].getType() == allPlayers[playerNum - 1]->getPlayerHand()[j].getType())
					count++;
			}
		}

		if (size - count < 3)
		{
			cout << "Player" << playerNum << " cannot exchange cards." << endl;
			cout << "Because the player owns three cards of different sorts or the same sorts, he can exchange them for armies. " << endl;
		}
		else
		{
			cout << "How many cards the player" << playerNum << " want to exchange? " << endl;
			int enteredNum;
			cin >> enteredNum;
			while (enteredNum > allPlayers[playerNum - 1]->getArmyQty_exchangeCard())
			{
				cout << "The number you entered is bigger than the quantity of cards. Please try again: " << endl;
				cin >> enteredNum;
			}
			for (int i = 0; i < enteredNum; i++)
			{
				allPlayers[playerNum - 1]->exchange(size - 1);
				int quantity = (i + 1) * 5;
				allPlayers[playerNum - 1]->setArmyQty_exchangeCard(allPlayers[playerNum - 1]->getArmyQty_exchangeCard() + quantity);
			}
		}

	}
}
//get total quantity of armies in the reinforcement phase.
void Strategy_user::makeReinforcementArmyQty(vector <Player*> allPlayers, int playerNum)
{
	int qty = allPlayers[playerNum - 1]->getArmyQty_numberOfCountry() +
		allPlayers[playerNum - 1]->getArmyQty_continentValue() +
		allPlayers[playerNum - 1]->getArmyQty_exchangeCard();
	allPlayers[playerNum - 1]->setReinforcementArmyQty(allPlayers[playerNum - 1]->getReinforcementArmyQty() + qty);
}

//distribute armies for a specific player.
void Strategy_user::distributeArmy_reinforcement(vector <Player*> allPlayers,int armyQty_startup, int playerNum)
{
	displayMyCountry(allPlayers, playerNum);
	while (allPlayers[playerNum - 1]->getReinforcementArmyQty() > 0)
	{
		for (int i = 0; i < (allPlayers[playerNum - 1]->getMapPtr()->getCountry()).size(); i++)
		{
			if ((allPlayers[playerNum - 1]->getMapPtr()->getCountry())[i]->getPlayerNum() == 1)
			{
				cout << "Now, player" << playerNum << " have " << allPlayers[playerNum - 1]->getReinforcementArmyQty() << " left to distribute." << endl;
				cout << "Please enter a number of armies for this country: " << (allPlayers[playerNum - 1]->getMapPtr()->getCountry())[i]->getCountry() << endl;
				cin >> armyQtytoDistribute;
				bool validNum = checkArmyQtytoDistribute_reinforcement(armyQtytoDistribute, allPlayers, playerNum);
				while (!validNum)
				{
					cout << "The number you entered is bigger than the quantity of amries you left.Please try again: " << endl;
					cin >> armyQtytoDistribute;
					if (armyQtytoDistribute <= armyQty_startup)
						validNum = true;
				}
				(allPlayers[playerNum - 1]->getMapPtr()->getCountry())[i]->setNumberOfArmies((allPlayers[playerNum - 1]->getMapPtr()->getCountry())[i]->getNumOfArmies() + armyQtytoDistribute);

				allPlayers[playerNum - 1]->setReinforcementArmyQty(allPlayers[playerNum - 1]->getReinforcementArmyQty() - armyQtytoDistribute);
				if (allPlayers[playerNum - 1]->getReinforcementArmyQty() == 0)
					break;
			}
		}
	}
	cout << "Now, you do not have any armies to distribute." << endl;
	cout << "You distributed armies for all your countries: " << endl;
	displayMyCountry(allPlayers, playerNum);
}
//check if the selected number of armies exceed the source number of the player
bool Strategy_user::checkArmyQtytoDistribute_reinforcement(int armyQtytoDistribute, vector <Player*> allPlayers, int playerNum)
{
	if (armyQtytoDistribute <= allPlayers[playerNum - 1]->getReinforcementArmyQty())
		return true;
	return false;
}
void Strategy_user::displayMyCountry(vector <Player*> allPlayers,int playerNum)
{
	cout << "Player " << playerNum << " has the following countries(country name,continent name,player number, quantity of armies):" << endl;
	for (int i = 0; i < (allPlayers[playerNum-1]->getMapPtr()->getCountry()).size(); i++)
	{
		if ((allPlayers[playerNum-1]->getMapPtr()->getCountry())[i]->getPlayerNum() == playerNum)
			cout << (allPlayers[playerNum-1]->getMapPtr()->getCountry())[i]->displayCountry();
	}
	cout << endl;
}
//***********************************************************************************************************
//**********************************The followings are Part5*************************************************
//***********************************************************************************************************

//start attack, the player can select as many as times it wants.
void Strategy_user::attack(vector <Player*> allPlayers, Deck* deckPtr, int playerNum)
{
	cout << "How many attacking times the player" << playerNum << " wants(please enter any integer including 0):" << endl;
	int attackTimes;
	cin >> attackTimes;
	for (int i = 0; i < attackTimes; i++)
	{
		int attackGoOn;
		cout << "If player" << playerNum << " want to attack, please enter 1. Otherwise, enter 0." << endl;
		cin >> attackGoOn;
		if (attackGoOn == 0)
			break;
		attackStart(allPlayers, playerNum);
	}
	if (numOfsuccessfulConquer > 0)
	{
		deckPtr->draw(allPlayers[playerNum - 1]->getHandPtr());
		allPlayers[playerNum - 1]->setPlayerHand();
	}
	numOfsuccessfulConquer = 0;
	cout << "Now, player" << playerNum << " has the following cards in hand:" << endl;
	allPlayers[playerNum - 1]->displayMyHand();
}
//start an attack(one time)
void Strategy_user::attackStart(vector <Player*> allPlayers, int playerNum)
{
	cout << "Player" << playerNum << " decided to attack." << endl;
	displayMyCountry(allPlayers, playerNum);
	cout << "Player" << playerNum << " can choose one of its countries to attack(enter a string):" << endl;
	string attackerCountry;
	cin >> attackerCountry;
	cout << "Player" << playerNum << " select " << attackerCountry << " to attack:" << endl;
	cout << "The " << attackerCountry << " has following neighbor countries(they belong to another players): " << endl;
	displayNeighborCountries(allPlayers, attackerCountry, playerNum);
	bool validCountryAttacker = checkValidCountry_attacker(allPlayers,attackerCountry, playerNum);
	while (!validCountryAttacker)
	{
		allPlayers[playerNum - 1]->clearTemp_neighborCountries();
		cin >> attackerCountry;
		cout << "Player" << playerNum << " select " << attackerCountry << " to attack:" << endl;
		cout << "The " << attackerCountry << " has following neighbor countries(they belong to another players): " << endl;
		displayNeighborCountries(allPlayers, attackerCountry, playerNum);
		validCountryAttacker = checkValidCountry_attacker(allPlayers,  attackerCountry, playerNum);
	}
	cout << "Player" << playerNum << " can choose one of these neighbor countries for attacking(enter a string):" << endl;
	string defenderCountry;
	cin >> defenderCountry;
	while (!checkValidCountry_defender(allPlayers, defenderCountry, playerNum))
	{
		cin >> defenderCountry;
	}
	defenderNum = playerNum_defenderCountry(allPlayers, defenderCountry, playerNum);
	allPlayers[playerNum - 1]->clearTemp_neighborCountries();

	cout << "Player" << playerNum << " chose the neighbor country " << defenderCountry << "  to be attacked:" << endl;

	cout << "The country " << defenderCountry << " belongs to player" << defenderNum << endl;
	cout << "Now, the two players are rolling dice." << endl;
	attackerRolling(allPlayers, attackerCountry, playerNum);
	defenderRolling(allPlayers, defenderCountry, defenderNum);
	compareDiceAndFight(allPlayers, attackerCountry, defenderCountry, playerNum, defenderNum);
}
//check if the country is belong to the attacker, and if the number of armies is bigger than 1
bool Strategy_user::checkValidCountry_attacker(vector <Player*> allPlayers,string countryName, int playerNum)
{
	int size = allPlayers[playerNum - 1]->getMapPtr()->getTotalNumOfCountry();
	for (int i = 0; i < size; i++)
	{
		if ((allPlayers[playerNum - 1]->getMapPtr()->getCountry()[i]->getCountry() == countryName)
			&& (allPlayers[playerNum - 1]->getMapPtr()->getCountry()[i]->getPlayerNum() != playerNum))
		{
			cout << "This country does not belong to player" << playerNum << endl;
			cout << "Please select another country: " << endl;
			return false;
		}
	}
	for (int i = 0; i < size; i++)
	{
		if ((allPlayers[playerNum - 1]->getMapPtr()->getCountry()[i]->getCountry() == countryName)
			&& (allPlayers[playerNum - 1]->getMapPtr()->getCountry()[i]->getNumOfArmies() < 2))
		{
			cout << "The attacking country must have at least 2 armies on it. " << endl;
			cout << "Please select another country: " << endl;
			return false;
		}
	}
	if (allPlayers[playerNum - 1]->getTemp_neighborCountries().size() == 0)
	{
		cout << "There is not any available country(belongs to another player) to attack. " << endl;
		cout << "Please select another country: " << endl;
		return false;
	}
	return true;
}
//display the attacker's neighbor countries(belong to other players)
void Strategy_user::displayNeighborCountries(vector <Player*> allPlayers, string theAttackerCountry, int playerNum)
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
int Strategy_user::indexOfCountry(vector <Player*> allPlayers, string countryName, int playerNum)
{
	int i;
	int size = allPlayers[playerNum - 1]->getMapPtr()->getTotalNumOfCountry();
	for (i = 0; i < size; i++)
	{
		if (allPlayers[playerNum - 1]->getMapPtr()->getCountry()[i]->getCountry() == countryName)
			return i;
	}
}
//check if the entered country name is in the attacker's neighbor countries or not
bool Strategy_user::checkValidCountry_defender(vector <Player*> allPlayers, string countryName, int playerNum)
{
	int size = allPlayers[playerNum - 1]->getTemp_neighborCountries().size();
	for (int i = 0; i < size; i++)
	{
		if (allPlayers[playerNum - 1]->getTemp_neighborCountries()[i] == countryName)
			return true;
	}
	cout << "The defender country you entered is not correct. Please enter again: " << endl;
	return false;
}
//get the player No. of the defender country
int Strategy_user::playerNum_defenderCountry(vector <Player*> allPlayers, string defenderCountry, int playerNum)
{
	int size = allPlayers[playerNum - 1]->getMapPtr()->getCountry().size();
	for (int i = 0; i < size; i++)
	{
		if (allPlayers[playerNum - 1]->getMapPtr()->getCountry()[i]->getCountry() == defenderCountry)
		{
			return allPlayers[playerNum - 1]->getMapPtr()->getCountry()[i]->getPlayerNum();
		}
	}
}
//attacker rolls and get a vector to store all the results from the rolling
void Strategy_user::attackerRolling(vector <Player*> allPlayers, string theAttackerCountry, int playerNum)
{
	int armyQty_inAttackerCountry;
	int size = allPlayers[playerNum - 1]->getMapPtr()->getCountry().size();
	for (int i = 0; i < size; i++)
	{
		if (allPlayers[playerNum - 1]->getMapPtr()->getCountry()[i]->getCountry() == theAttackerCountry)
			armyQty_inAttackerCountry = allPlayers[playerNum - 1]->getMapPtr()->getCountry()[i]->getNumOfArmies();
	}
	cout << "Please choose the number of dice to roll: " << endl;
	cout << "There are " << armyQty_inAttackerCountry << " armies in the attacking country." << endl;
	int times_roll;
	cin >> times_roll;
	bool wrongTimes = true;
	while (wrongTimes)
	{
		if (times_roll <= 0 || times_roll > 3)
		{
			cout << "Maximum 3 dices and minimum 1 dice, please try again: " << endl;
			cin >> times_roll;
			continue;
		}
		else if ((armyQty_inAttackerCountry <= 3) && (times_roll >= armyQty_inAttackerCountry))
		{
			cout << "The maximum number of dice being the number of armies on the attacking country, minus one. Please try again. " << endl;
			cin >> times_roll;
			continue;
		}
		wrongTimes = false;
	}
	allPlayers[playerNum - 1]->getMyDicePtr()->rolling(times_roll);
	allPlayers[playerNum - 1]->setDiceArray();
	cout << "Player" << allPlayers[playerNum - 1]->getPlayerName() << " has the follwing dice:" << endl;
	for (int i = 0; i < allPlayers[playerNum - 1]->getDiceArray().size(); i++)
	{
		cout << allPlayers[playerNum - 1]->getDiceArray()[i] << ",";
	}
	cout << endl;
	allPlayers[playerNum - 1]->getMyDicePtr()->clearRollArray();
}
//defender rolls and get a vector to store all the results from the rolling
void Strategy_user::defenderRolling(vector <Player*> allPlayers, string theDefenderCountry, int playerNum)
{
	int armyQty_inDefenderCountry;
	int size = allPlayers[playerNum - 1]->getMapPtr()->getCountry().size();
	for (int i = 0; i < size; i++)
	{
		if (allPlayers[playerNum - 1]->getMapPtr()->getCountry()[i]->getCountry() == theDefenderCountry)
			armyQty_inDefenderCountry = allPlayers[playerNum - 1]->getMapPtr()->getCountry()[i]->getNumOfArmies();
	}
	cout << "Please choose the number of dice to roll: " << endl;
	cout << "There are " << armyQty_inDefenderCountry << " armies in the attacked country." << endl;
	int times_roll;
	cin >> times_roll;
	bool wrongTimes = true;
	while (wrongTimes)
	{
		if (times_roll <= 0 || times_roll > 2)
		{
			cout << "Maximum 2 dices and minimum 1 dice, please try again: " << endl;
			cin >> times_roll;
			continue;
		}
		else if (armyQty_inDefenderCountry == 1 && times_roll != 1)
		{
			cout << "There are only 1 army on the defender country. Only 1 can be selected. Please try again." << endl;
			cin >> times_roll;
			continue;
		}
		else if (armyQty_inDefenderCountry == 1 && times_roll == 1)
		{
			break;
		}
		else if ((armyQty_inDefenderCountry <= 2) && (times_roll >= armyQty_inDefenderCountry))
		{
			cout << "The maximum number of dice being the number of armies on the attacked country, minus one. Please try again. " << endl;
			cin >> times_roll;
			continue;
		}
		wrongTimes = false;
	}
	srand((unsigned)time(NULL));
	int diceNum;
	vector<int>rollArrayForComputer_temp;
	for (int i = 0; i < times_roll; i++)
	{
		diceNum = rand() % 6 + 1;
		rollArrayForComputer_temp.push_back(diceNum);
	}
	sort(rollArrayForComputer_temp.begin(), rollArrayForComputer_temp.end());
	for (int i = rollArrayForComputer_temp.size() - 1; i >= 0; i--)
	{
		rollArrayForComputer.push_back(rollArrayForComputer_temp[i]);
	}

	cout << "Player" << defenderNum << " has the follwing dice:" << endl;
	for (int i = 0; i < rollArrayForComputer.size(); i++)
	{
		cout << rollArrayForComputer[i] << ",";
	}
	cout << endl;
}
//compare the dice and deduct armies for both attacker and defender as per the result of comparing
void Strategy_user::compareDiceAndFight(vector <Player*> allPlayers, string theAttackerCountry, string theDefenderCountry, int playerNum,int defenderNum)
{
	int size_defender = rollArrayForComputer.size();
	int index_attackerCountry, index_defenderCountry;
	int size_attacker = allPlayers[playerNum - 1]->getMapPtr()->getTotalNumOfCountry();
	for (int i = 0; i < size_attacker; i++)
	{
		if (allPlayers[playerNum - 1]->getMapPtr()->getCountry()[i]->getCountry() == theAttackerCountry)
			index_attackerCountry = i;
	}
	for (int i = 0; i < size_attacker; i++)
	{
		if (allPlayers[playerNum - 1]->getMapPtr()->getCountry()[i]->getCountry() == theDefenderCountry)
			index_defenderCountry = i;
	}
	for (int i = 0; i < size_defender; i++)
	{
		if (allPlayers[playerNum - 1]->getDiceArray()[i] > rollArrayForComputer[i])
		{
			if (allPlayers[defenderNum - 1]->getMapPtr()->getCountry()[index_defenderCountry]->getNumOfArmies() > 0)
			{
				allPlayers[defenderNum - 1]->getMapPtr()->getCountry()[index_defenderCountry]->setNumberOfArmies(
					allPlayers[defenderNum - 1]->getMapPtr()->getCountry()[index_defenderCountry]->getNumOfArmies() - 1);
			}
			if (allPlayers[defenderNum - 1]->getMapPtr()->getCountry()[index_defenderCountry]->getNumOfArmies() == 0)
			{
				cout << "The defender country has 0 army now. It is conquered by the attacker." << endl;
				allPlayers[defenderNum - 1]->getMapPtr()->getCountry()[index_defenderCountry]->setPlayerNum(1);
				int armies = allPlayers[playerNum - 1]->getMapPtr()->getCountry()[index_attackerCountry]->getNumOfArmies();
				cout << "The " << theAttackerCountry << " has " << armies << " armies.";
				cout << "The attacker can move 1 to " << armies - 1 << " armies to the conquered country " << theDefenderCountry << endl;
				cout << "Please select the number of armies:" << endl;
				int armyQtytoMove;
				cin >> armyQtytoMove;
				while (armyQtytoMove > armies - 1 || armyQtytoMove < 0)
				{
					cout << armyQtytoMove << " is not a valid number." << "Be only allowed to move 1 to" << armies - 1 << "armies" << endl;
				}
				allPlayers[playerNum - 1]->getMapPtr()->getCountry()[index_attackerCountry]->setNumberOfArmies(
					allPlayers[playerNum - 1]->getMapPtr()->getCountry()[index_attackerCountry]->getNumOfArmies() - armyQtytoMove);
				allPlayers[defenderNum - 1]->getMapPtr()->getCountry()[index_defenderCountry]->setNumberOfArmies(
					allPlayers[defenderNum - 1]->getMapPtr()->getCountry()[index_defenderCountry]->getNumOfArmies() + armyQtytoMove);
				numOfsuccessfulConquer++;
				break;
			}
		}
		else
		{
			allPlayers[playerNum - 1]->getMapPtr()->getCountry()[index_attackerCountry]->setNumberOfArmies(
				allPlayers[playerNum - 1]->getMapPtr()->getCountry()[index_attackerCountry]->getNumOfArmies() - 1);
			if (allPlayers[playerNum - 1]->getMapPtr()->getCountry()[index_attackerCountry]->getNumOfArmies() == 0)
			{
				cout << "The attacker country has 0 army now. It is conquered by the defender." << endl;
				allPlayers[playerNum - 1]->getMapPtr()->getCountry()[index_defenderCountry]->setPlayerNum(defenderNum);
				break;
			}
		}
	}
	cout << "The result is like following after this turn of fighting: " << endl;
	displayMyCountry(allPlayers, playerNum);
	displayMyCountry(allPlayers,defenderNum);
	allPlayers[playerNum - 1]->clearDiceArray();
	rollArrayForComputer.clear();
	checkGameOver(allPlayers, playerNum);
}

bool Strategy_user::checkGameOver(vector <Player*> allPlayers, int playerNum)
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
void Strategy_user::fortify(vector <Player*> allPlayers, int playerNum)
{
	cout << "Whether the player" << playerNum << " wants to fortify its countries or not." << endl;
	cout << "If yes, enter 1, otherwise 0:" << endl;
	int fortifyOrNot;
	cin >> fortifyOrNot;
	if (fortifyOrNot == 0)
		return;
	cout << "Player" << playerNum << " decided to fortify its countries." << endl;
	displayMyCountry(allPlayers, playerNum);
	cout << "Player" << playerNum << " can choose one of its countries as the source country(enter a string):" << endl;
	string sourceCountry;
	cin >> sourceCountry;
	cout << "Player" << playerNum << " select " << sourceCountry << " to fortify:" << endl;
	cout << "The " << sourceCountry << " has following neighbor countries(they belong to the player): " << endl;
	displayNeighborCountries_inFortification(allPlayers, sourceCountry, playerNum);
	bool validSourceCountry = checkValidCountry_sourceContry(allPlayers, sourceCountry, playerNum);
	while (!validSourceCountry)
	{
		//need to clear this vector so that the vector can store new neighbor countries for new source country
		allPlayers[playerNum - 1]->clearTemp_neighborCountries_inFortification();
		cin >> sourceCountry;
		cout << "Player" << playerNum << " select " << sourceCountry << " to fortify:" << endl;
		cout << "The " << sourceCountry << " has following neighbor countries(they belong to the player): " << endl;
		displayNeighborCountries_inFortification(allPlayers, sourceCountry, playerNum);
		validSourceCountry = checkValidCountry_sourceContry(allPlayers, sourceCountry, playerNum);
	}
	cout << "Player" << playerNum << " can choose one of these neighbor countries for target(enter a string):" << endl;
	string targetCountry;
	cin >> targetCountry;
	while (!checkValidCountry_targetCountry(allPlayers, targetCountry, playerNum))
	{
		cin >> targetCountry;
	}
	cout << "Player" << playerNum << " choose " << targetCountry << " for target country." << endl;
	int indexOftargetCountry = index_targetCountry(allPlayers, targetCountry, playerNum);
	int indexOfsourceCountry = index_sourceCountry(allPlayers, sourceCountry, playerNum);
	allPlayers[playerNum - 1]->clearTemp_neighborCountries_inFortification();
	int armyNumInSouceCountry = allPlayers[playerNum - 1]->getMapPtr()->getCountry()[indexOfsourceCountry]->getNumOfArmies();
	cout << "There are " << armyNumInSouceCountry << " armies in the source country. Please select 1-" << armyNumInSouceCountry - 1
		<< " armies to move:" << endl;
	int numArmyForFortification;
	cin >> numArmyForFortification;
	while (numArmyForFortification > armyNumInSouceCountry - 1 || numArmyForFortification < 0)
	{
		cout << "You entered wrong number of armies for fortification." << endl;
		cout << "You are only allowed to select 1-" << armyNumInSouceCountry - 1 << " armies to move:" << endl;
		cout << "Please try again: " << endl;
		cin >> numArmyForFortification;
	}
	cout << "Player" << playerNum << " decide to move " << numArmyForFortification << " armies to " << targetCountry << endl;
	allPlayers[playerNum - 1]->getMapPtr()->getCountry()[indexOftargetCountry]->setNumberOfArmies(
		allPlayers[playerNum - 1]->getMapPtr()->getCountry()[indexOftargetCountry]->getNumOfArmies() + numArmyForFortification);
	allPlayers[playerNum - 1]->getMapPtr()->getCountry()[indexOfsourceCountry]->setNumberOfArmies(
		allPlayers[playerNum - 1]->getMapPtr()->getCountry()[indexOfsourceCountry]->getNumOfArmies() - numArmyForFortification);
	displayMyCountry(allPlayers, playerNum);
}
//check if the source country is valid or not.
bool Strategy_user::checkValidCountry_sourceContry(vector <Player*> allPlayers, string countryName, int playerNum)
{
	if (allPlayers[playerNum - 1]->getTemp_neighborCountries_inFortification().size() == 0)
	{
		cout << "There is not any available country to fortify. " << endl;
		cout << "It does not have any adjacent countries(belong to this player). Please try again: " << endl;
		return false;
	}
	int size = allPlayers[playerNum - 1]->getMapPtr()->getTotalNumOfCountry();
	for (int i = 0; i < size; i++)
	{
		if (allPlayers[playerNum - 1]->getMapPtr()->getCountry()[i]->getCountry() == countryName
			&& allPlayers[playerNum - 1]->getMapPtr()->getCountry()[i]->getNumOfArmies() > 1)
		{
			cout << "This is a valid country. It has " <<
				allPlayers[playerNum - 1]->getMapPtr()->getCountry()[i]->getNumOfArmies() << " armies in it." << endl;
			return true;
		}
	}
	cout << "This is an invalid country because its armies less than 2 or this country name you entered is not existed." << endl;
	return false;
}
//check if the target country is valid or not.
bool Strategy_user::checkValidCountry_targetCountry(vector <Player*> allPlayers, string countryName, int playerNum)
{
	int size = allPlayers[playerNum - 1]->getTemp_neighborCountries_inFortification().size();
	for (int i = 0; i < size; i++)
	{
		if (allPlayers[playerNum - 1]->getTemp_neighborCountries_inFortification()[i] == countryName)
			return true;
	}
	cout << "The target country you entered is not correct. Please enter again: " << endl;
	return false;
}
//display all the neighbor countries of the attacker country.
//meanwhile, store these neighbor countries into a vector.
void Strategy_user::displayNeighborCountries_inFortification(vector <Player*> allPlayers, string theAttackerCountry, int playerNum)
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
//return the index of the target country.
int Strategy_user::index_targetCountry(vector <Player*> allPlayers, string targetCountry, int playerNum)
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
int Strategy_user::index_sourceCountry(vector <Player*> allPlayers, string sourceCountry, int playerNum)
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