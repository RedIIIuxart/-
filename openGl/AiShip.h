#pragma once
#include <vector>
#include "stdafx.h"
//finished

class AiShip {
public:
	int gun;		//�����
	bool existence;	//���/�����.
	bool intact;	//���/���. //��������� ������� ������� ������ (������ ����� ���������, ����� ��� ������� ��� ���)
//private:			//� �� ���� �� ��������.	
	std::vector<short int> x;	
	std::vector<short int> y;
	std::vector<short int> hp;	//��, ���� �� �������� �� ������, � �������, �� ������� ����� ������� � ��������� ����������� �����. ���� ������� ����� ��� ���.				
	unsigned short int size_AiShip;
//public:
	AiShip();
	virtual ~AiShip();
	virtual void check_AiShip();
	virtual void initVecVec(std::vector<short int> &_vec, unsigned short int _nSize, short int _value = -1);

	virtual void move(short int _x, short int _y, const bool horizontal = true);	//� �� ������ ��������; x,y - ����� ����������� x,y;  horizontal==true �� �����������, ����� ��������� 
	virtual void move(const short int _x[], const short int _y[]);					//������ �������, ������� ��� ����������.
	virtual void move(std::vector<short int> *_x, std::vector<short int> *_y);	//��� � ������ �������, ������� ��� ����������, �� � ��������, � �� ��������. (�� ����, ��� �� �����������)
	virtual void InitAiShip(const unsigned short int _size = 0, const short int _hp = -1, const short int _min_x = -1, const short int _min_y = -1, const bool _horizontal = true);

	virtual void GetX(std::vector<short int> *_x) const;								//� ����������� ���������� ������ ���������� � � ��� ��� �������� ������.
	virtual void GetY(std::vector<short int> *_y) const;
	virtual void GetXY(std::vector<short int> *_x, std::vector<short int> *_y) const;
	virtual void GetHp(std::vector<short int> *_hp) const;
	virtual short int GetHp(const short int _x, const short int _y) const;
	virtual unsigned short int  GetSize() const;

	virtual void AddHp(const short int _hp, const short int _x, const short int _y);	//������ ����� ��������
	virtual void SetHp(const short int _hp, const short int _x, const short int _y);	//��������
private:
	virtual void InitSize(const int _size);			//��� ������� ����������� ��� �������� �������. �������� InitSpip();
	virtual void InitHp(const int _hp);
	virtual void InitXY(int _x, int _y, const bool _horizontal);

};

//1)���� hp �� ����� ����� � ������, �� ����� ����� ������ ������ ���������, �������� ��, ���������� ��������, ����� ��� ���� � ��, ��������� ����. � ������ �����.
//2)���� ������ ��� �� �� ��������, ��:
//�) ���� ���� ��� ���� ������� � 1 ����
//�) ���� ������� ���� � �����, ��� � ����� ����������� ����� � ��� ����...
//�) ���� ������ check ��������� �� ������� ����.(� �������� �� ������ �����, ������� ��� ����� ����).
//P.s. � ����� ���� ����� ��? ����� ������ � ������ ������� ��������� �� ������� � ����� � ���� ���������� � ���. ��� �� ���:
/*
class Square
{
public:
	Points pts[4]; // square structure
	bool flag_stay, flag_life;
	AiShip *curentAiShip;

	int Gethp(int x, int y);
}

short int Square::Gethp(int x, int y){
	if (curentAiShip==nullptr)
		return -999; //����� �����, ��� ��� �����... �� ������ ��� ��������.
	else
		return this->curentAiShip.GetHp(x,y;
}
*/