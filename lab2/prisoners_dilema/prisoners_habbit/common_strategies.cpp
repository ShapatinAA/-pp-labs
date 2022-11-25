#include <iostream>
#include <string>
#include <random>
#include <time.h>
#include <fstream>
#include "prisoners_habbit.h"

void player::player_calculate_next_move_switcher(player* player_switcher, arguments arguments_of_the_game) {
	int i = 0;
	while (true) {
		if (arguments_of_the_game.players[i] == "switcher") break;
		i++;
	}
	if (!(arguments_of_the_game.answers_sheet[i]).empty()) {
		if (arguments_of_the_game.answers_sheet[i][arguments_of_the_game.answers_sheet[i].size() - 1] == '1')
		{
			(*player_switcher).next_move = 0;
		}
		else
		{
			(*player_switcher).next_move = 1;
		}
	}
	else (*player_switcher).next_move = 1;
}

void player::player_calculate_next_move_liar(player* player_liar) {
	(*player_liar).next_move = 0;
};

void player::player_calculate_next_move_naive(player* player_naive) {
	(*player_naive).next_move = 0;
};

void player::player_calculate_next_move_unpredictable(player* player_unpredictable) {
	srand( (int)time(NULL) );
	(*player_unpredictable).next_move = rand() % 2;
};

void analyse_other_players(int*** sequences_of_players, int position_of_other_player, arguments arguments_of_the_game) {
	int amount_of_true = 0;
	int amount_of_false = 0;
	bool last_symbol = arguments_of_the_game.answers_sheet[position_of_other_player][0] - '0';
	for (int i = 0; i < arguments_of_the_game.answers_sheet[position_of_other_player].size(); i++) {
		if (arguments_of_the_game.answers_sheet[position_of_other_player][i] == '1') amount_of_true++; else amount_of_false++;
		if (last_symbol != (bool)((arguments_of_the_game.answers_sheet[position_of_other_player][i] - '0'))) {
			if (last_symbol == 1) {
				sequences_of_players[position_of_other_player][last_symbol][amount_of_true]++;
				amount_of_true = 0;
				last_symbol = 0;
			}
			else {
				sequences_of_players[position_of_other_player][last_symbol][amount_of_false]++;
				amount_of_false = 0;
				last_symbol = 1;
			}
		}
	}
	if (last_symbol == 1) {
		sequences_of_players[position_of_other_player][last_symbol][amount_of_true]++;
		amount_of_true = 0;
		last_symbol = 0;
	}
	else {
		sequences_of_players[position_of_other_player][last_symbol][amount_of_false]++;
		amount_of_false = 0;
		last_symbol = 1;
	}

};

int get_likely_outcome_true(int*** sequences_of_players, int position_of_other_player, arguments arguments_of_the_game) {
	int likely_amount_of_true = 0;
	int max_amount_of_trues = 0;
	for (int i = 0; i <= arguments_of_the_game.answers_sheet[0].size(); i++) {
		if (sequences_of_players[position_of_other_player][1][i] > max_amount_of_trues) {
			max_amount_of_trues = sequences_of_players[position_of_other_player][1][i];
			likely_amount_of_true = i;
		}
	}
	if (max_amount_of_trues == 1) likely_amount_of_true = -likely_amount_of_true;
	return likely_amount_of_true;
};

int get_likely_outcome_false(int*** sequences_of_players, int position_of_other_player, arguments arguments_of_the_game) {
	int likely_amount_of_false = 0;
	int max_amount_of_falses = 0;
	for (int i = 0; i <= arguments_of_the_game.answers_sheet[0].size(); i++) {
		if (sequences_of_players[position_of_other_player][0][i] > max_amount_of_falses) {
			max_amount_of_falses = sequences_of_players[position_of_other_player][0][i];
			likely_amount_of_false = i;
		}
	}
	if (max_amount_of_falses == 1) likely_amount_of_false = -likely_amount_of_false;
	return likely_amount_of_false;
};

bool* get_likely_move_of_other_players(int*** sequences_of_players, arguments arguments_of_the_game) {
	bool* likely_move_of_players = new bool[2];
	int position_of_smart_player = 0;
	while (true) {
		if (arguments_of_the_game.players[position_of_smart_player] == "smart") break;
		position_of_smart_player++;
	}

	analyse_other_players(sequences_of_players, (position_of_smart_player + 1) % 3, arguments_of_the_game);
	analyse_other_players(sequences_of_players, (position_of_smart_player + 2) % 3, arguments_of_the_game);

	if (arguments_of_the_game.answers_sheet[(position_of_smart_player + 1) % 3][arguments_of_the_game.answers_sheet[(position_of_smart_player + 1) % 3].size() - 1] == '1') {
		int likely_amount_of_true_first = get_likely_outcome_true(sequences_of_players, (position_of_smart_player + 1) % 3, arguments_of_the_game);

		if (likely_amount_of_true_first < 0) {
			likely_move_of_players[0] = 1;
		}
		else {
			int curr_pos1 = arguments_of_the_game.answers_sheet[(position_of_smart_player + 1) % 3].size() - 1;
			for (curr_pos1; arguments_of_the_game.answers_sheet[(position_of_smart_player + 1) % 3][curr_pos1] == arguments_of_the_game.answers_sheet[(position_of_smart_player + 1) % 3][curr_pos1 - 1]; curr_pos1--);
			if (arguments_of_the_game.answers_sheet[(position_of_smart_player + 1) % 3].size() - curr_pos1 == likely_amount_of_true_first) likely_move_of_players[0] = 0;
			else likely_move_of_players[0] = 1;
		}

	}
	else {
		int likely_amount_of_false_first = get_likely_outcome_false(sequences_of_players, (position_of_smart_player + 1) % 3, arguments_of_the_game);

		if (likely_amount_of_false_first < 0) {
			likely_move_of_players[0] = 0;
		}
		else {
			int curr_pos1 = arguments_of_the_game.answers_sheet[(position_of_smart_player + 1) % 3].size() - 1;
			for (curr_pos1; arguments_of_the_game.answers_sheet[(position_of_smart_player + 1) % 3][curr_pos1] == arguments_of_the_game.answers_sheet[(position_of_smart_player + 1) % 3][curr_pos1 - 1]; curr_pos1--);
			if (arguments_of_the_game.answers_sheet[(position_of_smart_player + 1) % 3].size() - curr_pos1 == likely_amount_of_false_first) likely_move_of_players[0] = 1;
			else likely_move_of_players[0] = 0;
		}
	}

	if (arguments_of_the_game.answers_sheet[(position_of_smart_player + 2) % 3][(arguments_of_the_game.answers_sheet[(position_of_smart_player + 2) % 3].size()) - 1] == '1') {
		int likely_amount_of_true_second = get_likely_outcome_true(sequences_of_players, (position_of_smart_player + 2) % 3, arguments_of_the_game);

		if (likely_amount_of_true_second < 0) {
			likely_move_of_players[1] = 1;
		}
		else {
			int curr_pos2 = arguments_of_the_game.answers_sheet[(position_of_smart_player + 2) % 3].size() - 1;
			for (curr_pos2; arguments_of_the_game.answers_sheet[(position_of_smart_player + 2) % 3][curr_pos2] == arguments_of_the_game.answers_sheet[(position_of_smart_player + 2) % 3][curr_pos2 - 1]; curr_pos2--);
			if (arguments_of_the_game.answers_sheet[(position_of_smart_player + 2) % 3].size() - curr_pos2 == likely_amount_of_true_second) likely_move_of_players[1] = 0;
			else likely_move_of_players[1] = 1;
		}
	}
	else {
		int likely_amount_of_false_second = get_likely_outcome_false(sequences_of_players, (position_of_smart_player + 2) % 3, arguments_of_the_game);

		if (likely_amount_of_false_second < 0) {
			likely_move_of_players[1] = 0;
		}
		else {
			int curr_pos2 = arguments_of_the_game.answers_sheet[(position_of_smart_player + 2) % 3].size() - 1;
			for (curr_pos2; arguments_of_the_game.answers_sheet[(position_of_smart_player + 2) % 3][curr_pos2] == arguments_of_the_game.answers_sheet[(position_of_smart_player + 2) % 3][curr_pos2 - 1]; curr_pos2--);
			if (arguments_of_the_game.answers_sheet[(position_of_smart_player + 2) % 3].size() - curr_pos2 == likely_amount_of_false_second) likely_move_of_players[1] = 1;
			else likely_move_of_players[1] = 0;
		}
	}
	return likely_move_of_players;
}

void player::player_calculate_next_move_smart(player* player_smart, arguments arguments_of_the_game) {
	int*** sequences_of_players = new int** [2];
	sequences_of_players[0] = new int* [2];
	sequences_of_players[1] = new int* [2];
	sequences_of_players[0][0] = new int[arguments_of_the_game.answers_sheet[0].size()+1]; //вот тут fatal flaw, потому что если игра будет больше 300 ходов
	memset(sequences_of_players[0][0], 0, sizeof(int) * (arguments_of_the_game.answers_sheet[0].size()+1));
	sequences_of_players[0][1] = new int[arguments_of_the_game.answers_sheet[0].size()+1];
	memset(sequences_of_players[0][1], 0, sizeof(int) * (arguments_of_the_game.answers_sheet[0].size()+1));
	sequences_of_players[1][0] = new int[arguments_of_the_game.answers_sheet[0].size()+1];
	memset(sequences_of_players[1][0], 0, sizeof(int) * (arguments_of_the_game.answers_sheet[0].size()+1));
	sequences_of_players[1][1] = new int[arguments_of_the_game.answers_sheet[0].size()+1];
	memset(sequences_of_players[1][1], 0, sizeof(int) * (arguments_of_the_game.answers_sheet[0].size()+1));

	bool* likely_move_of_players = get_likely_move_of_other_players(sequences_of_players, arguments_of_the_game);

	if ((likely_move_of_players[1] == 1) && (likely_move_of_players[0] == 1)) (*player_smart).next_move = 1;
	else (*player_smart).next_move = 0;

	delete[] sequences_of_players[1][1];
	delete[] sequences_of_players[1][0];
	delete[] sequences_of_players[0][1];
	delete[] sequences_of_players[0][0];
	delete[] sequences_of_players[1];
	delete[] sequences_of_players[0];
	delete[] sequences_of_players;
	delete[] likely_move_of_players;
};

void player::player_calculate_next_move_side(player* player_side, arguments arguments_of_the_game) {};