#include "Joueur.h"
#include "../network/Client.h"

Joueur::Joueur() : point(0), cartes() {
	Output::GetInstance()->print(TAG, "New unknown player\n");
}

void Joueur::set_name(const std::string name) {
	this->name = name;
}

void Joueur::setPointJoueur(int newPoint)
{
	point += newPoint;
}

void Joueur::setCarteJoueur()
{
	//Carte *carte = new Carte();
}

const std::string& Joueur::get_name() {
	return name;
}

std::list<Carte> Joueur::getCarteJoueur()
{
	std::list<Carte> cartes;
	return cartes;
}

int Joueur::getPointJoueur()
{
	return point;
}
