#include "Player.h"
#include <list>
#include "../network/Client.h"

Player::Player(Client* client) : client(client) {

}

int Player::getId()
{
	return id;
}

void Player::setId(int newId)
{
	id = newId;
}

void Player::setPointJoueur(int newPoint)
{
	point += newPoint;
}

void Player::setCarteJoueur()
{
	Carte *carte = new Carte();
}

std::list<Carte> Player::getCarteJoueur()
{
	std::list<Carte> cartes;
	return cartes;
}

int Player::getPointJoueur()
{
	return point;
}
