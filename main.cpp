#include "ZombieSim.h"
#include <QtWidgets/QApplication>
#include "GameSpecs.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ZombieSim zombieSimulator;
    a.setStyleSheet("background-color: #000000;"); // TODO: Use global variable BACKGROUND_COLOR for the color
    zombieSimulator.show();
    //_CrtDumpMemoryLeaks(); // TODO: Remove this line
    return a.exec();
}

//Example main.cpp
//This supposes that city->step() calls the move method of each organism in the city
//in a single pass causing each to perform all tasks that it can.

//#include <iostream>
//#include <chrono>
//#include <thread>
//#include "Organism.h"
//#include "City.h"

//int main() {
//    City *city = new City();
//    chrono:: milliseconds interval(INTERVAL);
//
//    while (city->hasDiversity()) { //while both humans and zombies exist
//        this_thread::sleep_for(interval);
//        ClearScreen();
//        city->move(); //includes all actions
//
//
//// Alternate multi-pass version with each activity happening in its own
//// pass through the array. Lends itself to prototyping and testing:
//    //   city->humansMove();
//    //   city->zombiesMoveEat();
//    //   city->humansRecruit();
//    //   city->zombiesRecruit();
//    //   city->zombiesStarve();
//    //   city->countOrganisms(Z or H goes here);
//
//        city->reset(); //resets moved flags
//        city->countOrganisms(Z or H goes here);// run once for each type
//        cout << *city; //prints city
//        cout << "GENERATION " << city->getGeneration() << endl;
//        cout << "HUMANS: " << city->countType(HUMAN_CH) << endl;
//        cout << "ZOMBIES: " << city->countType(ZOMBIE_CH) << endl;
//    }//end while
//}//end main