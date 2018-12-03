#ifndef STRATEGY_RANDOM_H
#define STRATEGY_RANDOM_H
#include <iostream>
#include "Strategy.h"
#include "Player.h"
#include "Deck.h"
using namespace std;

class Strategy_random :public Strategy
{
public:
	void execute(vector <Player*> allPlayers, Deck* deckPtr, int armyQty_startup, int playerNum);

	void reinforce(vector <Player*> allPlayers, Deck* deckPtr, int armyQty_startup, int playerNum);
	void makeArmyQty_numberOfCountry(vector <Player*> allPlayers, int playerNum);
	void makeArmyQty_continentValue(vector <Player*> allPlayers, int playerNum);
	void makeArmyQty_exchangeCard(vector <Player*> allPlayers, int playerNum);
	void makeReinforcementArmyQty(vector <Player*> allPlayers, int playerNum);
	void distributeArmy_reinforcement(vector <Player*> allPlayers, int armyQty_startup, int playerNum);
	int findCountryIndex_random(vector <Player*> allPlayers, int playerNum);
	int findCountryIndex_largestArmyQty(vector <Player*> allPlayers, int playerNum);
	string findCountryName_largestArmyQty(vector <Player*> allPlayers, int playerNum);
	void displayMyCountry(vector <Player*> allPlayers, int playerNum);

	void attack(vector <Player*> allPlayers, Deck* deckPtr, int playerNum);
	bool checkValidCountry_attacker(vector <Player*> allPlayers, string countryName, int playerNum);
	int indexOfCountry(vector <Player*> allPlayers, string countryName, int playerNum);
	void displayNeighborCountries(vector <Player*> allPlayers, string theAttackerCountry, int playerNum);
	bool checkValidCountry_defender(vector <Player*> allPlayers, string countryName, int playerNum);
	int playerNum_defenderCountry(vector <Player*> allPlayers, string defenderCountry, int playerNum);
	void attackerRolling(vector <Player*> allPlayers, string theAttackerCountry, int playerNum);
	void defenderRolling(vector <Player*> allPlayers, string theDefenderCountry, int playerNum);
	void compareDiceAndFight(vector <Player*> allPlayers, string theAttackerCountry, string theDefenderCountry, int playerNum, int defenderNum);
	bool checkGameOver(vector <Player*> allPlayers, int playerNum);

	void fortify(vector <Player*> allPlayers, int playerNum);
	void displayNeighborCountries_inFortification(vector <Player*> allPlayers, string theAttackerCountry, int playerNum);
	int findNeighborCountryIndex_random(vector <Player*> allPlayers, int playerNum);
	int index_targetCountry(vector <Player*> allPlayers, string targetCountry, int playerNum);
	int index_sourceCountry(vector <Player*> allPlayers, string sourceCountry, int playerNum);
private:
	int armyQtytoDistribute = 0;
	int numOfsuccessfulConquer = 0;
	int defenderNum;
	vector<int> rollArrayForComputer;
};
#endif