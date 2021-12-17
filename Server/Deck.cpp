#include "Deck.h"
#include <list>
#include <iostream>
#include "Carte.h"
#include <math.h>

//int Deck::cartesRestantes(std::list<Carte> cartes)
//{
//	return 0;
//}

Deck::Deck() {}

Deck::~Deck() {}

void Deck::deckDeDepart() {

	for (int i = 1; i < 105; i++) {
		Carte carte;
		carte.setVal(i);

		int dizaine = floor(i / 10);
		int unite = i - dizaine * 10;

		if (unite == dizaine) {
			carte.setPoint(5);
		}
		else if (i % 10 == 0) {
			carte.setPoint(3);
		}
		else if (i % 5 == 0) {
			carte.setPoint(2);
		}
		else {
			carte.setPoint(1);
		}
		deck.push_back(carte);
	}

}

std::list<Carte> Deck::getDeck() {
	return Deck::deck;
}

void Deck::supprCarte(Carte carte) {
	deck.remove(carte);
}


void Deck::ajouterCarte(Carte carte) {
	deck.push_back(carte);
}