#pragma once

#include <raylib.h>
#include "Player.h"

class Game 
{
public:
	Game(int width, int height, const char* title);
	~Game();

	void run();

private:
	void handleInput();
	void update();
	void draw();

private:
	int screenWidth;
	int screenHeight;
	const char* windowTitle;

	Player player{};
};