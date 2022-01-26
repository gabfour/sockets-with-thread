#pragma once
#include <list>
#include "Carte.h"

class Deck {

private:
	std::list<Carte> deck;

public:
	Deck();
	~Deck();
	std::list<Carte> getDeck();
	void startingDeck();
	void deleteCard(Carte carte);
	void addCard(Carte carte);
};