//-----------------------------------
//Written by:Qing Qiu, 40022237
//For COMP 345 Fall 2018
//-----------------------------------
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>
#include <conio.h>
#include "Start.h"
#include "Map.h"
#include "StrategyBox.h"
using namespace std;

//************************************************************************************************************************
//*******************************The following are part 3-Statistic observer**************************************************
//************************************************************************************************************************
class Subject {
	// 1. "independent" functionality
	vector < class Observer * > views; // 3. Coupled only to "interface"
	int value;
public:
	void attach(Observer *obs) {
		views.push_back(obs);
	}
	void setVal(int val) {
		value = val;
		notify();
	}
	int getVal() {
		return value;
	}
	void notify();
};

class Observer {
	// 2. "dependent" functionality
	Subject *model;
	int denom;
public:
	Observer(Subject *mod, int div) {
		model = mod;
		denom = div;
		// 4. Observers register themselves with the Subject
		model->attach(this);
	}
	virtual void update() = 0;
protected:
	Subject *getSubject() {
		return model;
	}
	int getDivisor() {
		return denom;
	}
};

void Subject::notify() {
	// 5. Publisher broadcasts
	for (int i = 0; i < views.size(); i++)
		views[i]->update();
}

class Player1_Observer : public Observer {
public:
	Player1_Observer(Subject *mod, int div) : Observer(mod, div) {}
	void update() {
		// 6. "Pull" information of interest
		int v = getSubject()->getVal(), d = getDivisor();
		cout << "==================Player1 has " << (static_cast<double>(d) / v) << " percent of countries. =========================" << endl;
	}
};

class Player2_Observer : public Observer {
public:
	Player2_Observer(Subject *mod, int div) : Observer(mod, div) {}
	void update() {
		int v = getSubject()->getVal(), d = getDivisor();
		cout << "==================Player2 has " << (static_cast<double>(d) / v) << " percent of countries. =========================" << endl;
	}
};
class Player3_Observer : public Observer {
public:
	Player3_Observer(Subject *mod, int div) : Observer(mod, div) {}
	void update() {
		int v = getSubject()->getVal(), d = getDivisor();
		cout << "==================Player3 has " << (static_cast<double>(d) / v) << " percent of countries. =========================" << endl;
	}
};
class Player4_Observer : public Observer {
public:
	Player4_Observer(Subject *mod, int div) : Observer(mod, div) {}
	void update() {
		int v = getSubject()->getVal(), d = getDivisor();
		cout << "==================Player4 has " << (static_cast<double>(d) / v) << " percent of countries. =========================" << endl;
	}
};



Start::Start()
{
	//store some map names in a vector as a directory.
	vector<string> temp0; temp0.push_back("0"); temp0.push_back("001_I72_Ghtroc 720.map"); allMap.push_back(temp0);
	vector<string> temp1; temp1.push_back("1"); temp1.push_back("Aden.map"); allMap.push_back(temp1);
	vector<string> temp2; temp2.push_back("2"); temp2.push_back("ABC_Map.map"); allMap.push_back(temp2);
	vector<string> temp3; temp3.push_back("3"); temp3.push_back("004_I72_Cobra.map"); allMap.push_back(temp3);
	vector<string> temp4; temp4.push_back("4"); temp4.push_back("005_I72_V-22.map"); allMap.push_back(temp4);
	cout << "There are two game modes:" << endl;
	cout << "1. Single Game Mode." << endl;
	cout << "2. Tourname Mode." << endl;
	cout << "Please choose one of them to play(enter 1 or 2):" << endl;
	int mode;
	cin >> mode;
	while (mode != 1 && mode!=2)
	{
		cout << "You entered invalid integer. Please enter 1 or 2:" << endl;
		cin >> mode;
	}
	if (mode == 1)
	{
		cout << "-----------------------------------------------------------------------" << endl;
		cout << "Please enjoy the single game mode." << endl;
		cout << "-----------------------------------------------------------------------" << endl;
		singleGame();
	}
	else
	{
		cout << "-----------------------------------------------------------------------" << endl;
		cout << "Please enjoy the tournamet mode." << endl;
		cout << "-----------------------------------------------------------------------" << endl;
		tournament();
	}

}
void Start::singleGame()
{
	setPlayerQty();
	setArmyQty_startup();
	displayAllMap();
	selectMaptoPlay();
	mapPtr = new Map(selectedMap);
	deckPtr = new Deck(mapPtr->getCountry().size());
	setPlayers();
	distributeCountriesToPlayers();
	cout << "=============Display deck(card) and hand(card) in startup phase================" << endl;
	displayDeck();
	displayHand_AllPlayers();
	cout << "=================Display player's countries in startup phase===================" << endl;
	displayAllCountryForEachPlayer();
	cout << "===================Distribute armies for startup phase=========================" << endl;
	distributeArmy_startup_forEachPlayer();
	selectStrategy();
	randomOrderOfPlay();
	bool gameGoOn = true;
	while (gameGoOn)
	{
		for (int i = 0; i < box.size(); i++)
		{
			find_numberOfCountry(allPlayers);
			Subject subj;
			Player1_Observer player1(&subj, countryNum_player1); // 7. Client configures the number and
			Player2_Observer player2(&subj, countryNum_player2); //    type of Observers
			Player3_Observer player3(&subj, countryNum_player3);
			Player4_Observer player4(&subj, countryNum_player4); // 7. Client configures the number and
			
			subj.setVal(totalQtyofCountry);
			box[loopSequence[i] - 1].execute(allPlayers, deckPtr, armyQty_startup, loopSequence[i]);
			countryNum_player1 = 0; countryNum_player2 = 0; countryNum_player3 = 0;
			countryNum_player4 = 0; 
			if (checkGameOver(1) == true)
			{
				gameGoOn = false;
				break;
			}
		}
	}
	cout << "*****************************************************************************" << endl;
	cout << "The winner is :" << findWinner() << endl;
	cout << "*****************************************************************************" << endl;
}
void Start::tournament()
{
	setPlayerQty();
	setMapQty();
	setGameQty();
	setTurnQty();
	//create an initial tournament table.
	vector<string> temp5;
	temp5.push_back("Map \\ Game");
	for (int j = 0; j < gameQty; j++)
	{
		temp5.push_back(to_string(j + 1));
	}
	tournamentTable.push_back(temp5);
	for (int i = 0; i < mapQty; i++)
	{
		vector<string>temp6; temp6.push_back(to_string(i + 1)); tournamentTable.push_back(temp6);
	}

	setArmyQty_startup();
	displayAllMap();
	selectStrategy();
	displayInitialData();

	for (int i = 0; i < mapQty; i++)
	{
		selectMaptoPlay(i);
		mapPtr = new Map(selectedMap);
		deckPtr = new Deck(mapPtr->getCountry().size());
		setPlayers();
		distributeCountriesToPlayers();
		cout << "=============Display deck(card) and hand(card) in startup phase================" << endl;
		displayDeck();
		displayHand_AllPlayers();
		cout << "=================Display player's countries in startup phase===================" << endl;
		displayAllCountryForEachPlayer();
		cout << "===================Distribute armies for startup phase=========================" << endl;
		distributeArmy_startup_forEachPlayer();
		randomOrderOfPlay();
		for (int j = 0; j < gameQty; j++)
		{
			for (int k = 0; k < turnQty; k++)
			{

				for (int i = 0; i < box.size(); i++)
				{
					find_numberOfCountry(allPlayers);
					Subject subj;
					Player1_Observer player1(&subj, countryNum_player1);
					Player2_Observer player2(&subj, countryNum_player2);
					Player3_Observer player3(&subj, countryNum_player3);
					Player4_Observer player4(&subj, countryNum_player4);

					subj.setVal(totalQtyofCountry);
					box[loopSequence[i] - 1].execute(allPlayers, deckPtr, armyQty_startup, loopSequence[i]);
					countryNum_player1 = 0; countryNum_player2 = 0; countryNum_player3 = 0;
					countryNum_player4 = 0;
					if (checkGameOver(1) == true)
						break;
				}
				if (checkGameOver(1) == true)
				{
					tournamentTable[i + 1].push_back(findWinner());
					break;
				}
			}
			if (checkGameOver(1) == false)
			{
				tournamentTable[i + 1].push_back("Draw");
			}
		}
		allPlayers.clear();
	}
	displayFinalData();
}
void Start::selectMaptoPlay()
{
	int mapNum;
	cout << "Please select a Map to play (from 0 to " << allMap.size() - 1 << " ):" << endl;
	cin >> mapNum;
	bool exited = true;
	while (exited)
	{
		if (mapNum >= 0 && mapNum < allMap.size())
		{
			cout << "You selected " << mapNum << " map for this game." << endl;

			if (allMap[mapNum][2] == "---valid(Both countries and continents are connected.)")
			{
				cout << "The map " << mapNum << " is valid." << endl;
				selectedMap = allMap[mapNum][1];
				exited = false;
			}
			else
			{
				cout << "The map " << mapNum << " is invalid." << "Please select another map:" << endl;
				cin >> mapNum;
			}
		}
		else
		{
			cout << "The number you entered is invalid. Please try again:" << endl;
			cin >> mapNum;
		}
	}
}
//number of countries owned on the map, divided by 3(round down), with a minimum of 3
void Start::find_numberOfCountry(vector <Player*> allPlayers)
{
		totalQtyofCountry = (allPlayers[0]->getMapPtr()->getCountry()).size();
		for (int i = 0; i < (allPlayers[0]->getMapPtr()->getCountry()).size(); i++)
		{
			if ((allPlayers[0]->getMapPtr()->getCountry())[i]->getPlayerNum() == 1)
				countryNum_player1++;
		}
		for (int i = 0; i < (allPlayers[1]->getMapPtr()->getCountry()).size(); i++)
		{
			if ((allPlayers[1]->getMapPtr()->getCountry())[i]->getPlayerNum() == 2)
				countryNum_player2++;
		}
		if (playerQty>=3&&allPlayers[2]!=nullptr)
		{
			for (int i = 0; i < (allPlayers[2]->getMapPtr()->getCountry()).size(); i++)
			{
				if ((allPlayers[2]->getMapPtr()->getCountry())[i]->getPlayerNum() == 3)
					countryNum_player3++;
			}
		}
		if (playerQty >= 4 && allPlayers[3] != nullptr)
		{
			for (int i = 0; i < (allPlayers[3]->getMapPtr()->getCountry()).size(); i++)
			{
				if ((allPlayers[3]->getMapPtr()->getCountry())[i]->getPlayerNum() == 4)
					countryNum_player4++;
			}
		}
}
void Start::selectStrategy()
{
	vector<string> temp1; temp1.push_back("1"); temp1.push_back("Aggressive player"); strategyPlayers.push_back(temp1);
	vector<string> temp2; temp2.push_back("2"); temp2.push_back("Benevolent player"); strategyPlayers.push_back(temp2);
	vector<string> temp3; temp3.push_back("3"); temp3.push_back("Random player"); strategyPlayers.push_back(temp3);
	vector<string> temp4; temp4.push_back("4"); temp4.push_back("Cheater player"); strategyPlayers.push_back(temp4);
	cout << endl;
	for (int i = 0; i < playerQty; i++)
	{
		cout << "Player"<<i+1<<" wants to choose which strategy to play? " << endl;
		chooseStrategy(i+1);
	}
}
void Start::chooseStrategy(int i)
{
	cout << "You can select different kinds of players to play. There are following players." << endl;
	for (int i = 0; i < strategyPlayers.size(); i++)
	{
		for (int j = 0; j < strategyPlayers[i].size(); j++)
		{
			cout << strategyPlayers[i][j] << " ";
		}
		cout << endl;
	}
	int enterInt;
	cin >> enterInt;
	while (enterInt > 4 || enterInt < 1)
	{
		cout << "The integer you entered is not correct. Please try again: " << endl;
		cin >> enterInt;
	}
	putInStrategyBox(enterInt,i);
}
void Start::putInStrategyBox(int selectedNum, int i)
{
	switch (selectedNum)
	{
	case 1:
	    {
		   StrategyBox strategy1(new Strategy_aggressiveC());
		   vector<string> temp; temp.push_back(to_string(i)); temp.push_back("Aggressive"); playerWithStrategy.push_back(temp);
		   box.push_back(strategy1);
	    }
		break;
	case 2:
	    {
		   StrategyBox strategy2(new Strategy_benevolentC());
		   vector<string> temp; temp.push_back(to_string(i)); temp.push_back("Benevolent"); playerWithStrategy.push_back(temp);
		   box.push_back(strategy2);
	    }
		break;
	case 3:
	    {
		   StrategyBox strategy3(new Strategy_random());
		   vector<string> temp; temp.push_back(to_string(i)); temp.push_back("Random"); playerWithStrategy.push_back(temp);
		   box.push_back(strategy3);
	    }
		break;
	case 4:
	    {
		   StrategyBox strategy4(new Strategy_cheater());
		   vector<string> temp; temp.push_back(to_string(i)); temp.push_back("Cheater"); playerWithStrategy.push_back(temp);
		   box.push_back(strategy4);
	    }
	    break;

	}
}


//***********************************************************************************************************
//**********************************The followings are Part1*************************************************
//***********************************************************************************************************

//checking map valid or not and display all maps.Specify why the map is not valid.
void Start::displayAllMap()
{
	cout << "There are following maps in the directory. Waiting seconds..." << endl;
	cout << "Checking each country belongs to one and only one continent: " << endl;
	for (int i = 0; i < allMap.size(); i++)
	{
		Map map1(allMap[i][1]);
		int n1 = map1.getValue_validMap();
		int n2 = map1.getValue_validCountry();
		int n3 = map1.getValue_validContinent();
		if (n1 == 1)
			allMap[i].push_back("---valid(Both countries and continents are connected.)");
		else if (n1!=1&&n2==1&&n3!=1)
			allMap[i].push_back("---invalid(Countries are connected, but continents are not connected.)");
		else if(n1 != 1 && n2 != 1 && n3 == 1)
			allMap[i].push_back("---invalid(Continents are connected, but countries are not connected.)");
		else
			allMap[i].push_back("---invalid(Both countries and continents are not connected.)");
	}
	cout << endl;
	cout << "Checking the map is valid or not.Waiting seconds... " << endl;
	for (int i = 0; i < allMap.size(); i++)
	{
		for (int j = 0; j < allMap[i].size(); j++)
		{
			cout << allMap[i][j] << "  ";
		}
		cout << endl;
	}
}
//ask the user to enter the valid number of players to play the game (2-6)
void Start::setPlayerQty()
{
	int qtyEntered;
	bool exited = true;
	int gameGoOn;
	while (exited)
	{
		cout << "Please select the number of players in the game(2-4):" << endl;
		cin >> qtyEntered;
		if (qtyEntered >=2&& qtyEntered <=4)
		{
			exited = false;
			cout << "You selected " << qtyEntered << " players for this game." << endl;
			playerQty = qtyEntered;
		}
		else
		{
			cout << "The number you entered is invalid. Please try again." << endl;
		}
	}
}
void Start::setMapQty()
{
	int qtyEntered;
	bool exited = true;
	int gameGoOn;
	while (exited)
	{
		cout << "Please select the number of maps in the game(1-5):" << endl;
		cin >> qtyEntered;
		if (qtyEntered >= 1 && qtyEntered <= 5)
		{
			exited = false;
			cout << "You selected " << qtyEntered << " maps for this game." << endl;
			mapQty = qtyEntered;
		}
		else
		{
			cout << "The number you entered is invalid. Please try again." << endl;
		}
	}
}
void Start::setGameQty()
{
	int qtyEntered;
	bool exited = true;
	int gameGoOn;
	while (exited)
	{
		cout << "Please select the number of games in the game(1-5):" << endl;
		cin >> qtyEntered;
		if (qtyEntered >= 1 && qtyEntered <= 5)
		{
			exited = false;
			cout << "You selected " << qtyEntered << " games for this game." << endl;
			gameQty = qtyEntered;
		}
		else
		{
			cout << "The number you entered is invalid. Please try again." << endl;
		}
	}
}
void Start::setTurnQty()
{
	int qtyEntered;
	bool exited = true;
	int gameGoOn;
	while (exited)
	{
		cout << "Please select the number of turn in the game(10-50):" << endl;
		cin >> qtyEntered;
		if (qtyEntered >= 10 && qtyEntered <= 50)
		{
			exited = false;
			cout << "You selected " << qtyEntered << " turns for this game." << endl;
			turnQty = qtyEntered;
		}
		else
		{
			cout << "The number you entered is invalid. Please try again." << endl;
		}
	}
}
void Start::displayInitialData()
{
	cout << "***********************************************************************************" << endl;
	cout << "M: ";
	for (int i = 0; i < mapQty; i++)
	{
		cout << "Map " << i + 1 << ",";
	}
	cout << endl;

	cout << "P: ";
	for (int i = 0; i < playerWithStrategy.size(); i++)
	{
		cout << playerWithStrategy[i][1] << ",";
	}
	cout << endl;
	cout << "G: " << gameQty << endl;
	cout << "D: " << turnQty << endl;
	cout << "***********************************************************************************" << endl;
}
//ask the user to select a map to play. If the map is invalid, the user will be asked to select another one.
void Start::selectMaptoPlay(int index_map)
{
	selectedMap= allMap[index_map][1];
}
//put all players objects into a vector
void Start::setPlayers()
{
	for (int i = 0; i < playerQty; i++)
	{
		Player *player1 = new Player(mapPtr, i + 1);
		player1->setStartupArmyQty(armyQty_startup);
		allPlayers.push_back(player1);
	}
}
vector<vector<string>> Start::getAllMap()
{
	return allMap;
}
int Start::getPlayerQty()
{
	return playerQty;
}
string Start::getSelectedMap()
{
	return selectedMap;
}
vector<Player*> Start::getAllPlayers()
{
	return allPlayers;
}
Map* Start::getMapPtr()
{
	return mapPtr;
}
int Start::getArmyQty_startup()
{
	return armyQty_startup;
}
void Start::displayDeck()
{
	cout << "There are following cards in the deck:" << endl;
	for (int i = 0; i < deckPtr->size(); i++)
		cout << deckPtr->getCard(i).getType() << ",";
	cout << endl;
}
void Start::displayAllCountryForEachPlayer()
{
	for (int i = 0; i < allPlayers.size(); i++)
		displayMyCountry(i + 1);
}
//display all countries of the specific player.
void Start::displayMyCountry(int playerNumber)
{
	cout << "Player " << playerNumber << " has the following countries(country name,continent name,player number, quantity of armies):" << endl;
	for (int i = 0; i < (mapPtr->getCountry()).size(); i++)
	{
		if ((mapPtr->getCountry())[i]->getPlayerNum() == playerNumber)
			cout << (mapPtr->getCountry())[i]->displayCountry();
	}
	cout << endl;
}
//display all the cards in hand of a specific player.
void Start::displayHand_AllPlayers()
{
	for (int i = 0; i < allPlayers.size(); i++)
	{
		cout << "Player" << i + 1 << " has the following cards in hand :" << endl;
		allPlayers[i]->displayMyHand();
	}
}
//***********************************************************************************************************
//**********************************The followings are Part2*************************************************
//***********************************************************************************************************
void Start::randomOrderOfPlay()
{
	cout << "The order of play of the players in the game is determined randomly." << endl;
	srand(time(NULL));
	tempDynamicArray = new int[playerQty];
	int r;
	for (int i = 0; i < playerQty; i++)
	{
		tempDynamicArray[i] = i + 1;
	}
	for (int j = playerQty; j > 0; j--)
	{
		r = rand() % j;
		loopSequence.push_back(tempDynamicArray[r]);
		while (r < j - 1)
		{
			tempDynamicArray[r] = tempDynamicArray[r + 1];
			r++;
		}
	}
	cout << endl;
	cout << "The random order is (according to the index of the vector box ): " << endl;
	for (int i = 0; i < playerQty; i++)
	{
		cout << loopSequence[i] << ",";
	}
	cout << endl;
}
//randomly distributing all countries to players.
void Start::distributeCountriesToPlayers()
{
	srand(time(NULL));
	for (int i = 0; i < allPlayers[0]->getMapPtr()->getTotalNumOfCountry(); i++)
	{
		int randNum = rand() % playerQty + 1;
		allPlayers[0]->getMapPtr()->getCountry()[i]->setPlayerNum(randNum);
	}
}
void Start::setArmyQty_startup()
{
	switch (playerQty)
	{
	case 2:
		armyQty_startup = 40; break;
	case 3:
		armyQty_startup = 35; break;
	case 4:
		armyQty_startup = 30; break;
	case 5:
		armyQty_startup = 25; break;
	case 6:
		armyQty_startup = 20; break;
	}
}
//in the startup phase, distribute all armies for all players
void Start::distributeArmy_startup_forEachPlayer()
{
	for (int i = 0; i < allPlayers.size(); i++)
		distributeArmy_startup(i + 1);
}
//in the startup phase, distribute all armies for the specific player
void Start::distributeArmy_startup(int playerNum)
{
	//displayMyCountry(playerNum);
	while (allPlayers[playerNum - 1]->getStartupArmyQty() > 0)
	{
		for (int i = 0; i < (mapPtr->getCountry()).size(); i++)
		{
			if ((mapPtr->getCountry())[i]->getPlayerNum() == playerNum)
			{
				(mapPtr->getCountry())[i]->setNumberOfArmies((mapPtr->getCountry())[i]->getNumOfArmies() + 1);
				allPlayers[playerNum - 1]->setStartupArmyQty(allPlayers[playerNum - 1]->getStartupArmyQty() - 1);
				if (allPlayers[playerNum - 1]->getStartupArmyQty() == 0)
					break;
			}
		}
	}
	cout << "Now, you do not have any armies to distribute." << endl;
	cout << "You distributed armies for all your countries: " << endl;
	//displayMyCountry(playerNum);
}
//check if the distributed number exceeds the source number of the player in startup phase.
bool Start::checkArmyQtytoDistribute_startup(int armyQtytoDistribute, int playerNum)
{
	if (armyQtytoDistribute <= allPlayers[playerNum - 1]->getStartupArmyQty())
		return true;
	return false;
}
bool Start::checkGameOver(int attackerNum)
{
	int size = allPlayers[attackerNum - 1]->getMapPtr()->getTotalNumOfCountry();
	int playerNum = allPlayers[attackerNum - 1]->getMapPtr()->getCountry()[0]->getPlayerNum();
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (allPlayers[attackerNum - 1]->getMapPtr()->getCountry()[i]->getPlayerNum() == playerNum)
			count++;
	}
	if (count == size)
	{
		cout << "Game over. Player" << playerNum << " conquered all the countries." << endl;
		cout << "********************************Game over******************************" << endl;
		return true;
	}
	return false;
}
string Start::findWinner()
{
	int playerNum = allPlayers[1]->getMapPtr()->getCountry()[0]->getPlayerNum();
	for (int i = 0; i < playerWithStrategy.size(); i++)
	{
		if (playerNum == stoi(playerWithStrategy[i][0]))
			return playerWithStrategy[i][1];
	}
}
void Start::displayFinalData()
{
	for (int i = 0; i < tournamentTable.size(); i++)
	{
		for (int j = 0; j < tournamentTable[i].size(); j++)
		{
			cout.setf(ios::left);
			cout.width(15);
			cout << tournamentTable[i][j];
		}

		cout << endl;
	}
}

Start::~Start()
{
	delete mapPtr;
	delete deckPtr;
}
