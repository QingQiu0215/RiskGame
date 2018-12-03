//-----------------------------------
//Written by:Qing Qiu, 40022237
//For COMP 345 Fall 2018
//-----------------------------------


#ifndef MAP_H
#define MAP_H
#include <iostream>
using namespace std;
#include <vector>
#include "CountryNode.h"
#include "ContinentNode.h"
#include "MapLoader.h"

class Map
{
public:
	Map(string countryName);
	string getMapName();
	void setMapName(string newMapName);
	int getTotalNumOfCountry();
	int getTotalNumOfContinent();

	int indexOfCountry(string countryName);
	int indexOfContinent(string continentName);
	bool checkValidCountry();
	bool checkValidContinent();
	bool checkValidMap();
	void initCountry();
	void initContinent();
	int getValue_validMap() { return validValue_map; };
	int getValue_validCountry() { return validValue_country; };
	int getValue_validContinent() { return validValue_continent; };
	void checkCountryToOneContinent(string newMapName);
	bool checkDuplicate_country();
	vector <CountryNode*> getCountry();
	vector <ContinentNode*> getContinent();
	MapLoader* getLoaderPtr();

	~Map();
private:
	string mapName;
	int totalNumOfCountry;
	int totalNumOfContinent;
	MapLoader* loaderPtr;//a pointer that points the class MapLoader
	vector <CountryNode*> country;//a vector to store all country nodes
	vector <ContinentNode*> continent;//a vector to store all country nodes

	int validValue_country;
	int validValue_continent;
	int validValue_map;
};

#endif