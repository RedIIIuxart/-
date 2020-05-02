#include "stdafx.h"
#include "AiShip.h"

//finished

AiShip::AiShip() 
{
	gun = 0;
	existence = true;
	intact = true;
	x.push_back(-1);
	y.push_back(-1);
	hp.push_back(-1);
	size_AiShip = 1;
}


AiShip::~AiShip() {
	this->x.clear();
	this->y.clear();
	this->hp.clear();
}

//либо оставить, либо переписать, выкинув hp в корабле, на уровне выше.
void AiShip::check_AiShip()
{
	int f = 0;
	unsigned int n = size_AiShip;
	for (int i = 0; i < n; i++)
	{
		if (this->hp.at(i)<1)
			f++;
	}
	if (n == f) { existence = false; }
}


void AiShip::initVecVec(std::vector<short int> &_vec, unsigned short int _nSize, short int _value) {
	_vec.resize(_nSize, _value);
}

//min x and y
void AiShip::move(short int _x, short int _y, const bool _horizontal) {
	unsigned short int i = this->size_AiShip;
	while (i-- > 0) {
		this->x.at(i) = _x;
		this->y.at(i) = _y;
		_horizontal ? _x++ : _y++;
	}
}


void AiShip::move(const short int _x[], const short int _y[]) {
	unsigned short int i = this->size_AiShip;
	while (i-- > 0) {
		this->x.at(i) = _x[i];
		this->y.at(i) = _y[i];
	}
}


void AiShip::move(std::vector<short int> *_x, std::vector<short int> *_y) {
	unsigned short int i = this->size_AiShip;
	while (i-- > 0) {
		this->x.at(i) = _x->at(i);
		this->y.at(i) = _y->at(i);
	}
}


void AiShip::InitAiShip(const unsigned short int _size, const short int _hp, const short int _min_x, const short int _min_y, const bool _horizontal) {
	this->gun = 0;
	this->existence = true;
	this->intact = true;
	this->InitSize(_size);
	this->InitHp(_hp);
	this->InitXY(_min_x, _min_y, _horizontal);
}


void AiShip::GetX(std::vector<short int> *_x) const {
	_x->clear();
	for (int i = 0; i < this->size_AiShip; i++) {
		_x->push_back(this->x.at(i));
	}
}


void AiShip::GetY(std::vector<short int> *_y) const {
	_y->clear();
	for (int i = 0; i < this->size_AiShip; i++) {
		_y->push_back(this->y.at(i));
	}
}


void AiShip::GetXY(std::vector<short int> *_x, std::vector<short int> *_y) const {
	this->GetX(_x);
	this->GetY(_y);
}


void AiShip::GetHp(std::vector<short int> *_hp) const {
	_hp->clear();
	for (int i = 0; i < this->size_AiShip; i++) {
		_hp->push_back(this->hp.at(i));
	}
}


short int AiShip::GetHp(const short int _x, const short int _y) const {
	for (int i = 0; i < this->size_AiShip; i++) {
		if (_x == this->x.at(i) && _y == this->y.at(i))
			return this->hp.at(i);
	}
	return -999;		//если корабль не имеет такую координату. 
}


unsigned short int AiShip::GetSize() const {
	return size_AiShip;
}

void AiShip::AddHp(const short int _hp, const short int _x, const short int _y) {
	for (int i = 0; i < this->size_AiShip; i++) {
		if (_x == this->x.at(i) && _y == this->y.at(i)) {
			this->hp.at(i) += _hp;
			return;
		}
	}
}


void AiShip::SetHp(const short int _hp, const short int _x, const short int _y) {
	for (int i = 0; i < this->size_AiShip; i++) {
		if (_x == this->x.at(i) && _y == this->y.at(i)) {
			this->hp.at(i) = _hp;
			return;
		}
	}
}


void AiShip::InitSize(const int _size) {
	this->size_AiShip = _size;
	this->x.resize(_size);
	this->y.resize(_size);
	this->hp.resize(_size);
}


void AiShip::InitHp(const int _hp) {
	for (int i = 0; i < this->size_AiShip; i++) {
		this->hp.at(i) = _hp;
	}
}


void AiShip::InitXY(int _x, int _y, const bool _horizontal) {
	for (int i = 0; i < this->size_AiShip; i++) {
		this->x.at(i) = _x;
		this->y.at(i) = _y;
		if (_x < 0)
			continue;
		else
			_horizontal ? _x++ : _y++;
	}
}