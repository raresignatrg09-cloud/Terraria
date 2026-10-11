#include <raylib.h>
#include "headers/Game.h"

int main() {
	// Initialization
	const int screenWidth = 1200;
	const int screenHeight = 800;

	Game game(screenWidth, screenHeight, "Terraria");
	game.run();
}