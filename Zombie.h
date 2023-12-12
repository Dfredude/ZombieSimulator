#ifndef _Zombie_H
#define _Zombie_H

#include "Organism.h"
#include "GameSpecs.h"

class Zombie : public Organism
{
	private:
	int health = 3;
	
public:
	Zombie(int x, int y, City* parent);
	virtual ~Zombie();

	void move();

	bool isNull();

	map<zombie::DIRECTION, Organism*> getNeighbours();

	Organism* getNeighbour(zombie::DIRECTION);
};

#endif
