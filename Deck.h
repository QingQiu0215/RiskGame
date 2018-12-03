#ifndef DECK_H
#define DECK_H
#include "Card.h"
#include "Hand.h"

class Deck
{
public:
	Deck();
	Deck(int countryNum);
	Card draw(Hand* player);
	int size();
	Card getCard(int index);
	~Deck();
private:
	vector<Card> deck;

};
#endif