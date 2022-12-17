#include <iostream>
#include <string>
#include <random>
#include <time.h>
#include <fstream>
#include "prisoners_habbit.h"



/*...................................................................класс аргументов...........................................................................*/



arguments::arguments() :
	mode("detailed"),
	steps(0),
	configs(""),
	matrix(""),
	players(),
	answers_sheet()
{}

arguments::arguments(int argc, char* argv[]):
	mode("detailed"),
	steps(0),
	configs(""),
	matrix(""),
	players(),
	answers_sheet()
{
	int number_of_players;
	for (number_of_players = 1; (number_of_players != argc) && (argv[number_of_players][0] != '-'); number_of_players++) {

	}
	number_of_players--;
	players = arguments_get_players(players, argc, argv);
	arguments_get_mode(&mode, argc, argv);
	arguments_get_configs(&configs, argc, argv);
	arguments_get_matrix(&matrix, argc, argv);
	arguments_get_steps(&steps, argc, argv);
	answers_sheet = arguments_get_answers_sheet(answers_sheet, matrix, number_of_players);
}

arguments::arguments(const arguments& argument) :
	mode(argument.mode),
	steps(argument.steps),
	configs(argument.configs),
	matrix(argument.matrix),
	players(),
	answers_sheet()
{
	players = new std::string[3];
	if (players == nullptr) {
		std::cout << "\nerror in memorry allocation\n";
		abort();
	}
	players[0] = argument.players[0];
	players[1] = argument.players[1];
	players[2] = argument.players[2];
	
	answers_sheet = new std::string[3];
	if (answers_sheet == nullptr) {
		std::cout << "\nerror in memorry allocation\n";
		abort();
	}
	answers_sheet[0] = argument.answers_sheet[0];
	answers_sheet[1] = argument.answers_sheet[1];
	answers_sheet[2] = argument.answers_sheet[2];
}

arguments::~arguments() {
	delete[] players;
	delete[] answers_sheet;
}

std::string* arguments::arguments_get_players(std::string* players, int argc, char* argv[]) {
	int i;
	for (i = 1; (i!=argc) && (argv[i][0] != '-'); i++) {}
	i--;
	if (i < 3) {
		std::cout << "\nyour number of players is incorrect, please reopen the program\n";
		abort();
	}
	players = new std::string[i];
	if (players == nullptr) {
		std::cout << "\nerror in memorry allocation\n";
		abort();
	}
	for (i; i; i--) {
		(players)[i-1] = argv[i];
	}
	return players;
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
	if ((*config).empty()) return;
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
	if ((*matrix).empty()) return;
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

std::string* arguments::arguments_get_answers_sheet(std::string* answers_sheet, std::string matrix, int number_of_players) {
	answers_sheet = new std::string[number_of_players];
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
	for (int i = 0; (getline(matrix_file, answers_sheet[i])) && (i < number_of_players); i++);
	matrix_file.close();
	arguments_chech_if_sheet_okay(answers_sheet, number_of_players);
	return answers_sheet;
}

void arguments::arguments_chech_if_sheet_okay(std::string* answers_sheet, int number_of_players) {
	for (int i = 0; i < number_of_players; i++) {
		for (int j = 0; j < (answers_sheet)[i].size(); j++) {
			if ((answers_sheet[i][j] != '1') && (answers_sheet[i][j] != '0')) {
				std::cout << "the sheet of answers is incorrect, please reopen the program";
				abort();
			}
		}
	}
	for (int i = 0; i < number_of_players - 1; i++) {
		if (answers_sheet[i].size() != answers_sheet[i + 1].size()) {
			std::cout << "the sheet of answers is incorrect, please reopen the program";
			abort();
		}
	}
}


/*.....................................................................класс игроков............................................................................*/



player::player() :
	personality(0),
	next_move(true)
{}

player::player(std::string players_personality) :

	personality(0),
	next_move(true)
{
	player_get_personality(&personality, players_personality);
}

player::~player() {}

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
		if (!personality_string.compare("unpredictable")) {
			*personality_int = 4;
			break;
		}
		if (!personality_string.compare("smart")) {
			*personality_int = 5;
			break;
		}
		if (!personality_string.compare("marat")) {
			*personality_int = 6;
			break;
		}
		std::cout << "Wrong player choosen" << std::endl;
		abort();
	}

}

void player::player_calculate_next_move(arguments arguments_of_the_game) {
	switch (this->personality) {
	case (1): {
		player_calculate_next_move_switcher(this, arguments_of_the_game);								
		break;
	}
	case (2): {
		player_calculate_next_move_liar(this);
		break;
	}
	case (3): {
		player_calculate_next_move_naive(this);
		break;
	}
	case (4): {
		player_calculate_next_move_unpredictable(this);
		break;
	}
	case (5): {
		player_calculate_next_move_smart(this, arguments_of_the_game);
		break;
	}
	case (6): {
		player_calculate_next_move_marat(this, arguments_of_the_game);
		break;
	}
	default: {
		std::cout << "\n There is something wrong with one of your players \n";
		abort();
	}
	}
}

player* game::get_list_of_players(int argc, char* argv[]) {
	int i;
	for (i = 1; (i != argc) && (argv[i][0] != '-'); i++) {}
	i--;
	player* list_of_players = new player[i];
	if (list_of_players == nullptr) {
		std::cout << "\nerror in memorry allocation\n";
		abort();
	}
	for (i; i; i--) {
		(list_of_players)[i - 1] = player((std::string)argv[i]);
	}
	return list_of_players;
}

void game::renew_matrix_and_answers_sheet(player* list_of_players, arguments* arguments_of_the_game) {
	std::string curr_string = "";
	curr_string += arguments_of_the_game->answers_sheet[0] + (char)(list_of_players[0].next_move + '0') + '\n';
	curr_string += arguments_of_the_game->answers_sheet[1] + (char)(list_of_players[1].next_move + '0') + '\n';
	curr_string += arguments_of_the_game->answers_sheet[2] + (char)(list_of_players[2].next_move + '0');
	std::ofstream output_sheet_of_answers(arguments_of_the_game->matrix);
	if (output_sheet_of_answers.fail()) {
		std::cout << "Can not open file " << arguments_of_the_game->matrix << " to write within" << std::endl;
		abort();
	}
	output_sheet_of_answers << curr_string;
	output_sheet_of_answers.close();
	arguments_of_the_game->answers_sheet = arguments_of_the_game->arguments_get_answers_sheet(arguments_of_the_game->answers_sheet, arguments_of_the_game->matrix, 3);
}

void game::player_play_one_round(player* list_of_players, arguments* arguments_of_the_game) {
	list_of_players[0].player_calculate_next_move(*arguments_of_the_game);
	list_of_players[1].player_calculate_next_move(*arguments_of_the_game);
	list_of_players[2].player_calculate_next_move(*arguments_of_the_game);
	renew_matrix_and_answers_sheet(list_of_players, arguments_of_the_game);
}

void game::get_score_of_raw(std::string* answer_sheet, int raw_position, int* players_points) {
	switch (answer_sheet[0][raw_position]) {
	case ('0'): {
		switch (answer_sheet[1][raw_position]) {
		case ('0'): {
			switch (answer_sheet[2][raw_position]) {
			case ('0'): {
				players_points[0] += 1;
				players_points[1] += 1;
				players_points[2] += 1;
				break;
			}
			case ('1'): {
				players_points[0] += 5;
				players_points[1] += 5;
				players_points[2] += 0;
				break;
			}
			}
			break;
		}
		case ('1'): {
			switch (answer_sheet[2][raw_position]) {
			case ('0'): {
				players_points[0] += 5;
				players_points[1] += 0;
				players_points[2] += 5;
				break;
			}
			case ('1'): {
				players_points[0] += 9;
				players_points[1] += 3;
				players_points[2] += 3;
				break;
			}
			}
			break;
		}
		}
		break;
	}
	case('1'): {
		switch (answer_sheet[1][raw_position]) {
		case ('0'): {
			switch (answer_sheet[2][raw_position]) {
			case ('0'): {
				players_points[0] += 0;
				players_points[1] += 5;
				players_points[2] += 5;
				break;
			}
			case ('1'): {
				players_points[0] += 3;
				players_points[1] += 9;
				players_points[2] += 3;
				break;
			}
			}
			break;
		}
		case ('1'): {
			switch (answer_sheet[2][raw_position]) {
			case ('0'): {
				players_points[0] += 3;
				players_points[1] += 3;
				players_points[2] += 9;
				break;
			}
			case ('1'): {
				players_points[0] += 7;
				players_points[1] += 7;
				players_points[2] += 7;
				break;
			}
			}
			break;
		}

		}
		break;
	}
	}
}

int* game::get_players_score(arguments arguments_of_the_game) {
	int* players_score = new int[3]{0,0,0};
	for (int i = 0; i < arguments_of_the_game.answers_sheet[0].size(); i++) {
		get_score_of_raw(arguments_of_the_game.answers_sheet, i, players_score);
	}
	return players_score;
}

void game::print_players_score(int* players_points, arguments arguments_of_the_game) {
	std::cout << "Player named \"" << arguments_of_the_game.players[0] << "\" have " << players_points[0] << " points" << std::endl;
	std::cout << "Player named \"" << arguments_of_the_game.players[1] << "\" have " << players_points[1] << " points" << std::endl;
	std::cout << "Player named \"" << arguments_of_the_game.players[2] << "\" have " << players_points[2] << " points" << std::endl;
}

void game::print_players_score_last_raw(arguments arguments_of_the_game) {
	int* players_last_score = new int[3]{0,0,0};
	get_score_of_raw(arguments_of_the_game.answers_sheet, arguments_of_the_game.answers_sheet[0].size() - 1, players_last_score);
	std::cout << "Player named \"" << arguments_of_the_game.players[0] << "\" had " << players_last_score[0] << " points for the last round" << std::endl;
	std::cout << "Player named \"" << arguments_of_the_game.players[1] << "\" had " << players_last_score[1] << " points for the last round" << std::endl;
	std::cout << "Player named \"" << arguments_of_the_game.players[2] << "\" had " << players_last_score[2] << " points for the last round" << std::endl;
	delete[] players_last_score;
}

void game::print_players_choices(arguments arguments_of_the_game) {
	std::cout << "Player named \"" << arguments_of_the_game.players[0] << "\" made " << arguments_of_the_game.answers_sheet[0][arguments_of_the_game.answers_sheet[0].size() - 1] << " decision" << std::endl;
	std::cout << "Player named \"" << arguments_of_the_game.players[1] << "\" made " << arguments_of_the_game.answers_sheet[1][arguments_of_the_game.answers_sheet[0].size() - 1] << " decision" << std::endl;
	std::cout << "Player named \"" << arguments_of_the_game.players[2] << "\" made " << arguments_of_the_game.answers_sheet[2][arguments_of_the_game.answers_sheet[0].size() - 1] << " decision" << std::endl;
}

void game::print_games_layout(arguments arguments_of_the_game) {
	std::cout << arguments_of_the_game.answers_sheet[0] << std::endl;
	std::cout << arguments_of_the_game.answers_sheet[1] << std::endl;
	std::cout << arguments_of_the_game.answers_sheet[2] << std::endl;
}

void game::play_detailed_game(player* list_of_players, arguments* arguments_of_the_game) {
	int* players_score = get_players_score(*arguments_of_the_game);
	char c = 0;
	while (true) {
		std::cout << "Press ENTER key to continue or press \"q\" to exit" << std::endl;
		c = getc(stdin);
		if (c == 'q') break;
		player_play_one_round(list_of_players, arguments_of_the_game);
		players_score = get_players_score(*arguments_of_the_game);
		print_players_score(players_score, *arguments_of_the_game);
		print_players_choices(*arguments_of_the_game);
		print_players_score_last_raw(*arguments_of_the_game);
	}
	delete[] players_score;
}

void game::play_fast_game(player* list_of_players, arguments* arguments_of_the_game) {
	int* players_score;
	for (int i = 0; i < arguments_of_the_game->steps; i++) {
		player_play_one_round(list_of_players, arguments_of_the_game);
	}
	players_score = get_players_score(*arguments_of_the_game);
	print_players_score(players_score, *arguments_of_the_game);
	print_games_layout(*arguments_of_the_game);
}

char** game::make_new_argv(std::string* arguments_in_strings) {
	char* argv[] = {"",const_cast<char*>(arguments_in_strings[1].c_str()), const_cast<char*>(arguments_in_strings[2].c_str()), const_cast<char*>(arguments_in_strings[3].c_str()),const_cast<char*>(arguments_in_strings[4].c_str()),const_cast<char*>(arguments_in_strings[5].c_str()),const_cast<char*>(arguments_in_strings[6].c_str()),const_cast<char*>(arguments_in_strings[7].c_str())};
	/*char** argv = new char[8][];
	for (int i = 1; i < 8; i++) {
		int tmp = (arguments_in_strings[i].size());
		argv[i] = new char[8];
		for (int j = 0; j < arguments_in_strings[i].size(); j++) {
			argv[i][j] = arguments_in_strings[i][j];
		}
	}*/
	return argv;
}

arguments* game::make_new_arguments_for_tournament_game(arguments* arguments_of_the_game, int player_first, int player_second, int player_third, int trios_counter) {
	std::string* arguments_in_strings = new std::string[8];
	arguments_in_strings[4] = "--mode=[" + arguments_of_the_game->mode + ']';
	arguments_in_strings[7] = "--steps=[" + std::to_string(arguments_of_the_game->steps) + ']';
	arguments_in_strings[5] = "--configs=[" + arguments_of_the_game->configs + ']';
	arguments_in_strings[6] = "--matrix=[" + arguments_of_the_game->matrix + ']';
	arguments_in_strings[6].insert(arguments_in_strings[6].size() - 5, std::to_string(trios_counter));
	arguments_in_strings[1] = arguments_of_the_game->players[player_first];
	arguments_in_strings[2] = arguments_of_the_game->players[player_second];
	arguments_in_strings[3] = arguments_of_the_game->players[player_third];
	std::string curr_string = "";
	curr_string += arguments_of_the_game->answers_sheet[player_first]+'\n';
	curr_string += arguments_of_the_game->answers_sheet[player_second]+'\n';
	curr_string += arguments_of_the_game->answers_sheet[player_third];
	std::string file_for_matrix = arguments_of_the_game->matrix;
	file_for_matrix.insert(file_for_matrix.size() - 4, std::to_string(trios_counter));
	std::ofstream output_sheet_of_answers(file_for_matrix);
	if (output_sheet_of_answers.fail()) {
		std::cout << "Can not open file " << file_for_matrix << " to write within" << std::endl;
		abort();
	}
	output_sheet_of_answers << curr_string;
	output_sheet_of_answers.close();
	char** argv = make_new_argv(arguments_in_strings);
	char* argv2[] = {argv[0],argv[1],argv[2],argv[3],argv[4],argv[5],argv[6],argv[7]};
	arguments* arguments_of_the_tournament_game = new arguments{7, argv2};
	return arguments_of_the_tournament_game;
}

void game::play_tournament_game(arguments* arguments_of_the_game, int number_of_players) {
	int trios_number = 1;
	for (int i = number_of_players; i > 3; i--) {
		trios_number *= i;
	}
	for (int i = number_of_players - 3; i > 1; i--) {
		trios_number /= i;
	}
	int** all_players_score_by_games = new int* [trios_number];
	for (int w = 0; w < trios_number; w++) {
		all_players_score_by_games[w] = new int[3]{ 0,0,0 };
	}
	int trios_counter = 0;
	for (int i = 0; i < number_of_players - 2; i++) {
		for (int j = i+1; j < number_of_players - 1; j++) {
			for (int k = j + 1; k < number_of_players; k++) {
				player* list_of_players_for_tournament = new player[3]{arguments_of_the_game->players[i],arguments_of_the_game->players[j],arguments_of_the_game->players[k]};
				arguments* arguments_of_the_tournament_game = make_new_arguments_for_tournament_game(arguments_of_the_game,i,j,k,trios_counter);
				for (int w = 0; w < arguments_of_the_game->steps; w++) {
					player_play_one_round(list_of_players_for_tournament, arguments_of_the_tournament_game);
				}
				all_players_score_by_games[trios_counter] = get_players_score(*arguments_of_the_tournament_game);
				std::cout << "Trio with number " << trios_counter+1 << " got:" << std::endl;
				print_players_score(all_players_score_by_games[trios_counter], *arguments_of_the_tournament_game);
				print_games_layout(*arguments_of_the_tournament_game);
				trios_counter++;
			}
		}
	}
	int* overall_players_score = new int[number_of_players];
	for (int i = 0; i < number_of_players; i++) {
		overall_players_score[i] = 0;
	}
	for (int curr_player = 0; curr_player < number_of_players; curr_player++) {
		trios_counter = 0;
		for (int i = 0; i < number_of_players - 2; i++) {
			for (int j = i + 1; j < number_of_players - 1; j++) {
				for (int k = j + 1; k < number_of_players; k++) {
					if (curr_player == i) overall_players_score[curr_player] += all_players_score_by_games[trios_counter][0];
					if (curr_player == j) overall_players_score[curr_player] += all_players_score_by_games[trios_counter][1];
					if (curr_player == k) overall_players_score[curr_player] += all_players_score_by_games[trios_counter][2];
					trios_counter++;
				}
			}
		}
	}
	int coolest_player = 0, score_of_coolest_player = 0;
	for (int i = 0; i < number_of_players; i++) {
		if (score_of_coolest_player < overall_players_score[i]) {
			score_of_coolest_player = overall_players_score[i];
			coolest_player = i;
		}
	}
	for (int i = 0; i < number_of_players; i++) {
		std::cout << "Player number " << i+1 << " named " << arguments_of_the_game->players[i] << ". He have " << overall_players_score[i] << " points!" << std::endl;
	}
	std::cout << "The winner of the competition is player number " << coolest_player+1 << " named " << arguments_of_the_game->players[coolest_player] << ". He have " << score_of_coolest_player << " points!" << std::endl;
}

void game::play_game(arguments* arguments_of_the_game, int argc, char* argv[]) {
	if (arguments_of_the_game->mode == "detailed") {
		player* list_of_players = get_list_of_players(argc, argv);
		play_detailed_game(list_of_players, arguments_of_the_game);
	}
	if (arguments_of_the_game->mode == "fast") {
		player* list_of_players = get_list_of_players(argc, argv);
		play_fast_game(list_of_players, arguments_of_the_game);
	}
	if (arguments_of_the_game->mode == "tournament") {
		int number_of_players;
		for (number_of_players = 1; (number_of_players != argc) && (argv[number_of_players][0] != '-'); number_of_players++) {}
		number_of_players--;
		play_tournament_game(arguments_of_the_game, number_of_players);
	}
}