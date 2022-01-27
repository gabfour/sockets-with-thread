#pragma once
#include <list>
class Player;

class Game {

private:
	std::list<Player*> Players;
	int nbTour;
	int nbPlayerReady;

	void startGame();
public:
	Game();
	void addPlayer(Player *newPlayer);
	void setPlayerReady();
};