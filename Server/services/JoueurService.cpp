#include "JoueurService.h"

std::unique_ptr<JoueurService> JoueurService::instance;

JoueurService &JoueurService::get_instance() {
	if (instance == nullptr || instance.get() == nullptr) {
		instance = std::unique_ptr<JoueurService>(new JoueurService());
	}
	return *instance;
}

void JoueurService::add_joueur(std::unique_ptr<Joueur> joueur) {
	if (joueur == nullptr)return;
	joueurs.push_back(std::move(joueur));
}

void JoueurService::remove_joueur(Joueur &joueur) {
	joueurs.remove_if([&](const std::unique_ptr<Joueur>& p1) { return &joueur == p1.get(); });
}

int JoueurService::get_nbr_players() {
	return joueurs.size();
}