#pragma once
#include <list>
#include "Carte.h"
class Client;

class Joueur {

private:
	Client* client;
	int id;
	int point;
	std::list<Carte> cartes;

	int getId();
	void setId(int newId);
	void setPointJoueur(int newPoint);

public:
	Joueur(Client* client);
	int getPointJoueur();
	std::list<Carte> getCarteJoueur();
	void setCarteJoueur(Carte* carte);
	void sendCarteToClient();
};