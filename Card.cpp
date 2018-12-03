#include <string>
#include <ctime>
#include "Card.h"

Card::Card()
{
	type = "/";
}

Card::Card(string assign)
{
	type = assign;
}
string Card::getType()
{
	return type;
}
Card::~Card()
{

}




