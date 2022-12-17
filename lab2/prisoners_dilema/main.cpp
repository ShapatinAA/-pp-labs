#include <iostream>
#include <string>
#include "prisoners_habbit/prisoners_habbit.h"

int main(int argc, char* argv[]) {

	arguments arguments_of_the_game(argc, argv);

	game game;

	game.play_game(&arguments_of_the_game, argc, argv);


}
