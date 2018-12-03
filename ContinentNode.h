//-----------------------------------
//Written by:Qing Qiu, 40022237
//For COMP 345 Fall 2018
//-----------------------------------

#ifndef CONTINENTNODE_H
#define CONTINENTNODE_H

#include <iostream>
using namespace std;

class ContinentNode
{
public:
	ContinentNode();
	ContinentNode(string newContinentName, int controlValue);
	string getContinentName();
	void setContinentName(string newContinent);
	int getContinentValue();
	void setContinentValue(int newContinentValue);
private:
	friend class Map;
	string continentName;
	int continentValue;
};

#endif
