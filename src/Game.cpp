#include "headers/Game.h"

Game::Game(int width, int height, const char* title)
	: screenWidth(width), screenHeight(height), windowTitle(title)
{
	InitWindow(screenWidth, screenHeight, windowTitle);
	SetTargetFPS(60);

	player = Player({ static_cast<float>(screenWidth) / 2.0f, static_cast<float>(screenHeight) / 2.0f });

	camera.rotation = 0.0f;
	camera.zoom = 1.0f;
	camera.offset = Vector2{ static_cast<float>(screenWidth) / 2.0f, static_cast<float>(screenHeight) / 2.0f };

	tileset = LoadTexture(RESOURCES_PATH"textures/texture_atlas.png");
}

Game::~Game()
{
	UnloadTexture(tileset);
	CloseWindow();
}

void Game::run()
{
	camera.target = player.getPosition();
	world.update(camera);

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
	if(IsKeyPressed(KEY_KP_ADD))
	{
		camera.zoom += 0.1f;
	}
	if(IsKeyPressed(KEY_KP_SUBTRACT))
	{
		camera.zoom -= 0.1f;
	}
	if (IsKeyPressed(KEY_F1))
	{
		debugMode = !debugMode;
	}
}

void Game::update()
{
	float dt = GetFrameTime();
	player.update(dt);

	camera.target = player.getPosition();
	world.update(camera);
}

void Game::draw()
{
	BeginDrawing();
	ClearBackground(SKYBLUE);

	BeginMode2D(camera);
	// Randăm blocurile din lume
		world.draw(tileset, debugMode);
		
		player.draw(debugMode);
	EndMode2D();
	
	if(debugMode)
	{
		DrawFPS(10, 10);

		Vector2 tilePosition = player.getTilePosition();
		DrawText(TextFormat("x: %.0f, y: %.0f", tilePosition.x, tilePosition.y), 10, 30, 20, WHITE);
	}

	EndDrawing();
}