#ifndef _Human_H
#define _Human_H

#include "Organism.h"
//#include <map>
#include "GameSpecs.h"

class Human : public Organism
{
private:
	int turnsSurvived;
	//int turnsSinceInfected;
	//bool infected;
	//bool moved;
	//bool isNull();

public:
	Human(int x, int y, City* parent); 
	virtual ~Human();

	void move();

	map<human::DIRECTION, Organism*> getNeighbours();

	bool isNull();

	Organism* recruit(human::DIRECTION);

	bool isRecruitThresholdMet();

	Organism* getNeighbour(human::DIRECTION);
	
};

#endif
