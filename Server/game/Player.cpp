#include "Player.h"
#include "../network/Client.h"

Player::Player() : point(0), cards() {
	Output::GetInstance()->print(TAG, "New unknown player\n");
}

void Player::set_name(const std::string name) {
	this->name = name;
}

void Player::setPointPlayer(int newPoint)
{
	point += newPoint;
}


void Player::set_cards(std::list<std::unique_ptr<Carte>>& cards) {
	this->cards.clear();
	for (auto it = cards.begin(); it != cards.end(); it++) {
		this->cards.push_back(std::move(*it));
	}
}

const std::string& Player::get_name() {
	return name;
}

int Player::getPointPlayer()
{
	return point;
}

std::list<std::unique_ptr<Carte>>& Player::get_cards() {
	return cards;
}