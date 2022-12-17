#include <iostream>
#include <string>
#include <fstream>

										/*класс созданный для мэйна, он нужен чтобы определить параметры игры*/

class arguments {
public:
	
	arguments();
	arguments(int argc, char* argv[]);			//инициализация всех аргументов, поданных в начале.
	arguments(const arguments& argument);
	~arguments();

private:

	/*.......................................................достаём все предвыборки из аргументов командной строки.............................................*/

	std::string mode;				//режим игры
	int steps;						//колчисло шагов симуляции
	std::string configs;			//конфигурационный файл соседнего игрока
	std::string matrix;				//лист сделанных ходов
	std::string* players;			//игроки
	std::string* answers_sheet;		//преобразованый лист сделанных ходов, в виде матрица 3xn

	std::string* arguments_get_players(std::string* players, int argc, char* argv[]);
	void arguments_get_mode(std::string* mode, int argc, char* argv[]);
	void arguments_get_configs(std::string* config, int argc, char* argv[]);
	void arguments_get_matrix(std::string* matrix, int argc, char* argv[]);
	void arguments_get_steps(int* steps, int argc, char* argv[]);
	std::string* arguments_get_answers_sheet(std::string* answers_sheet, std::string matrix, int number_of_players);
	void arguments_chech_if_sheet_okay(std::string* answers_sheet, int number_of_players);

	friend class player;
	friend class game;
};

/*..............................................класс игрока, он определяет модель поведения конкретного заключённого...........................................*/

class player {

private:

	int personality;												//модель поведения
	bool next_move;													//следующий ход

	player();
	player(std::string players_personality);
	~player();

	void player_get_personality(int* personality_int, std::string players_personality);
	void player_calculate_next_move(arguments arguments_of_the_game);		//просчёт следующего хода игрока


/*....................................................................функции выбора для каждого типа..............................................................*/

	void player_calculate_next_move_switcher(player* player_switcher, arguments arguments_of_the_game);
	void player_calculate_next_move_liar(player* player_liar);
	void player_calculate_next_move_naive(player* player_naive);
	void player_calculate_next_move_unpredictable(player* player_unpredictable);
	void player_calculate_next_move_smart(player* player_smart, arguments arguments_of_the_game);
	void player_calculate_next_move_marat(player* player_marat, arguments arguments_of_the_game);

	friend class game;

};

class game {

private:

	void player_play_one_round(player* list_of_players, arguments* arguments_of_the_game);
	void get_score_of_raw(std::string* answer_sheet, int raw_position, int* players_points);
	int* get_players_score(arguments arguments_of_the_game);
	void print_players_score(int* players_points, arguments arguments_of_the_game);
	void print_players_score_last_raw(arguments arguments_of_the_game);
	void print_players_choices(arguments arguments_of_the_game);
	void print_games_layout(arguments arguments_of_the_game);
	void play_detailed_game(player* list_of_players, arguments* arguments_of_the_game);
	void play_fast_game(player* list_of_players, arguments* arguments_of_the_game);
	char** make_new_argv(std::string* arguments_in_strings);
	void play_tournament_game(arguments* arguments_of_the_game, int number_of_players);
	void renew_matrix_and_answers_sheet(player* list_of_players, arguments* arguments_of_the_game);
	player* get_list_of_players(int argc, char* argv[]);
	arguments* make_new_arguments_for_tournament_game(arguments* arguments_of_the_game, int player_first, int player_second, int player_third, int trios_counter);

public:

	void play_game(arguments* arguments_of_the_game, int argc, char* argv[]);

};