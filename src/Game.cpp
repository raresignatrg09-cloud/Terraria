#include "headers/Game.h"

Game::Game(int width, int height, const char* title)
	: screenWidth(width), screenHeight(height), windowTitle(title)
{
	InitWindow(screenWidth, screenHeight, windowTitle);
	SetTargetFPS(60);

	player = Player({ static_cast<float>(screenWidth) / 2.0f, static_cast<float>(screenHeight) / 2.0f });
}

Game::~Game()
{
	CloseWindow();
}

void Game::run()
{
	while (!WindowShouldClose())
	{
		handleInput();
		update();
		draw();
	}
}

void Game::handleInput()
{
	if (IsKeyPressed(KEY_ESCAPE))
	{
		CloseWindow();
	}
}

void Game::update()
{
	float dt = GetFrameTime();
	player.update(dt);
}

void Game::draw()
{
	BeginDrawing();
	ClearBackground(SKYBLUE);
	player.draw();
	EndDrawing();
}
