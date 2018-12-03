//-----------------------------------
//Written by:Qing Qiu, 40022237
//For COMP 345 Fall 2018
//-----------------------------------

#ifndef MAPLOADER_H;
#define MAPLOADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class MapLoader
{
public:
	MapLoader();
	MapLoader(string srcName);
	~MapLoader();
	void getMapInfo(string srcName);
	vector<vector<string>> getMapInfo();
	vector<vector<string>> getMapInfo_continent();
	vector<vector<string>> getMapInfo_country();
	vector<vector<string>> getContinentContainCountries();
	vector<vector<string>> getContinentMatrix();
	int indexOfCountry1(string countryName);
	void putCountryToContinent();
	void setContinentMatrix();
	bool connectedCountry(string countryA, string countryB);
	void displayFile();
private:
	friend class Map;
	ifstream input_map;
	vector<vector<string>> mapInfo;
	vector<vector<string>> mapInfo_continent;//store the information of continent in the 2D vector
	vector<vector<string>> mapInfo_country;//store the information of countries in the 2D vector
	vector<vector<string>> continentContainCountries;//each continent contain its countries
	vector<vector<string>> continentMatrixTemp;
	vector<vector<string>> continentMatrix;
};

#endif

