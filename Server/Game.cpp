#include "Game.h"
#include "Carte.h"
#include "Joueur.h"
#include "iostream"
#include <list>
using namespace std;

Game::Game() {
	nbJoueurReady = 0;
}

void Game::addJoueur(Joueur *newJoueur) {
	Joueurs.push_back(newJoueur);
	cout <<  "newJoueur" << endl;
	cout << Joueurs.size() << endl;
}

void Game::setJoueurReady() {
	++nbJoueurReady;
	if (Joueurs.size() >= 2 && nbJoueurReady == Joueurs.size()) {
		startGame();
	}
}

void Game::startGame() {
	cout << "START GAME" << endl;
	//TODO for sur les joueurs
	//for de 0 à 10
	//Creation d'une nouvelle carte d'un nombre aléatoire entre 1 et 104
	//addNewCarte au joueur actuel
	//Creation d'une nouvelle boucle for parcours tt les joueurs
	//Envoie aux joueurs la list carte
	for (Joueur *joueurActual : Joueurs)
	{
		for (int j = 0; j < 10; j++)
		{
			int val = rand() % 104;
			Carte *carte = new Carte(val, 1);
			joueurActual->setCarteJoueur(carte);
		}
		joueurActual->sendCarteToClient();
	}
}
