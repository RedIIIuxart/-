#include "stdafx.h"
#include "AiFleet.h"
#include <random>
//just started


AiFleet::AiFleet() {
	this->AiShip_number = 0; 
	this->Playermap = nullptr;
	this->Aimap = nullptr;
}


AiFleet::~AiFleet() {
	this->fleet.clear();
	this->Playermap = nullptr;
	this->Aimap = nullptr;
}


void AiFleet::AddAiShip(AiShip *_a) {
	this->fleet.push_back(*_a);
	this->AiShip_number++;
}


void AiFleet::MakeSpip(int _size, int _number) {
	while (_number-- > 0) {
		AiShip init;
		init.InitAiShip(_size);
		this->AddAiShip(&init);
	}
}


bool AiFleet::SetAiFleet() {	//�.�. � ������� ������� ���� ���� � ��, �� � ������ �� ���� ����� ���������� ������������. ���� � �������, �� ��� ����� 1 �� ����� ��� � 1 ���� � 2 ����, � ���...
	if (!(this->fleet.size()))
		return 1;
	const int _size_x = this->Aimap->size();		//map size x and y
	const int _size_y = this->Aimap->at(0).size();
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrx(0, _size_x);
	std::uniform_int_distribution<> distry(0, _size_y);
	std::uniform_int_distribution<> distrh(0, 1);
	std::vector<AiShip>::iterator begin = this->fleet.begin();
	std::vector<AiShip>::iterator end = this->fleet.end();
	int max_err;
	std::vector<short int> sx, sy;
	sx.reserve(4);
	sy.reserve(4);
	unsigned short int size;
	while (begin != end) {
		max_err = 0;
		size = (*begin).GetSize();
		do
		{
			sx.push_back(distrx(gen));
			sy.push_back(distry(gen));
			if (distrh(gen)) {
				for (int i = 1; i < size; i++)
					sx.push_back(sx.at(0) + i);
			}
			else {
				for (int i = 1; i < size; i++)
					sy.push_back(sy.at(0) + i);
			}
			if (max_err++ > 100) {	//�� ��� ������ �� ����� ����� ���� �����(� ���� �� ����, ��� �����)
				(*begin).existence = false;
				break;
			}
		} while (!(this->CheckPlace(&sx, &sy)));
		if ((*begin).existence)
			MoveAiShip(&sx, &sy, &(*begin));
		begin++;
		sx.clear();
		sy.clear();
	}
	return 0;
}

//�������� ������ �� ��������� � ������. 0 - ������, 1 - ��������.
bool AiFleet::CheckPlace(std::vector<short int> *_sx, std::vector<short int> *_sy) const{
	const int size = _sx->size();
	if (Aimap->at(_sx->at(0)).at(_sy->at(0)).flag_stay || Aimap->at(_sx->at(0)).at(_sy->at(0)).count_must_not || Aimap->at(_sx->at(0)).at(_sy->at(0)).flag_danger)
		return 0;
	
	int i = 1;
	for (; i < size; i++) {
		if ( Aimap->at(_sx->at(i)).at(_sy->at(i)).count_must_not || Aimap->at(_sx->at(0)).at(_sy->at(0)).flag_danger)
			break;
	}
	if (i == size)
		return 1;
	else
		return 0;
	
}

//������� ������� � ����� �����, � ����������� ��� �����.
void AiFleet::MoveAiShip(std::vector<short int> *_sx, std::vector<short int> *_sy, AiShip *_AiShip) {
	const int size = _sx->size();
	const int _size_x = this->Aimap->size();
	const int _size_y = this->Aimap->at(0).size(); 
	for (int a = _sx->at(0) - 1; a <= _sx->at(size - 1) + 1; a++) {
		if (a < 0)	//�������� �� ����� �� ����
			continue;
		if (a = _size_x)
			break;
		for (int b = _sy->at(0) - 1; b <= _sy->at(size - 1) + 1; b++) {
			if (b < 0)
				continue;
			if (b = _size_y)
				break;
			Aimap->at(a).at(b).count_must_not++;
		}
	}
	for (int a = _sx->at(0); a <= _sx->at(size - 1); a++) {
		for (int b = _sy->at(0); b <= _sy->at(size - 1); b++) {
			Aimap->at(a).at(b).flag_stay = true;
			Aimap->at(a).at(b).sh = _AiShip;
		}
	}
}


bool AiFleet::AiTurn() {
	this->CheckAiMap();		//��������� ����� �� ����� ������
	this->AiMove();			//������� ��������� ����
	this->AiFireRand();		//��������
	return 0;
}

//����������, ������ ���� 5 �� 5, � ������� � ������ ��������.
bool AiFleet::CheckAiMap() {
	struct Matrix {
		int x;
		int y;
		int type[3][3];	//1 - ������� ������, 0 - ������ ��� �������, -1 - �� ��������
	} temp;
	const int x = this->Aimap->size();
	const int y = this->Aimap->at(0).size();
	for (int i = 0; i < x - 3; i++) {			//����� c�����
		for (int j = 0; j < y - 3; j++) {		//����� �������
			temp.x = i;							//����� ������� ���� �����
			temp.y = j;							//����� ������� ���� �����
			for (int ti = 0; ti < 3; ti++) {
				for (int tj = 0; tj < 2; tj++) {
					if (j == 0) {
						temp.type[ti][tj] = GetMapFlag(i + ti, tj);
					}
					else {
						temp.type[ti][tj] = temp.type[ti][tj + 1];
					}
				}
			}
			temp.type[0][2] = GetMapFlag(i, j + 2);
			temp.type[1][2] = GetMapFlag(i + 1, j + 2);
			temp.type[2][2] = GetMapFlag(i + 2, j + 2);
			//3x3 have matrix, now analyze; 
			int ti = 0;			//��������� ������ 2 ������� ��������� � ������� �����.
			int tj = 0;
			//������ ����� ���.

		}
	}
	return 0;
}


bool AiFleet::AiMove() {
	int size = this->fleet.size();
	for (int i = 0; i < size; i++) {
		if (this->CheckAiShip(i)) {
			std::vector<short int> x, y;
			this->GetAiShip(&x, &y, i);
			this->FindPlase(&x, &y);
			this->MoveAiShip(&x, &y, &(this->fleet.at(i)));
			return 1;
		}
	}
	return 0;
}


bool AiFleet::AiFireRand() {
	const int _size_x = this->Playermap->size();		//map size x and y
	const int _size_y = this->Playermap->at(0).size();
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrx(0, _size_x);
	std::uniform_int_distribution<> distry(0, _size_y);
	int x, y;
	int a = 0;
	while (a++<999){
		x = distrx(gen);
		y = distry(gen);
		if (!(this->Aimap->at(x).at(y).flag_life)) {
			fire(x, y);
			return 1;
		}
	}
	return 0;
}


int AiFleet::GetMapFlag(int x, int y) const {
	if (!(this->Aimap->at(x).at(y).flag_life))	//������ � ������� ��������
		return 1;
	else if (this->Aimap->at(x).at(y).flag_danger)	//������ � ������� 
		return 0;
	else
		return -1;
}


bool AiFleet::CheckAiShip(int _i) const{
	std::vector<short int> x, y;
	this->fleet.at(_i).GetXY(&x, &y);
	int size = this->fleet.at(_i).GetSize();
	for (int j = 0; j < size; j++) {
		if (this->Aimap->at(x.at(j)).at(y.at(j)).flag_danger)
			return 1;
	}
	return 0;
}


void AiFleet::GetAiShip(std::vector<short int> *_sx, std::vector<short int> *_sy, const int _i) {
	const int _size_x = this->Aimap->size();
	const int _size_y = this->Aimap->at(0).size();
	int size = this->fleet.at(_i).GetSize();

	this->fleet.at(_i).GetXY(_sx, _sy);
	for (int a = 0; a < size; a++) {
		this->Aimap->at(_sx->at(a)).at(_sy->at(a)).flag_stay = false;	//����� ������� � �� �������� �����
		this->Aimap->at(_sx->at(a)).at(_sy->at(a)).sh = nullptr;
	}

	for (int x = _sx->at(0) - 1; x <= _sx->at(size - 1) + 1; x++) {
		if (x < 0)
			continue;
		if (x = _size_x)
			break;
		for (int y = _sy->at(0) - 1; y <= _sy->at(size - 1) + 1; y++) {
			if (y < 0)
				continue;
			if (y = _size_y)
				break;
			this->Aimap->at(x).at(y).count_must_not--;		//������ ��� ������� ��������.
		}
	}
}


void AiFleet::FindPlase(std::vector<short int> *_sx, std::vector<short int> *_sy) {
	//���� ��� ����� ��� �������, ����� :  1)�������� �������� 1 �� ��� 2)������� � ��������� "�����" ������ ������.
	//��� � ������.
	std::vector<std::vector<short int>> xmas;
	std::vector<std::vector<short int>> ymas;
	const int _size_x = this->Aimap->size();
	const int _size_y = this->Aimap->at(0).size();
}


bool AiInit(AiFleet *fleet, std::vector<AiShip>::iterator begin, std::vector<AiShip>::iterator end) {
	try
	{
		while (begin != end) {
			fleet->fleet.push_back((*begin++));
		}
	}
	catch (const std::exception&)
	{
		fleet->fleet.clear();
		return true;	//error;
	}
	return false;
}


void fire(int x, int y) {
	//��, ��� ���. ��� �� ���.
}