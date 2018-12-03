//-----------------------------------
//Written by:Qing Qiu, 40022237
//For COMP 345 Fall 2018
//-----------------------------------
#include <iostream>
using namespace std;
#include "continentNode.h"

ContinentNode::ContinentNode()
{
	continentName = "";
	continentValue = 0;
}
ContinentNode::ContinentNode(string newContinentName, int newContinentValue) :continentName(newContinentName), continentValue(newContinentValue)
{
}
string ContinentNode::getContinentName()
{
	return continentName;
}
void ContinentNode::setContinentName(string newContinentNum)
{
	continentName = newContinentNum;
}
int ContinentNode::getContinentValue()
{
	return continentValue;
}
void ContinentNode::setContinentValue(int newContinentValue)
{
	continentValue = newContinentValue;
}





