#pragma once

#include <raylib.h>
#include "Player.h"
#include "World.h"
#include "Inventory.h"
#include "TileRegistry.h"
#include "TileRenderer.h"

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

	void drawHotbar(const TileRenderer& renderer) const;

private:
	int screenWidth;
	int screenHeight;
	const char* windowTitle;

	Player player{};
	Camera2D camera{};
	World world{};
	Texture2D tileset{};

	bool debugMode = false;
	TileType currentTileType = TileType::AIR;
	Inventory inventory{};
	TileRenderer tileRenderer;
};