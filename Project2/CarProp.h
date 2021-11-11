#pragma once
#include <math.h>

enum class Direction {
	NORTH, EAST, EAST_W, SOUTH, WEST,WEST_E,  NOWHERE
};

enum class Color {
	RED, BLUE, YELLOW
}; 
enum class Ampel_Farbe {
	RED, YELLOW, GREEN, REDYELLOW
};
enum class Ampel_Seite {
	OBEN, RECHTS, UNTEN, LINKS
};