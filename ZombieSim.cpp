#include "ZombieSim.h"
#include "City.h"
#include <qlabel.h>
#include <qgridlayout.h>
#include <Qt>
#include <iostream>
#include <Human.h>
#include "GameSpecs.h"
#include <QTimer>

using namespace std;

void printHello() {
	cout << "Hello" << endl;
}

ZombieSim::ZombieSim(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    // Create a new City with the MainWidget as the parent
    city = new City(this);

    // Add the City to the MainWidget's layout
    
    ui.MainWidget->setLayout(city);

    // Create a timer
    QTimer* timer = new QTimer(this);
    // Based on a time event(timer or thread sleep), the city will be updated and printed.
    // The city will be updated by calling the move() function on each Organism.
    // The city will be printed by calling the printGrid() function on the City.
    connect(timer,&QTimer::timeout, city, &City::move);
    //connect(timer, SIGNAL(timeout()), city, SLOT(hide));
    // Start the timer
    timer->start(GAME_SPEED);

}

ZombieSim::~ZombieSim(){
	delete city;
}
