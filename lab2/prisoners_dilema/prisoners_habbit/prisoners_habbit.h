#include <iostream>
#include <string>
#include <fstream>

										/*����� ��������� ��� �����, �� ����� ����� ���������� ��������� ����*/

class arguments {
private:
	std::string mode;		//����� ����
	int steps;				//�������� ����� ���������
	std::string configs;	//���������������� ���� ��������� ������
	std::string matrix;		//���� ��������� �����
	std::string *players;	//������
	std::string* answers_sheet;

public:

	arguments(int argc, char* argv[]);
	~arguments();

	/*.......................................................������ ��� ����������� �� ���������� ��������� ������.............................................*/


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

	int personality;												//������ ���������
	bool next_move;													//��������� ���

public:

	player(int number_of_the_player, arguments arguments_of_the_game);
	~player();

	void player_get_personality(int* personality_int, std::string personality_string);

	//void choose(player);											//����� ������� ������ ��������

/*....................................................................������� ������ ��� ������� ����..............................................................*/

	//void switcher(player);											//��� �������� t-f-t
	//void liar(player);												//��� ���� f-f-f
	//void naive(player);												//��� ������� t-t-t
	//void unpredictable(player);										//��� ������ w-t-f
	//void smart(player);												//��� ������
};