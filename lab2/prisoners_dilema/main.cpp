#include <iostream>
#include <string>
#include "prisoners_habbit/prisoners_habbit.h"

int main(int argc, char* argv[]) {

	arguments arguments_of_the_game(argc, argv);

	player* list_of_players = new player[3]{arguments_of_the_game.players[0], arguments_of_the_game.players[1], arguments_of_the_game.players[2]};

	(list_of_players[2]).player_calculate_next_move(arguments_of_the_game);
	

}
