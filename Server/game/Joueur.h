#pragma once
#include <list>
#include <memory>
#include <string>

#include "Carte.h"
class Client;

class Joueur {

private:
	const char* TAG = "[Joueur] ";

	std::string name;
	int point;
	std::list<std::unique_ptr<Carte>> cards;

public:
	Joueur();

	void setPointJoueur(int newPoint);
	void set_cards(std::list<std::unique_ptr<Carte>> &cards);
	void set_name(const std::string name);

	const std::string& get_name();
	int getPointJoueur();
	std::list<std::unique_ptr<Carte>> &get_cards();
};