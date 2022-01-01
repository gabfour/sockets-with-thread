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
	void deckDeDepart();
	void supprCarte(Carte carte);
	void ajouterCarte(Carte carte);
};