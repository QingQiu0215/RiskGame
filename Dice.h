#ifndef DICE_H
#define DICE_H
#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Dice
{
public:
	Dice();
	//dice rolling function, ask player how many rolls, and return an array with 3 random numbers
	void rolling(int times_roll);
	//generate a random number, and display the probability of getting this number, return a int
	int rollDice();
	//save the ramdom number into container
	int saveDice(int d);
	//return the rolls (how many dices player wants to roll)
	int getRolls();
	vector<int> getRollArray();
	void clearRollArray();
	////traverse the dice number container(vector) and return all of the numbers
	int getContainer();
	~Dice();
private:
	//the number on the dice side, and the number of rolls
	int diceNum, rolls;
	//count number of each dice number
	int count = 0, one = 0,
		two = 0, three = 0,
		four = 0, five = 0, six = 0;
	//array to store maximum 3 rolls
	vector<int> rollArray;
	//container of dice numbers
	vector<int> container;
	//list<int> diceList;
};

#endif