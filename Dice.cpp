#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Dice.h"

Dice::Dice() {

}
//ask player how many rolls first, then calling rollDice function
//and return an array with size of 3 with the rolled dice numbers
void Dice::rolling(int times_roll)
{
	//use the system time as random seed?make sure rand won't return a Pseudo random)
	srand((unsigned)time(NULL));
	//generate random numbers by calling rollDices()
	for (int i = 0; i < times_roll; i++) {
		diceNum = rand() % 6 + 1;
		rollArray.push_back(diceNum);
	}
}
//dice rolling function, return a int dice number 1~6
int Dice::rollDice() {
	//use the system time as random seed?make sure rand won't return a Pseudo random)
	//srand((unsigned)time(NULL));
	//generate random numbers
	diceNum = rand() % 6 + 1;
	//count the total random number and the appear of this number
	//display the precentage of getting this number, and save it to the container
	switch (diceNum) {
	case 1:
		one++;
		count++;
		cout << "The probability to get 1 is: " << one << "/" << count << endl;
		saveDice(diceNum);
		break;
	case 2:
		two++;
		count++;
		cout << "The probability to get 2 is: " << two << "/" << count << endl;
		saveDice(diceNum);
		break;
	case 3:
		three++;
		count++;
		cout << "The probability to get 3 is: " << three << "/" << count << endl;
		saveDice(diceNum);
		break;
	case 4:
		four++;
		count++;
		cout << "The probability to get 4 is: " << four << "/" << count << endl;
		saveDice(diceNum);
		break;
	case 5:
		five++;
		count++;
		cout << "The probability to get 5 is: " << five << "/" << count << endl;
		saveDice(diceNum);
		break;
	case 6:
		six++;
		count++;
		cout << "The probability to get 6 is: " << six << "/" << count << endl;
		saveDice(diceNum);
		break;
	}
	return diceNum;
}
//save the rolled dice into dice number container
int Dice::saveDice(int d) {
	container.push_back(d);
	//diceList.insert(diceList.end(),d);
	return 0;
}
//return how many rolls the player wants to roll
int Dice::getRolls() {

	return rolls;
}
vector<int> Dice::getRollArray()
{
	return rollArray;
}
void Dice::clearRollArray()
{
	rollArray.clear();
}
//traverse the dice number container(vector) and return all of the numbers
int Dice::getContainer() {

	for (auto &vec : container) {
		cout << vec << " ";
	}
	return 0;
}
Dice::~Dice()
{

}
