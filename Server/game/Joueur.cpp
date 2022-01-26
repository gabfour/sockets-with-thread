#include "Joueur.h"
#include "../network/Client.h"

Joueur::Joueur() : point(0), cards() {
	Output::GetInstance()->print(TAG, "New unknown player\n");
}

void Joueur::set_name(const std::string name) {
	this->name = name;
}

void Joueur::setPointJoueur(int newPoint)
{
	point += newPoint;
}


void Joueur::set_cards(std::list<std::unique_ptr<Carte>> &cards) {
	this->cards.clear();
	for (auto it = cards.begin(); it != cards.end(); it++) {
		this->cards.push_back(std::move(*it));
	}
}

const std::string& Joueur::get_name() {
	return name;
}

int Joueur::getPointJoueur()
{
	return point;
}

std::list<std::unique_ptr<Carte>>& Joueur::get_cards() {
	return cards;
}