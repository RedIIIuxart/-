#pragma once
#include <vector>
#include "stdafx.h"
//finished

class AiShip {
public:
	int gun;		//пушка
	bool existence;	//жив/мертв.
	bool intact;	//цел/нет. //раненныйй корабль двигать нельз€ (быстро можно проверить, можно его двигать или нет)
//private:			//€ бы пока не рисковал.	
	std::vector<short int> x;	
	std::vector<short int> y;
	std::vector<short int> hp;	//хп, если хп рисовать не клетке, а караблю, то корабль можно вынести в отдельный независ€щий класс. ѕлюс двигать проще его так.				
	unsigned short int size_AiShip;
//public:
	AiShip();
	virtual ~AiShip();
	virtual void check_AiShip();
	virtual void initVecVec(std::vector<short int> &_vec, unsigned short int _nSize, short int _value = -1);

	virtual void move(short int _x, short int _y, const bool horizontal = true);	//€ ей двигаю кораблик; x,y - новый минимальный x,y;  horizontal==true по горизонтали, иначе вертикали 
	virtual void move(const short int _x[], const short int _y[]);					//второй вариант, задава€ все координаты.
	virtual void move(std::vector<short int> *_x, std::vector<short int> *_y);	//как и второй вариант, задава€ все координаты, но с вектором, а не массивом. (не знал, чем вы пользуетесь)
	virtual void InitAiShip(const unsigned short int _size = 0, const short int _hp = -1, const short int _min_x = -1, const short int _min_y = -1, const bool _horizontal = true);

	virtual void GetX(std::vector<short int> *_x) const;								//€ предпочитаю переменные делать приватными и к ним так получать доступ.
	virtual void GetY(std::vector<short int> *_y) const;
	virtual void GetXY(std::vector<short int> *_x, std::vector<short int> *_y) const;
	virtual void GetHp(std::vector<short int> *_hp) const;
	virtual short int GetHp(const short int _x, const short int _y) const;
	virtual unsigned short int  GetSize() const;

	virtual void AddHp(const short int _hp, const short int _x, const short int _y);	//ћен€ть после выстрела
	virtual void SetHp(const short int _hp, const short int _x, const short int _y);	//ѕолучать
private:
	virtual void InitSize(const int _size);			//мои функции запускаемые при создании корабл€. вызывает InitSpip();
	virtual void InitHp(const int _hp);
	virtual void InitXY(int _x, int _y, const bool _horizontal);

};

//1)≈сли hp ну очень нужно в клетке, то можно брать вектор старых координат, обнул€ть хп, перемещать кораблик, брать его коры и хп, заполн€ть поле. ¬ классе флота.
//2)≈сли совсем нет на хп кораблс€, то:
//а) либо весь код надо свалить в 1 файл
//б) либо создать файл с полем, что € плохо представл€ю зачем и как пока...
//в) либо просто check перенести на ступень выше.(в проверку на уровне флота, который уже видит поле).
//P.s. а зачем полю нужно хп? ћожно просто к клетке крепить указатель на корабль и сразу к нему обращатьс€ с нее. кок то так:
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
		return -999; //любое число, что там пусто... на клетке нет кораблс€.
	else
		return this->curentAiShip.GetHp(x,y;
}
*/