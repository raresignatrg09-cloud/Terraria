#pragma once

#include <raylib.h>
#include "Player.h"
#include "World.h"

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

	Vector2 getPlayerWorldPosition();
private:
	int screenWidth;
	int screenHeight;
	const char* windowTitle;

	Player player{};
	Camera2D camera{};
	World world{};
	Texture2D tileset{};

	bool debugMode = false;
};