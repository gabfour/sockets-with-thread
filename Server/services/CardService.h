#ifndef CARDSERVICE_H_
#define CARDSERVICE_H_

#include <memory>
#include <list>
#include <string>

#include "../game/Carte.h"
#include "../game/Joueur.h"

class CardService {
public:
	static CardService& get_instance();

	void generate_game_cards();
	void randomize_game_cards();

	std::list<std::unique_ptr<Carte>> draw_cards(int nbr_cards = 1);

	void dispay_cards(std::list<std::unique_ptr<Carte>>& cards);
	void dispay_card(Carte& card);

	std::list<std::unique_ptr<Carte>>&	get_game_cards();
private:
	const std::string TAG = "[CardService] ";
	static std::unique_ptr<CardService> instance;

	std::list<std::unique_ptr<Carte>>	gameCards;
};

#endif