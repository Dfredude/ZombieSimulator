#ifndef _Organism_H
#define _Organism_H

#include <QFrame>
#include <QLabel>
#include <map>

using namespace std;

class City;

class Organism : public QFrame
{
	Q_OBJECT
protected:
	int x;
	int y;
	int width;
	int height;
	bool moved;
	QLabel symbol;
	City *city;
	int turnsSurvived = 0;
	bool tookTurn = false;

public:
	Organism(int x, int y, City* parent);
	// Organism( City *city, int width, int height );
	virtual ~Organism();

	virtual void move();
	City* getCity();
	pair<int, int> getPosition();
	virtual bool isNull();
	pair<int, int> setPosition(int x, int y);
	bool isTurn();
	void resetTurn();
	//virtual void spawn() = 0;
	//virtual int getSpecies() = 0; //this could also be coded concrete here
	//virtual void getPosition() = 0;

	/*void setPosition( int x, int y );
	void endTurn();
	bool isTurn();*/
};

#endif
