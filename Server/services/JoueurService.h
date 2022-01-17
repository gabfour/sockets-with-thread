#ifndef JOUEURSERVICE_H_
#define JOUEURSERVICE_H_

#include <memory>
#include <list>

#include "../game/Joueur.h"

class JoueurService {
public:
	static JoueurService &get_instance();

	void add_joueur(std::unique_ptr<Joueur> joueur);
	void remove_joueur(Joueur &joueur);

	int get_nbr_players();
private:
	static std::unique_ptr<JoueurService> instance;

	std::list<std::unique_ptr<Joueur>> joueurs;
};

#endif