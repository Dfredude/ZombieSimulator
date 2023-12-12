#include "Human.h"
#include "City.h"
#include <map>
#include "GameSpecs.h"

Human::Human(int x, int y, City* parent = nullptr) : Organism(x, y, parent)
{
	this->symbol.setText("H");
	this->turnsSurvived = 0;
	// TODO: Use global variable HUMAN_COLOR
	this->symbol.setStyleSheet("color: #40E0D0");
}

Human::~Human()
{
}

void Human::move()
{
	turnsSurvived++;
	tookTurn = true;
	map<human::DIRECTION, Organism*> neighbors = getNeighbours();
	if (neighbors.size() < 1)
	{
		return;
	}
	int randomly_chosen_index = rand() % neighbors.size();
	auto it = neighbors.begin();
	for (int i = 0; i < randomly_chosen_index; i++)
	{ 
		it++;
	}
	human::DIRECTION direction = it->first;
	if (isRecruitThresholdMet())
	{
		recruit(direction);
		return;
	}

	pair<int, int> old_position = getPosition();
	switch (direction)
	{
		case human::LEFT:
			city->removeOrganism(getNeighbour(human::LEFT));
			this->setPosition(x - 1, y);
			city->setOrganism(this);
			break;
		case human::UP:
			city->removeOrganism(getNeighbour(human::UP));
			this->setPosition(x, y - 1);
			city->setOrganism(this);
			break;
		case human::RIGHT:
			city->removeOrganism(getNeighbour(human::RIGHT));
			this->setPosition(x + 1, y);
			city->setOrganism(this);
			break;
		case human::DOWN:
			city->removeOrganism(getNeighbour(human::DOWN));
			this->setPosition(x, y + 1);
			city->setOrganism(this);
			break;
	}
	city->setOrganism(new Organism(old_position.first, old_position.second, getCity()));
}

map<human::DIRECTION, Organism*>  Human::getNeighbours()
{
	map<human::DIRECTION, Organism*> neighbors;
	pair<int, int> position = getPosition();
	int x = position.first, y = position.second;
	Organism* neighbor = getNeighbour(human::UP);
	if (y > 0 && neighbor->isNull())
	{
		neighbors[human::UP] = neighbor;
	}
	neighbor = getNeighbour(human::DOWN);
	if (y < GRID_SIZE - 1 && neighbor->isNull())
	{
		neighbors[human::DOWN] = neighbor;
	}
	neighbor = getNeighbour(human::LEFT);
	if (x > 0 && neighbor->isNull())
	{
		neighbors[human::LEFT] = neighbor;
	}
	neighbor = getNeighbour(human::RIGHT);
	if (x < GRID_SIZE - 1 && neighbor->isNull() )
	{
		neighbors[human::RIGHT] = city->getOrganism(x + 1, y);
	}
	return neighbors;
}

bool Human::isNull()
{
	return false;
}

Organism* Human::recruit(human::DIRECTION direction)
{
	city->incrementHumanCount();
	Organism* neighbor = getNeighbour(direction);
	pair<int, int> position = neighbor->getPosition();
	city->removeOrganism(neighbor);
	Organism* o = city->setOrganism(new Human(position.first, position.second, city));
	/*string color = int_to_hex(BREED_COLOR);
	QString style = QString();
	o->setStyleSheet(style);*/
	return o;
}

bool Human::isRecruitThresholdMet()
{
	if (turnsSurvived >= human::BREED_THRESHOLD)
	{
		turnsSurvived = 0;
		return true;
	} else return false;
}

Organism* Human::getNeighbour(human::DIRECTION direction)
{
	switch (direction)
	{
		case human::LEFT:
			return city->getOrganism(x - 1, y);
			break;
		case human::UP:
			return city->getOrganism(x, y - 1);
			break;
		case human::RIGHT:
			return city->getOrganism(x + 1, y);
			break;
		case human::DOWN:
			return city->getOrganism(x, y + 1);
			break;
		default:
			return nullptr;
			break;
	}
}
