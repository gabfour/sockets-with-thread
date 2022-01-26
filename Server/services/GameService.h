#ifndef GAMESERVICE_H_
#define GAMESERVICE_H_

#include <memory>
#include <list>
#include <string>

#include "../game/Carte.h"

class GameService {
public:
	static GameService& get_instance();

	void init();

	void display_board();
private:
	void create_the_board(std::list<std::unique_ptr<Carte>> &cards);
		
	const std::string TAG = "[GameService] ";
	static std::unique_ptr<GameService> instance;

	std::list<std::list<std::unique_ptr<Carte>>> board;
};

#endif