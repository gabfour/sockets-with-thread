#pragma once
#include <list>
class Player;

class Game {

private:
	std::list<Player*> Joueurs;
	int nbTour;
	int nbJoueurReady;

	void startGame();
public:
	Game();
	void addJoueur(Player *newJoueur);
	void setJoueurReady();
};