#include "Joueur.h"
#include <list>
#include "Client.h"
#include <string>

Joueur::Joueur(Client* client) : client(client) {
	id = 0;
	id++;
	point = 0;
}

int Joueur::getId()
{
	return id;
}

void Joueur::setId(int newId)
{
	id = newId;
}

void Joueur::setPointJoueur(int newPoint)
{
	point += newPoint;
}

void Joueur::setCarteJoueur(Carte *carte)
{
	cartes.push_back(*carte);
}

std::list<Carte> Joueur::getCarteJoueur()
{
	return cartes;
}

int Joueur::getPointJoueur()
{
	return point;
}

void Joueur::sendCarteToClient() 
{
	//gestion envoie en JSON
	std::string message = "";
	for (Carte c : cartes) {
		message += std::to_string(c.getValCarte()) + " / " + std::to_string(c.getPointCarte()) + ",";
	}
	client->send_message(message.c_str());
}
