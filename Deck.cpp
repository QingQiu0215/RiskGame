#include "Deck.h"
#include <ctime> 
Deck::Deck()
{
	cout << "empty deck is created" << endl;
}

Deck::Deck(int countryNum)
{
	for (int i = 0; i < countryNum; i++)//create cards and put them in the deck
	{
		deck.push_back(Card("infantry"));
		deck.push_back(Card("cavalry"));
		deck.push_back(Card("artillery"));
	}
}
Card Deck::draw(Hand* player)
{
	srand(time(NULL));
	int random = rand() % deck.size();//get a random number as index
	player->addCard(deck.at(random));//put the card into hand
	deck.erase(deck.begin() + random);//replace the drew card by the last card in the deck
	return player->getCard(player->size() - 1);
}
int Deck::size()
{
	return deck.size();
}
Card Deck::getCard(int index)
{
	return deck.at(index);
}
Deck::~Deck()
{

}
