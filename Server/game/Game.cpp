#include "Game.h"
#include "iostream"
#include <list>
using namespace std;

Game::Game() {
	nbPlayerReady = 0;
	nbTour = 0;
}

void Game::addPlayer(Player *newPlayer) {
	cout << "ADD JOUEUR" << endl;
	Players.push_back(newPlayer);
}

void Game::setPlayerReady() {
	++nbPlayerReady;
	if (Players.size() >= 2 && nbPlayerReady == Players.size()) {
		startGame();
	}
}

void Game::startGame() {
	cout << "START GAME" << endl;
	//TODO for sur les players
	//for de 0 à 10
	//Creation d'une nouvelle carte d'un nombre aléatoire entre 1 et 104
	//addNewCarte au player actuel
	//Creation d'une nouvelle boucle for parcours tt les players
	//Envoie aux players la list carte
}
