//-----------------------------------
//Written by:Qing Qiu, 40022237
//For COMP 345 Fall 2018
//-----------------------------------
#include <iostream>
#include <vector>
#include <new>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include "Map.h"
#include "MapLoader.h"
using namespace std;

Map::Map(string newMapName)
{
	mapName = newMapName;
	loaderPtr = new MapLoader(newMapName);

	totalNumOfCountry = loaderPtr->mapInfo_country.size();
	totalNumOfContinent = loaderPtr->mapInfo_continent.size() - 1;
	initCountry();
	initContinent();
	checkCountryToOneContinent(newMapName);
	validValue_country = checkValidCountry();
	validValue_continent = checkValidContinent();
	validValue_map = checkValidMap();
}
//return the index of the country in the vector mapInfo_country.
int Map::indexOfCountry(string countryName)
{
	int i;
	for (i = 0; i < totalNumOfCountry; i++)
	{
		if (loaderPtr->mapInfo_country[i][0] == countryName)
			return i;
	}
}
//return the index of the continent in the vector mapInfo_country.
int Map::indexOfContinent(string continentName)
{
	int i;
	for (i = 0; i < totalNumOfContinent; i++)
	{
		if (loaderPtr->continentMatrix[i][0] == continentName)
			return i;
	}
}
//check the map valid. Only both countries and continents are connected, the map is valid. Ohterwise, it is invalid.
bool Map::checkValidMap()
{
	if (checkValidCountry() == 1 && checkValidContinent() == 1)
		return true;
	return false;
}
//check if all countries are connected.Using DFS algorithm(start from a country) to search all 
//next connected countries(for example: a-b-c-d-e-.....), search one by one and store all connected 
//countries in the vector. Not duplicated!!!
//Finally, if the size of the vector is equal to the quantity of all counties. It means all countries 
//are connected.
bool Map::checkValidCountry()
{
	vector<string> tempVector1;
	vector<string> tempVector2;
	int count = 0;
	tempVector1.push_back(loaderPtr->mapInfo_country[0][0]);
	tempVector2.push_back(loaderPtr->mapInfo_country[0][0]);
	for (int i = 0; i < tempVector2.size(); i++)
	{
		for (int j = loaderPtr->mapInfo_country[indexOfCountry(tempVector2[i])].size() - 1; j > 3; j--)
		{
			int m;
			for (m = 0; m < tempVector2.size(); m++)
			{
				if (tempVector2[m] != loaderPtr->mapInfo_country[indexOfCountry(tempVector2[i])][j])
					count++;
			}
			if (m == count)
				tempVector1.push_back(loaderPtr->mapInfo_country[indexOfCountry(tempVector2[i])][j]);
			count = 0;
		}
		tempVector2 = tempVector1;
	}
	if (tempVector2.size() != totalNumOfCountry)
	{
		return false;
	}
	return true;
}
//using the same algorithm as countries.
bool Map::checkValidContinent()
{
	vector<string> tempVector1;
	vector<string> tempVector2;
	int count = 0;
	tempVector1.push_back(loaderPtr->continentMatrix[0][0]);
	tempVector2.push_back(loaderPtr->continentMatrix[0][0]);
	for (int i = 0; i < tempVector2.size(); i++)
	{
		for (int j = loaderPtr->continentMatrix[indexOfContinent(tempVector2[i])].size() - 1; j > 0; j--)
		{
			int m;
			for (m = 0; m < tempVector2.size(); m++)
			{
				if (tempVector2[m] != loaderPtr->continentMatrix[indexOfContinent(tempVector2[i])][j])
					count++;
			}
			if (m == count)
				tempVector1.push_back(loaderPtr->continentMatrix[indexOfContinent(tempVector2[i])][j]);
			count = 0;
		}
		tempVector2 = tempVector1;
	}
	if (tempVector2.size() != totalNumOfContinent)
	{
		return false;
	}
	return true;
}
//create objects for all countries
void Map::initCountry()
{
	string countryN, continentN;
	for (unsigned int i = 0; i < totalNumOfCountry; i++)
	{
		CountryNode* p = nullptr;
		try
		{
			countryN = loaderPtr->mapInfo_country[i][0];
			continentN = loaderPtr->mapInfo_country[i][3];
			p = new CountryNode(countryN, continentN, 0, 0);
			country.push_back(p);
		}
		catch (bad_alloc)
		{
			cout << "Run out of memory.";
			exit(1);
		}
	}
}
//create objects for all continents
void Map::initContinent()
{
	string continentN;
	int value;
	for (unsigned int i = 0; i < totalNumOfContinent; i++)
	{
		ContinentNode* c = nullptr;
		try
		{
			continentN = loaderPtr->getMapInfo_continent()[i][0];
			c = new ContinentNode(continentN, 0);
			continent.push_back(c);
		}
		catch (bad_alloc)
		{
			cout << "Run out of memory.";
			exit(1);
		}
	}
}
//check if the country belongs to one continent
void Map::checkCountryToOneContinent(string newMapName)
{
	if (!checkDuplicate_country())
		cout << newMapName<<": Yes.Each country belongs to one and only one continent." << endl;
	int i, j;
	for (i = 0; i < totalNumOfCountry - 1; i++)
	{
		for (j = i + 1; j < totalNumOfCountry; j++)
		{
			if (loaderPtr->mapInfo_country[i][0] == loaderPtr->mapInfo_country[j][0])
			{
				if (loaderPtr->mapInfo_country[i][3] == loaderPtr->mapInfo_country[j][3])
				{
					cout << newMapName<<": No.Some countries belongs to more than one continent.";
					return;
				}
			}
		}
	}
}
//this is a help method for method checkCountryToOneContinent(string newMapName)
bool Map::checkDuplicate_country()
{
	int i, j;
	for (i = 0; i < totalNumOfCountry - 1; i++)
	{
		for (j = i + 1; j < totalNumOfCountry; j++)
		{
			if (loaderPtr->mapInfo_country[i][0] == loaderPtr->mapInfo_country[j][0])
			{
				return true;
			}
		}
	}
	return false;
}

string Map::getMapName()
{
	return mapName;
}
int Map::getTotalNumOfCountry()
{
	return totalNumOfCountry;
}
int Map::getTotalNumOfContinent()
{
	return totalNumOfContinent;
}
void Map::setMapName(string newMapName)
{
	mapName = newMapName;
}

vector <CountryNode*> Map::getCountry()
{
	return country;
}
vector <ContinentNode*> Map::getContinent()
{
	return continent;
}
MapLoader*  Map::getLoaderPtr()
{
	return loaderPtr;
}
Map::~Map()
{
	delete loaderPtr;
}