#pragma once
#include <list>
#include <memory>
#include <string>

#include "Carte.h"
class Client;

class Player {

private:
	const char* TAG = "[Player] ";

	std::string name;
	int point;
	std::list<std::unique_ptr<Carte>> cards;

public:
	Player();

	void setPointPlayer(int newPoint);
	void set_cards(std::list<std::unique_ptr<Carte>> &cards);
	void set_name(const std::string name);

	const std::string& get_name();
	int getPointPlayer();
	std::list<std::unique_ptr<Carte>> &get_cards();
};