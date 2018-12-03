#include "Hand.h"

Hand::Hand()
{}

void Hand::exchange(int index)
{
	if (index >= hand.size())
	{
		std::cout << "wrong number!" << endl;
	}
	else
	{
		hand.erase(hand.begin() + index);//delete the card in the hand
		//player->setTroopNum(player->getTroopNum() + 5);//increment troop of player
	}
}
bool Hand::addCard(Card card)
{
	hand.push_back(card);
	return true;
}
Card Hand::getCard(int index)
{
	return hand.at(index);
}
int Hand::size()
{
	return hand.size();
}
vector<Card> Hand::getHand()
{
	return hand;
}
void Hand::clearHand()
{
	hand.clear();
}
Hand::~Hand()
{

}
