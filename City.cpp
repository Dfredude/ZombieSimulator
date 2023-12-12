#include "City.h"
#include <Human.h>
#include <Zombie.h>
#include "GameSpecs.h"
#include <qtime>
#include <QCoreApplication>
#include <set>

void delay()
{
	QTime dieTime = QTime::currentTime().addMSecs(GAME_SPEED/10);
	while (QTime::currentTime() < dieTime)
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

City::City(QWidget* parent = nullptr) : QGridLayout(parent)
{
	humanCount = HUMAN_STARTCOUNT;
	timer = new QTimer(this);
	// Initalize the grid
	int numOfHumans = HUMAN_STARTCOUNT;
	int numOfZombies = ZOMBIE_STARTCOUNT;
	int numOfEmpty = GRID_SIZE * GRID_SIZE - numOfHumans - numOfZombies;
	set<ORGANISM_TYPE> organisms = { HUMAN, ZOMBIE, NOTHING };
	for (int x = 0; x < GRID_SIZE; x++)
	{
		for (int y = 0; y < GRID_SIZE; y++)
		{
			// Choose random Organism type
			ORGANISM_TYPE organismType = *(next(organisms.begin(), rand() % organisms.size()));
			switch (organismType)
			{
			case HUMAN:
				setOrganism(new Human(x, y, this));
				numOfHumans--;
				break;
			case ZOMBIE:
				setOrganism(new Zombie(x, y, this));
				numOfZombies--;
				break;
			case NOTHING:
				setOrganism(new Organism(x, y, this));
				numOfEmpty--;
				break;
			}
			if (numOfHumans <= 0)
			{
				organisms.erase(HUMAN);
			}
			if (numOfZombies <= 0)
			{
				organisms.erase(ZOMBIE);
			}
			if (numOfEmpty <= 0)
			{
				organisms.erase(NOTHING);
			}
		}
	}
}

City::~City()
{
	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			if (grid[i][j] != nullptr)
			{
				delete grid[i][j];
			}
		}
	}
}

Organism* City::getOrganism(int x, int y)
{
	if (x < 0 || x >= GRID_SIZE || y < 0 || y >= GRID_SIZE)
	{
		return nullptr;
	}
	return grid[y][x];
}

Organism* City::setOrganism(Organism* organism)
{
	if (organism == nullptr)
	{
		throw runtime_error("Organism cannot be null");
	}
	int x = organism->getPosition().first, y = organism->getPosition().second;
	grid[y][x] = organism;
	this->addWidget(organism, y, x, 1, 1);
	return organism;
}

void City::removeOrganism(int x, int y)
{
	if (x < 0 || x >= GRID_SIZE || y < 0 || y >= GRID_SIZE)
	{
		throw runtime_error("Invalid coordinates");
	}
	Organism* organism = getOrganism(x, y);	
	removeOrganism(organism);
}

void City::removeOrganism(Organism* organism)
{
	if (organism != nullptr)
	{
		this->removeWidget(organism);
		delete organism;
	}
}

int City::move()
{
	if (humanCount <= 0)
	{
		qDebug() << "Zombies win!";
		QCoreApplication::quit();
		return 0;
	}
	turn++;
	resetTurns();
	// Move all the organisms
	for (int x = 0; x < GRID_SIZE; x++)
	{
		for (int y = 0; y < GRID_SIZE; y++)
		{
			Organism* organism = getOrganism(x, y);
			if (organism != nullptr && organism->isTurn())
			{
				if (dynamic_cast<Zombie*>(organism) || dynamic_cast<Human*>(organism))
				{
					// Sleep for 50ms second
					delay();
					organism->move(); // Late binding
				}
			}
		}
	}
	return 1;
}

void City::_debugPrintGrid()
{
	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			if (grid[i][j] != nullptr)
			{
				qDebug() << "Organism at (" << i << ", " << j << ")";
			}
		}
	}
}

void City::resetTurns() {
	for (int x = 0; x < GRID_SIZE; x++)
	{
		for (int y = 0; y < GRID_SIZE; y++)
		{
			Organism* organism = getOrganism(x, y);
			if (organism != nullptr)
			{
				organism->resetTurn();
			}
		}
	}
}

int City::incrementHumanCount()
{
	return this->humanCount++;
}

int City::decrementHumanCount()
{
	return this->humanCount--;
}
