#include <iostream>
#include <string>
#include <fstream>

										/*класс созданный дл€ мэйна, он нужен чтобы определить параметры игры*/

class arguments {
private:
	std::string mode;		//режим игры
	int steps;				//колчисло шагов симул€ции
	std::string configs;	//конфигурационный файл соседнего игрока
	std::string matrix;		//лист сделанных ходов
	std::string *players;	//игроки
	std::string* answers_sheet;

public:

	arguments(int argc, char* argv[]);
	~arguments();

	/*.......................................................достаЄм все предвыборки из аргументов командной строки.............................................*/


	void arguments_get_players(std::string* players, int argc, char* argv[]);
	void arguments_get_mode(std::string* mode, int argc, char* argv[]);
	void arguments_get_configs(std::string* config, int argc, char* argv[]);
	void arguments_get_matrix(std::string* matrix, int argc, char* argv[]);
	void arguments_get_steps(int* steps, int argc, char* argv[]);
	void arguments_get_answers_sheet(std::string* answers_sheet, std::string matrix);
	void arguments_chech_if_sheet_okay(std::string* answers_sheet);

	friend class player;
};

class player {

private:

	int personality;												//модель поведени€
	bool next_move;													//следующий ход

public:

	player(int number_of_the_player, arguments arguments_of_the_game);
	~player();

	void player_get_personality(int* personality_int, std::string personality_string);

	//void choose(player);											//обща€ функци€ выбора действи€

/*....................................................................функции выбора дл€ каждого типа..............................................................*/

	//void switcher(player);											//дл€ свитчера t-f-t
	//void liar(player);												//дл€ лгун f-f-f
	//void naive(player);												//дл€ трушный t-t-t
	//void unpredictable(player);										//дл€ рандом w-t-f
	//void smart(player);												//дл€ умного
};