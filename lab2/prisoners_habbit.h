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
	int personality;												//������ ���������
	bool next_move;													//��������� ���

public:

	player();
	player(int personality, int list_length, bool** answer_list);
	~player();

	//void choose(player);											//����� ������� ������ ��������

/*....................................................................������� ������ ��� ������� ����..............................................................*/

	//void switcher(player);											//��� �������� t-f-t
	//void liar(player);												//��� ���� f-f-f
	//void naive(player);												//��� ������� t-t-t
	//void unpredictable(player);										//��� ������ w-t-f
	//void smart(player);												//��� ������
};