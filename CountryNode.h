//-----------------------------------
//Written by:Qing Qiu, 40022237
//For COMP 345 Fall 2018
//-----------------------------------

#ifndef COUNTRYNODE_H
#define COUNTRYNODE_H

#include <iostream>
using namespace std;

class CountryNode
{
public:
	CountryNode();
	~CountryNode();
	CountryNode(string newCountry, string newContinent, int newPlayerNum, int newNumOfArmies);
	string getCountry();
	string getContinent();
	int getPlayerNum();
	int getNumOfArmies();
	void setCountry(string newCountry);
	void setContinent(string newContinent);
	void setPlayerNum(int newPlayer);
	void setNumberOfArmies(int newNumOfArmies);
	string displayCountry();
private:
	string country;
	string continent;
	int playerNum;
	int numOfArmies;
};

#endif



