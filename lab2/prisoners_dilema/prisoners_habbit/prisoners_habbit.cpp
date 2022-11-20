#include <iostream>
#include <string>
#include <random>
#include <time.h>
#include <fstream>
#include "prisoners_habbit.h"



/*...................................................................класс аргументов...........................................................................*/



arguments::arguments(int argc, char* argv[]):
	mode("detailed"),
	steps(0),
	configs(""),
	matrix(""),
	players(),
	answers_sheet(nullptr)
{
	arguments_get_players(players, argc, argv);
	arguments_get_mode(&mode, argc, argv);
	arguments_get_configs(&configs, argc, argv);
	arguments_get_matrix(&matrix, argc, argv);
	arguments_get_steps(&steps, argc, argv);
	arguments_get_answers_sheet(answers_sheet, matrix);
}

arguments::~arguments() {
	delete[] players;
}

void arguments::arguments_get_players(std::string* players, int argc, char* argv[]) {
	int i;
	for (i = 1; (i!=argc) && (argv[i][0] != '-'); i++) {}
	i--;
	if (i < 3) {
		std::cout << "\nyour number of players is incorrect, please reopen the program\n";
		abort();
	}
	players = new std::string[3];
	if (players == nullptr) {
		std::cout << "\nerror in memorry allocation\n";
		abort();
	}
	for (i; i; i--) {
		(players)[i-1] = argv[i];
	}
};

void arguments::arguments_get_mode(std::string* mode, int argc, char* argv[]) {
	for (int i = 4; i < argc; i++) {
		int flag = (int)((std::string)argv[i]).find("--mode=");
		if (flag != (std::string::npos)) {
			*mode = ((std::string)argv[i]).substr(7, ((std::string)argv[i]).length() - 1);
			mode->erase(mode->length() - 1);
			*mode = (*mode).substr(1, (*mode).length());
			break;
		}
	}
	if (*mode == "detailed")	{} else
	if (*mode == "fast")		{} else
	if (*mode == "tournament")  {} else
	{
		std::cout << "\nyou typed wrong mode, please reopen the program\n";
		abort();
	}
}

void arguments::arguments_get_configs(std::string* config, int argc, char* argv[]) {
	for (int i = 4; i < argc; i++) {
		int flag = (int)((std::string)argv[i]).find("--configs=");
		if (flag != (std::string::npos)) {
			*config = ((std::string)argv[i]).substr(10,((std::string)argv[i]).length()-1);
			config->erase(config->length() - 1);
			*config = (*config).substr(1, (*config).length());
			break;
		}
	}
	std::ifstream if_exists;
	if_exists.open(*config);
	if (!if_exists) {
		std::cout << "\nprovided config does not exist\n";
		if_exists.close();
		abort();
	}
	if_exists.close();
}

void arguments::arguments_get_matrix(std::string* matrix, int argc, char* argv[]) {
	for (int i = 4; i < argc; i++) {
		int flag = (int)((std::string)argv[i]).find("--matrix=");
		if (flag != (std::string::npos)) {
			*matrix = ((std::string)argv[i]).substr(9, ((std::string)argv[i]).length() - 1);
			matrix->erase(matrix->length() - 1);
			*matrix = (*matrix).substr(1, (*matrix).length());
			break;
		}
	}
	std::ifstream if_exists;
	if_exists.open(*matrix);
	if (!if_exists) {
		std::cout << "\nprovided matrix does not exist\n";
		if_exists.close();
		abort();
	}
	if_exists.close();
}

void arguments::arguments_get_steps(int* steps, int argc, char* argv[]) {
	for (int i = 4; i < argc; i++) {
		int flag = (int)((std::string)argv[i]).find("--steps=");
		if (flag != (std::string::npos)) {
			*steps = std::stoi(((std::string)argv[i]).substr(9, ((std::string)argv[i]).length() - 3)); //тут хз как поймать ошибку если переполнение Int
			break;
		}
	}
	if (*steps < 0) {
		std::cout << "\nnumber of steps in provided game is incorrect\n";
		abort();
	}
}

void arguments::arguments_get_answers_sheet(std::string* answers_sheet, std::string matrix) {
	answers_sheet = new std::string[3];
	if (answers_sheet == nullptr) {
		std::cout << "\nerror in memorry allocation\n";
		abort();
	}
	std::ifstream matrix_file(matrix);
	if (!matrix_file) {
		std::cout << "\nerror in oppening file\n";
		matrix_file.close();
		abort();
	}
	for (int i = 0; (getline(matrix_file, answers_sheet[i])) && (i < 3); i++);
	matrix_file.close();
	arguments_chech_if_sheet_okay(answers_sheet);
}

void arguments::arguments_chech_if_sheet_okay(std::string* answers_sheet) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < (answers_sheet)[i].size(); j++) {
			if ((answers_sheet[i][j] != '1') && (answers_sheet[i][j] != '0')) {
				std::cout << "the sheet of answers is incorrect, please reopen the program";
				abort();
			}
		}
	}
	for (int i = 0; i < 2; i++) {
		if (answers_sheet[i].size() != answers_sheet[i + 1].size()) {
			std::cout << "the sheet of answers is incorrect, please reopen the program";
			abort();
		}
	}
}



/*.....................................................................класс игроков............................................................................*/



player::player(int number_of_the_player, arguments arguments_of_the_game): 

	personality(0),
	next_move(false)
{
	player_get_personality(&personality, arguments_of_the_game.players[number_of_the_player]);
}

void player::player_get_personality(int* personality_int, std::string personality_string) {
	while (true) {
		if (!personality_string.compare("switcher")) {
			*personality_int = 1;
			break;
		}
		if (!personality_string.compare("liar")) {
			*personality_int = 2;
			break;
		}
		if (!personality_string.compare("naive")) {
			*personality_int = 3;
			break;
		}
		if (!personality_string.compare("smart")) {
			*personality_int = 4;
			break;
		}
		if (!personality_string.compare("switcher")) {
			*personality_int = 5;
			break;
		}
	}
}

player::~player() {}

/*void player::choose(player player1) {		//узнаём модель поведения
	switch (player1.personality) {
	case (1): {	
		switcher(player1);								//свитчер t-f-t
		return;
	}
	case (2): {
		liar(player1);									//лгун f-f-f
		return;
	}
	case (3): {
		naive(player1);									//правдивый t-t-t
		return;
	}
	case (4): {
		unpredictable(player1);							//рандом w-t-f
		return;
	}
	case (5): {
		smart(player1);									//умный
		return;
	}
	default: {
		std::cout << "\n There is something wrong with one of your players \n";
		return;
	}
	}
}*/