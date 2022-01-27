#ifndef JOUEURSERVICE_H_
#define JOUEURSERVICE_H_

#include <memory>
#include <list>

#include "../game/Player.h"

class PlayerService {
public:
	static PlayerService &get_instance();

	void add_player(std::unique_ptr<Player> player);
	void remove_player(Player&player);

	int get_nbr_players();
private:
	static std::unique_ptr<PlayerService> instance;

	std::list<std::unique_ptr<Player>> players;
};

#endif