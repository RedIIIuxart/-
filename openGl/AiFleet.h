#pragma once
#include <vector>
#include "AiShip.h"
#include "Square.h"
//just started

class AiFleet {
public:
	std::vector<std::vector<Square>> *Playermap;		//указатель на поле игрока
	std::vector<std::vector<Square>> *Aimap;			//указатель на поле компа
	std::vector<AiShip> fleet;
	int AiShip_number;

	AiFleet();
	~AiFleet();
	void AddAiShip(AiShip *_a);
	void MakeSpip(int _size, int _number = 1);
	bool SetAiFleet();
	bool CheckPlace(std::vector<short int> *_sx, std::vector<short int> *_sy) const;
	void MoveAiShip(std::vector<short int> *_sx, std::vector<short int> *_sy, AiShip *_AiShip = nullptr);
	bool AiTurn();
	bool CheckAiMap();	//переделать
	bool AiMove();	
	bool AiFireRand();
private:
	int GetMapFlag(int x, int y) const;
	bool CheckAiShip(int i) const;
	void GetAiShip(std::vector<short int> *_sx, std::vector<short int> *_sy, const int i);
	void FindPlase(std::vector<short int> *_sx, std::vector<short int> *_sy);		//переделать
};


bool AiInit(AiFleet *fleet, std::vector<AiShip>::iterator begin, std::vector<AiShip>::iterator end);
void fire(int x, int y);