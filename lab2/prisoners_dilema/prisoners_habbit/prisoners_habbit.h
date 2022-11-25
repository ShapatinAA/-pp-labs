#include <iostream>
#include <string>
#include <fstream>

										/*класс созданный для мэйна, он нужен чтобы определить параметры игры*/

class arguments {
public:
	std::string mode;				//режим игры
	int steps;						//колчисло шагов симуляции
	std::string configs;			//конфигурационный файл соседнего игрока
	std::string matrix;				//лист сделанных ходов
	std::string* players;			//игроки
	std::string* answers_sheet;		//преобразованый лист сделанных ходов, в виде матрица 3xn

	arguments(int argc, char* argv[]);			//инициализация всех аргументов, поданных в начале.
	arguments(const arguments& argument);
	~arguments();

private:

	/*.......................................................достаём все предвыборки из аргументов командной строки.............................................*/


	std::string* arguments_get_players(std::string* players, int argc, char* argv[]);
	void arguments_get_mode(std::string* mode, int argc, char* argv[]);
	void arguments_get_configs(std::string* config, int argc, char* argv[]);
	void arguments_get_matrix(std::string* matrix, int argc, char* argv[]);
	void arguments_get_steps(int* steps, int argc, char* argv[]);
	std::string* arguments_get_answers_sheet(std::string* answers_sheet, std::string matrix);
	void arguments_chech_if_sheet_okay(std::string* answers_sheet);

	friend class player;
};

/*..............................................класс игрока, он определяет модель поведения конкретного заключённого...........................................*/

class player {

private:

	int personality;												//модель поведения
	bool next_move;													//следующий ход

public:

	player(std::string players_personality);
	~player();

	void player_get_personality(int* personality_int, std::string players_personality);
	void player_play_one_round(player* player1, player* player2, player* player3, arguments* arguments_of_the_game);
	void player_calculate_next_move(arguments arguments_of_the_game);		//просчёт следующего хода игрока


/*....................................................................функции выбора для каждого типа..............................................................*/

	void player_calculate_next_move_switcher(player* player_switcher, arguments arguments_of_the_game);
	void player_calculate_next_move_liar(player* player_liar);
	void player_calculate_next_move_naive(player* player_naive);
	void player_calculate_next_move_unpredictable(player* player_unpredictable);
	void player_calculate_next_move_smart(player* player_smart, arguments arguments_of_the_game);
	void player_calculate_next_move_side(player* player_side, arguments arguments_of_the_game);
};