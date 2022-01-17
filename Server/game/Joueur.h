#pragma once
#include <list>
#include <string>

#include "Carte.h"
class Client;

class Joueur {

private:
	const char* TAG = "[Joueur] ";

	std::string name;
	int point;
	std::list<Carte> cartes;

	void setPointJoueur(int newPoint);
	void setCarteJoueur();
public:
	Joueur();

	void set_name(const std::string name);

	const std::string& get_name();
	int getPointJoueur();
	std::list<Carte> getCarteJoueur();
};