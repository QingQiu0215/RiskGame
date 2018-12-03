#ifndef HAND_H
#define HAND_H
#include "Card.h"
#include <vector>
class Hand
{
public:
	Hand();
	void exchange(int index);
	bool addCard(Card card);
	Card getCard(int index);
	vector<Card> getHand();
	void clearHand();
	int size();
	~Hand();
private:
	vector<Card> hand;
};
#endif
