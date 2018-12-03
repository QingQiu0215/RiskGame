//-----------------------------------
//Written by:Qing Qiu, 40022237
//For COMP 345 Fall 2018
//-----------------------------------
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include "MapLoader.h"

MapLoader::MapLoader(string srcName)
{
	getMapInfo(srcName);
}
MapLoader::MapLoader()
{
	MapLoader("srcName");
}
void MapLoader::getMapInfo(string srcName)
{
	string str1 = "[Map]";
	string str2 = "[Continents]";
	string str3 = "[Territories]";
	input_map.open(srcName);
	if (input_map.fail())
	{
		cout << "Unable to open file: " << srcName << endl;
		//exit(1);
	}
	//=====================read author info====================================
	string str;
	string temp;
	getline(input_map, str);
	str = "";
	while (getline(input_map, str))
	{
		vector<string> temp1;
		if (str.compare(str2) == 0)
		{
			break;
		}
		stringstream checkl(str);
		while (getline(checkl, temp, '='))
		{
			temp1.push_back(temp);
		}
		mapInfo.push_back(temp1);
		str = "";
	}
	//=====================read continent info====================================
	str = "";
	while (getline(input_map, str))
	{
		vector<string> temp2;
		if (str.compare(str3) == 0)
		{
			break;
		}
		stringstream checkl(str);
		while (getline(checkl, temp, '='))
		{
			temp2.push_back(temp);
		}
		mapInfo_continent.push_back(temp2);
		str = "";
	}

	//================read country info===========================
	str = "";
	while (getline(input_map, str))
	{
		vector<string> temp3;
		stringstream checkl(str);
		while (getline(checkl, temp, ','))
		{
			temp3.push_back(temp);
		}
		mapInfo_country.push_back(temp3);
		str = "";
	}
	putCountryToContinent();
	setContinentMatrix();
	//displayFile();
}
//put all countries to continent vector, the first column of the vector is the continent name
//the remaining columns are country names.
void MapLoader::putCountryToContinent()
{
	for (int i = 0; i < mapInfo_continent.size() - 1; i++)
	{
		vector<string> temp;
		temp.push_back(mapInfo_continent[i][0]);
		for (int j = 0; j < mapInfo_country.size(); j++)
		{
			if (mapInfo_continent[i][0] == mapInfo_country[j][3])
			{
				temp.push_back(mapInfo_country[j][0]);
			}
		}
		continentContainCountries.push_back(temp);
	}

}

//return index of the country in the vector mapInfo_country
int MapLoader::indexOfCountry1(string countryName)
{
	int i;
	for (i = 0; i < mapInfo_country.size(); i++)
	{
		if (mapInfo_country[i][0] == countryName)
			return i;
	}
}
//to generate a matrix that contain connected continent. Just like:
//continent1: continent2, continent3
//continent2: continent3, continent4
//continent3: continent4, continent5
//...
//this method is for checking if all continents are connected 
void MapLoader::setContinentMatrix()
{
	for (int i = 0; i < continentContainCountries.size(); i++)
	{
		vector<string> temp;
		temp.push_back(continentContainCountries[i][0]);
		for (int j = 1; j < continentContainCountries[i].size(); j++)
		{
			for (int m = i + 1; m < continentContainCountries.size(); m++)
			{
				for (int n = 1; n < continentContainCountries[m].size(); n++)
				{
					if (connectedCountry(continentContainCountries[i][j], continentContainCountries[m][n]))
					{
						temp.push_back(continentContainCountries[m][0]);
						break;
					}
				}
			}
		}
		continentMatrixTemp.push_back(temp);
	}
	//delete all the duplicated continents.
	int count = 0;
	for (int i = 0; i < continentMatrixTemp.size(); i++)
	{
		vector<string> temp;
		temp.push_back(continentMatrixTemp[i][0]);
		for (int j = 1; j < continentMatrixTemp[i].size(); j++)
		{
			int m;
			for (m = 0; m < j; m++)
			{
				if (continentMatrixTemp[i][j] != continentMatrixTemp[i][m])
					count++;
			}
			if (count == m)
				temp.push_back(continentMatrixTemp[i][j]);
			count = 0;
		}
		continentMatrix.push_back(temp);
	}
}
//check if two countries are connected 
bool MapLoader::connectedCountry(string countryA, string countryB)
{
	for (int i = mapInfo_country[indexOfCountry1(countryA)].size() - 1; i > 3; i--)
	{
		if (mapInfo_country[indexOfCountry1(countryA)][i] == countryB)
			return true;
	}
	return false;
}
void MapLoader::displayFile()
{
	for (int i = 0; i < continentMatrix.size(); i++)
	{
		for (int j = 0; j < continentMatrix[i].size(); j++)
		{
			cout << continentMatrix[i][j] << " ,";
		}
		cout << endl;
	}
}

vector<vector<string>>  MapLoader::getMapInfo()
{
	return mapInfo;
}
vector<vector<string>>  MapLoader::getMapInfo_continent()
{
	return mapInfo_continent;
}
vector<vector<string>>  MapLoader::getMapInfo_country()
{
	return mapInfo_country;
}
vector<vector<string>>  MapLoader::getContinentContainCountries()
{
	return continentContainCountries;
}
vector<vector<string>>  MapLoader::getContinentMatrix()
{
	return continentMatrix;
}
MapLoader::~MapLoader()
{}