#pragma once // This is a preprocessor directive that tells the compiler to include this file only once
#include <qobject.h>
#include <qgridlayout.h>
#include <qframe.h>
#include "GameSpecs.h"
#include <qtimer.h>

using namespace std;

class Organism;

class City : public QGridLayout
{
	Q_OBJECT
private:
	Organism* grid[GRID_SIZE][GRID_SIZE];
	QTimer* timer;
	int humanCount = 0;
	int turn = 0;

public:
	City(QWidget* parent);
	virtual ~City();

	Organism* getOrganism( int x, int y );
	Organism* setOrganism( Organism *organism);
	void removeOrganism( int x, int y );
	void removeOrganism( Organism *organism );

	int decrementHumanCount();
	int incrementHumanCount();

	int move();
	void resetTurns();

	void _debugPrintGrid();

	// friend ostream& operator<<( ostream &output, City &city );
};

