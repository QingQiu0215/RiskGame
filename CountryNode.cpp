//-----------------------------------
//Written by:Qing Qiu, 40022237
//For COMP 345 Fall 2018
//-----------------------------------

#include <iostream>
#include <string>
using namespace std;
#include "CountryNode.h"

CountryNode::CountryNode()
{
	country = "";
	continent = "";
	playerNum = 0;
	numOfArmies = 0;
}
CountryNode::CountryNode(string newCountry, string newContinent, int newPlayerNum, int newNumOfArmies)
{
	country = newCountry;
	continent = newContinent;
	playerNum = newPlayerNum;
	numOfArmies = newNumOfArmies;
}
string CountryNode::getCountry()
{
	return country;
}
string CountryNode::getContinent()
{
	return continent;
}
int CountryNode::getPlayerNum()
{
	return playerNum;
}
int CountryNode::getNumOfArmies()
{
	return numOfArmies;
}
void CountryNode::setCountry(string newCountry)
{
	country = newCountry;
}
void CountryNode::setContinent(string newContinent)
{
	continent = newContinent;
}
void CountryNode::setPlayerNum(int newPlayerNum)
{
	playerNum = newPlayerNum;
}
void CountryNode::setNumberOfArmies(int newNumOfArmies)
{
	numOfArmies = newNumOfArmies;
}
string CountryNode::displayCountry()
{
	string str = country + ", " + continent + ", " + to_string(playerNum) + ", " + to_string(numOfArmies) + "\n";
	return str;
}
CountryNode::~CountryNode()
{}

