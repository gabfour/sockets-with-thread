#pragma once
#include <list>
#include <memory>
#include <string>

#include "Carte.h"
class Client;

class Player {

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

<<<<<<< HEAD:Server/game/Joueur.h
	const std::string& get_name();
=======
public:
	Player(Client* client);
>>>>>>> 4f943eb901d92a4b0ce4901128631ab040b5d263:Server/game/Player.h
	int getPointJoueur();
	std::list<std::unique_ptr<Carte>> &get_cards();
};