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

public:

	arguments(int argc, char* argv[]);
	~arguments();

	void arguments_get_players(std::string** players, int argc, char* argv[]);
	void arguments_get_mode(std::string* mode, int argc, char* argv[]);
	void arguments_get_configs(std::string* config, int argc, char* argv[]);
	void arguments_get_matrix(std::string* matrix, int argc, char* argv[]);
	void arguments_get_steps(int* steps, int argc, char* argv[]);
};

class player {

private:

	bool** answer_list;
	int list_length;
	int personality;												//модель поведени€
	bool next_move;													//следующий ход

public:

	player();
	player(int personality, int list_length, bool** answer_list);
	~player();

	//void choose(player);											//обща€ функци€ выбора действи€

/*....................................................................функции выбора дл€ каждого типа..............................................................*/

	//void switcher(player);											//дл€ свитчера t-f-t
	//void liar(player);												//дл€ лгун f-f-f
	//void naive(player);												//дл€ трушный t-t-t
	//void unpredictable(player);										//дл€ рандом w-t-f
	//void smart(player);												//дл€ умного
};