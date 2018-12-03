//-----------------------------------
//Written by:Qing Qiu, 40022237
//For COMP 345 Fall 2018
//-----------------------------------
#ifndef START_H
#define START_H
#include <iostream>
#include <vector>
#include "Player.h"
#include "Strategy_user.h"
#include "Strategy_aggressiveC.h"
#include "Strategy_benevolentC.h"
#include "Strategy_random.h"
#include "Strategy_cheater.h"
#include "Deck.h"
#include "StrategyBox.h"
using namespace std;

class Start
{
public:
	Start();
	vector<vector<string>> getAllMap();
	void find_numberOfCountry(vector <Player*> allPlayers);
	void selectStrategy();
	void putInStrategyBox(int selectedNum,int i);
	void chooseStrategy(int i);
	int getPlayerQty();
	string getSelectedMap();
	void displayAllMap();
	void setPlayerQty();
	void selectMaptoPlay(int index_map);
	void setPlayers();
	Map* getMapPtr();
	vector <Player*> getAllPlayers();
	int getArmyQty_startup();
	void setArmyQty_startup();
	void displayDeck();
	void displayMyCountry(int playerNumber);
	void distributeArmy_startup(int playerNum);
	bool checkArmyQtytoDistribute_startup(int armyQtytoDistribute, int playerNum);
	void displayAllCountryForEachPlayer();
	void distributeArmy_startup_forEachPlayer();
	void displayHand_AllPlayers();
	void randomOrderOfPlay();
	void distributeCountriesToPlayers();
	bool checkGameOver(int attackerNum);
	string findWinner();

	void singleGame();
	void tournament();
	void selectMaptoPlay();
	void setMapQty();
	void setGameQty();
	void setTurnQty();
	void displayInitialData();
	void displayFinalData();
	~Start();
private:
	vector<vector<string>> allMap;
	string selectedMap;
	vector <Player*> allPlayers;
	Map* mapPtr = nullptr;
	int armyQty_startup;
	Deck* deckPtr = nullptr;
	int armyQtytoDistribute = 0;
	int numOfsuccessfulConquer = 0;
	int* tempDynamicArray;//get an array without duplicate.
	vector<int> loopSequence;
	vector<vector<string>> strategyPlayers;
	vector<StrategyBox> box;
	vector<vector<string>> playerWithStrategy;
	vector<vector<string>> tournamentTable;
	int countryNum_player1=0;
	int countryNum_player2=0;
	int countryNum_player3=0;
	int countryNum_player4 = 0;
	int totalQtyofCountry = 0;
	int mapQty;
	int playerQty;
	int gameQty;
	int turnQty;
};


#endif