#ifndef _GAMESPECS_H
#define _GAMESPECS_H
#include <string>
#include <sstream>
#include <iomanip>

template<typename T>
std::string int_to_hex(T i) {
	std::stringstream stream;
	stream << std::hex << i;
	return stream.str();
}


const int GRID_SIZE = 20; // size of the square grid
const int HUMAN_STARTCOUNT = 100; // inital Humans
const int ZOMBIE_STARTCOUNT = 5; //initial Zombie count
const int ZOMBIE_BREED = 8; // steps until an Zombie breeds
const int ZOMBIE_STARVE = 3; // steps until a Zombie starves and converts back
const char HUMAN_CH = 111;//72 "H"// ascii for Human
const char SPACE_CH = 45; // "-" ascii dash for empty elements
const char ZOMBIE_CH = 90;//90 "Z"// ascii for zombie
const double PAUSE_SECONDS = .09; // pause between steps
const int ITERATIONS = 1000; // max number of steps
const int BREED_COLOR = 0xFF0000; // red
const int GAME_SPEED = 10; // milliseconds between turn

enum ORGANISM_TYPE { HUMAN, ZOMBIE, NOTHING };

namespace human {
	//const string COLOR = "#40E0D0"; // turquoise
	//const string SYMBOL = "H";
	enum DIRECTION { UP, DOWN, LEFT, RIGHT, NUM_DIRECTIONS };
	const int BREED_THRESHOLD = 3; // steps until an Human breeds
}

namespace zombie {
	//const string COLOR = "#FFFF00"; // bright yellow
	//const string SYMBOL = "Z";
	enum DIRECTION { UP, DOWN, LEFT, RIGHT, UPRIGHT, UPLEFT, DOWNRIGHT, DOWNLEFT, NUM_DIRECTIONS };
	const int BREED_THRESHOLD = 8; // steps until an Zombie breeds
}


//Colors
//0  = black				//9  = bright blue
//1  = blue					//10 = bright green
//2  = green				//11 = bright turquoise
//3  = turquise				//12 = bright red
//4  = red					//13 = bright pink
//5  = pink					//14 = bright yellow
//6  = yellow				//15 = bright white
//7  = white regular		//16+ = solid blocks
//8  = white pale

//const string HUMAN_COLOR = "#40E0D0"; // turquoise
//
//const string ZOMBIE_COLOR = "#FFFF00"; // bright yellow

#endif