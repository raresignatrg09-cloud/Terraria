#include "headers/Game.h"
#include "headers/TileRegistry.h"

Game::Game(int width, int height, const char* title)
	: screenWidth(width), screenHeight(height), windowTitle(title)
{
	InitWindow(screenWidth, screenHeight, windowTitle);
	SetTargetFPS(60);

	player = Player({ static_cast<float>(screenWidth) / 2.0f, static_cast<float>(screenHeight) / 2.0f });

	camera.rotation = 0.0f;
	camera.zoom = 1.0f;
	camera.offset = Vector2{ static_cast<float>(screenWidth) / 2.0f, static_cast<float>(screenHeight) / 2.0f };

	srand(time(NULL)); 
	Chunk::setSeed(std::rand() % 1000);

	tileset = LoadTexture(RESOURCES_PATH"textures/texture_atlas.png");
	tileRenderer.setTexture(tileset);
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
	if (IsKeyPressed(KEY_KP_ADD) && camera.zoom <= 2.0f)
	{
		camera.zoom += 0.1f;
	}
	if (IsKeyPressed(KEY_KP_SUBTRACT) && camera.zoom >= 0.5f)
	{
		camera.zoom -= 0.1f;
	}
	TraceLog(LOG_INFO, TextFormat("zoom: %.2f", camera.zoom));
	if (IsKeyPressed(KEY_F1))
	{
		debugMode = !debugMode;
	}
	if (IsKeyPressed(KEY_ONE))
	{
		inventory.selectSlot(0);
	}
	if(IsKeyPressed(KEY_TWO))
	{
		inventory.selectSlot(1);
	}
	if (IsKeyPressed(KEY_THREE))
	{
		inventory.selectSlot(2);
	}
	if (IsKeyPressed(KEY_FOUR))
	{
		inventory.selectSlot(3);
	}
	if (IsKeyPressed(KEY_FIVE))
	{
		inventory.selectSlot(4);
	}
	if (IsKeyPressed(KEY_SIX))
	{
		inventory.selectSlot(5);
	}
	if (IsKeyPressed(KEY_SEVEN))
	{
		inventory.selectSlot(6);
	}
	if (IsKeyPressed(KEY_EIGHT))
	{
		inventory.selectSlot(7);
	}
	if (IsKeyPressed(KEY_NINE))
	{
		inventory.selectSlot(8);
	}

	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

		const int tileX = static_cast<int>(std::floor(mouseWorldPos.x / TILE_SIZE));
		const int tileY = static_cast<int>(std::floor(mouseWorldPos.y / TILE_SIZE));

		Tile* tile = world.getTileAt(
			static_cast<float>(tileX),
			static_cast<float>(tileY)
		);

		if (tile != nullptr)
		{
			const TileDefinition* def = getTileDefinition(tile->id);

			if (def != nullptr &&
				def->breakable &&
				def->drop != ItemType::NONE)
			{
				Item item;
				item.type = def->drop;

				if (inventory.addItem(item, def->dropCount))
				{
					tile->id = AIR;
				}
			}
		}
	}

	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{
		Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

		const int tileX = static_cast<int>(std::floor(mouseWorldPos.x / TILE_SIZE));
		const int tileY = static_cast<int>(std::floor(mouseWorldPos.y / TILE_SIZE));

		Tile* tile = world.getTileAt(
			static_cast<float>(tileX),
			static_cast<float>(tileY)
		);

		if (tile != nullptr && tile->id == AIR)
		{
			int selectedIndex = inventory.getSelectedSlotIndex();
			const InventorySlot& slot = inventory.getSlot(selectedIndex);

			if (!slot.isEmpty())
			{
				TileType tileType = getTileFromItem(slot.item.type);

				if (tileType != AIR && inventory.removeItem(slot.item, 1))
				{
					tile->id = tileType;
				}
			}
		}
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
		world.draw(tileRenderer, debugMode);
		player.draw(debugMode);
	EndMode2D();
	
	if(debugMode)
	{
		DrawFPS(10, 10);

		Vector2 tilePosition = player.getTilePosition();
		DrawText(TextFormat("x: %.0f, y: %.0f", tilePosition.x, tilePosition.y), 10, 30, 20, WHITE);
		DrawText(TextFormat("seed: %d", Chunk::getSeed()), 10, 50, 20, WHITE);
	}

	drawHotbar(tileRenderer);

	EndDrawing();
}

void Game::drawHotbar(const TileRenderer& renderer) const
{
	constexpr int SLOT_SIZE = 50;
	constexpr int SLOT_GAP = 4;
	constexpr int TOTAL_WIDTH = 9 * SLOT_SIZE + 8 * SLOT_GAP;

	int startX = (GetScreenWidth() - TOTAL_WIDTH) / 2;
	int y = GetScreenHeight() - SLOT_SIZE - 20;

	for (int i = 0; i < Inventory::MAX_SLOTS; ++i)
	{
		int x = startX + i * (SLOT_SIZE + SLOT_GAP);

		Color color = i == inventory.getSelectedSlotIndex() ? YELLOW : DARKGRAY;

		DrawRectangle(x, y, SLOT_SIZE, SLOT_SIZE, color);
		DrawRectangleLines(x, y, SLOT_SIZE, SLOT_SIZE, BLACK);

		const InventorySlot& slot = inventory.getSlot(i);

		if (!slot.isEmpty())
		{
			int textureID = getTextureIndexFromItem(slot.item.type);
			renderer.draw(textureID, { static_cast<float>(x + 9),
				static_cast<float>(y + 5) }, TILE_SIZE);

			DrawText(TextFormat("%d", slot.count), x + 28, y + 28, 16, WHITE);
		}
	}
}
