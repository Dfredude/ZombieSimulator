#include "Zombie.h"
#include "City.h"
#include "GameSpecs.h"
#include "Human.h"

Zombie::Zombie(int x, int y, City* parent = nullptr) : Organism(x, y, parent)
{
	this->symbol.setText("Z");
	// TODO: Use global variable ZOMBIE_COLOR for the color
	this->symbol.setStyleSheet("color: #FFFF00;");
}

Zombie::~Zombie()
{
	
}

map<zombie::DIRECTION, Organism*> Zombie::getNeighbours() {
	map<zombie::DIRECTION, Organism*> neighbors;
	pair<int, int> position = getPosition();
	int x = position.first, y = position.second;
	// Up
	Organism* neighbor = city->getOrganism(x, y - 1);
	if (neighbor != nullptr && !dynamic_cast<Zombie*>(neighbor))
	{
		neighbors[zombie::UP] = neighbor;
	}
	// Down
	neighbor = city->getOrganism(x, y + 1);
	if (neighbor != nullptr && !dynamic_cast<Zombie*>(neighbor))
	{
		neighbors[zombie::DOWN] = neighbor;
	}
	// Left
	neighbor = city->getOrganism(x - 1, y);
	if (neighbor != nullptr && !dynamic_cast<Zombie*>(neighbor))
	{
		neighbors[zombie::LEFT] = neighbor;
	}
	// Right
	neighbor = city->getOrganism(x + 1, y);
	if (neighbor != nullptr && !dynamic_cast<Zombie*>(neighbor))
	{
		neighbors[zombie::RIGHT] = neighbor;
	}
	// UpLeft
	neighbor = city->getOrganism(x - 1, y - 1);
	if (neighbor != nullptr && !dynamic_cast<Zombie*>(neighbor))
	{
		neighbors[zombie::UPLEFT] = neighbor;
	}
	// UpRight
	neighbor = city->getOrganism(x + 1, y - 1);
	if (neighbor != nullptr && !dynamic_cast<Zombie*>(neighbor))
	{
		neighbors[zombie::UPRIGHT] = neighbor;
	}
	// DownLeft
	neighbor = city->getOrganism(x - 1, y + 1);
	if (neighbor != nullptr && !dynamic_cast<Zombie*>(neighbor))
	{
		neighbors[zombie::DOWNLEFT] = neighbor;
	}
	// DownRight
	neighbor = city->getOrganism(x + 1, y + 1);
	if (neighbor != nullptr && !dynamic_cast<Zombie*>(neighbor))
	{
		neighbors[zombie::DOWNRIGHT] = neighbor;
	}
	return neighbors;
}

Organism* Zombie::getNeighbour(zombie::DIRECTION direction)
{
	switch (direction)
	{
	case zombie::UP:
		return city->getOrganism(x, y - 1);
		break;
	case zombie::UPLEFT:
		return city->getOrganism(x - 1, y - 1);
		break;
	case zombie::UPRIGHT:
		return city->getOrganism(x + 1, y - 1);
		break;
	case zombie::DOWN:
		return city->getOrganism(x, y + 1);
		break;
	case zombie::DOWNLEFT:
		return city->getOrganism(x - 1, y + 1);
		break;
	case zombie::DOWNRIGHT:
		return city->getOrganism(x + 1, y + 1);
		break;
	case zombie::LEFT:
		return city->getOrganism(x - 1, y);
		break;
	case zombie::RIGHT:
		return city->getOrganism(x + 1, y);
		break;
	default:
		return nullptr;
		break;
	}
}

void Zombie::move()
{
	turnsSurvived++;
	tookTurn = true;
	health--;
	map<zombie::DIRECTION, Organism*> neighbors = getNeighbours();
	if (neighbors.size() < 1)
	{
		return;
	}
	// Check if there is a human in the neighbors - If so, minus one from the human count
	for (auto it = neighbors.begin(); it != neighbors.end(); it++)
	{
		if (dynamic_cast<Human*>(it->second))
		{
			city->decrementHumanCount();
			health = 3;
			pair<int, int> human_position = it->second->getPosition();
			if (turnsSurvived >= zombie::BREED_THRESHOLD)
			{
				// Turn the human into a zombie
				city->removeOrganism(it->second);
				city->setOrganism(new Zombie(human_position.first, human_position.second, city));
				turnsSurvived = 0;
				return;
			}
			// Eat the human
			pair<int, int> old_position = getPosition();
			this->setPosition(human_position.first, human_position.second);
			city->removeOrganism(it->second);
			city->setOrganism(this);
			city->setOrganism(new Organism(old_position.first, old_position.second, city));
			return;
		}
	}
	
	if (health <= 0)
	{
		// Turn into a human - plus one to the human count
		city->incrementHumanCount();
		pair<int, int> position = getPosition();
		city->removeWidget(this);
		city->setOrganism(new Human(position.first, position.second, city));
		deleteLater();
		return;
	}
	int randomly_chosen_index = rand() % neighbors.size();
	auto it = neighbors.begin();
	for (int i = 0; i < randomly_chosen_index; i++)
	{
		it++;
	}
	zombie::DIRECTION direction = it->first;
	pair<int, int> old_position = getPosition();
	switch (direction)
	{
		case zombie::LEFT:
			city->removeOrganism(getNeighbour(zombie::LEFT));
			this->setPosition(x - 1, y);
			city->setOrganism(this);
			break;
		case zombie::RIGHT:
			city->removeOrganism(getNeighbour(zombie::RIGHT));
			this->setPosition(x + 1, y);
			city->setOrganism(this);
			break;
		case zombie::UP:
			city->removeOrganism(getNeighbour(zombie::UP));
			this->setPosition(x, y - 1);
			city->setOrganism(this);
			break;
		case zombie::UPLEFT:
			city->removeOrganism(getNeighbour(zombie::UPLEFT));
			this->setPosition(x - 1, y - 1);
			city->setOrganism(this);
			break;
		case zombie::UPRIGHT:
			city->removeOrganism(getNeighbour(zombie::UPRIGHT));
			this->setPosition(x + 1, y - 1);
			city->setOrganism(this);
			break;
		case zombie::DOWN:
			city->removeOrganism(getNeighbour(zombie::DOWN));
			this->setPosition(x, y + 1);
			city->setOrganism(this);
			break;
		case zombie::DOWNLEFT:
			city->removeOrganism(getNeighbour(zombie::DOWNLEFT));
			this->setPosition(x - 1, y + 1);
			city->setOrganism(this);
			break;
		case zombie::DOWNRIGHT:
			city->removeOrganism(getNeighbour(zombie::DOWNRIGHT));
			this->setPosition(x + 1, y + 1);
			city->setOrganism(this);
			break;
		default:
			break;
	}
	city->setOrganism(new Organism(old_position.first, old_position.second, city));
}

bool Zombie::isNull()
{
	return false;
}
