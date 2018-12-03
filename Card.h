#ifndef CARD_H
#define CARD_H

#include <iostream>
using namespace std;

class Card
{
public:
	Card();
	Card(string assign);
	string getType();
	~Card();
private:
	string type;

};



#endif


