#include "headers/Chunk.h"
#include "headers/TileRenderer.h"

#include <stdexcept>
#include <string>
#include <cmath>

Chunk::Chunk(int chunkX, int chunkY)
	: cx(chunkX), cy(chunkY)
{
	noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	noise.SetFrequency(0.1f);
	noise.SetFractalType(FastNoiseLite::FractalType_FBm);
	noise.SetFractalOctaves(4);

	generate();
}

void Chunk::generate()
{
	for (int x = 0; x < CHUNK_SIZE; ++x)
	{
		const int worldX = cx * CHUNK_SIZE + x;

		const float value = noise.GetNoise(
			static_cast<float>(worldX), 0.0f
		);

		const int surfaceY = SURFACE_Y +
			static_cast<int>(std::round(value * HEIGHT_VARIATION));

		for (int y = 0; y < CHUNK_SIZE; ++y)
		{
			// Drawing uses top-down tile coordinates.
			const int screenTileY = cy * CHUNK_SIZE + y;

			// Convert to bottom-up world coordinates.
			const int worldY = WORLD_HEIGHT - 1 - screenTileY;

			if (worldY < 0 || worldY >= WORLD_HEIGHT)
				tiles[x][y].id = AIR;
			else if (worldY == BEDROCK_Y)
				tiles[x][y].id = BEDROCK;
			else if (worldY > surfaceY)
				tiles[x][y].id = AIR;
			else if (worldY == surfaceY)
				tiles[x][y].id = GRASS;
			else if (worldY >= surfaceY - DIRT_DEPTH)
				tiles[x][y].id = DIRT;
			else
				tiles[x][y].id = STONE;
		}
	}
}

void Chunk::draw(const TileRenderer& renderer) const
{
	for (int x = 0; x < CHUNK_SIZE; ++x)
	{
		for (int y = 0; y < CHUNK_SIZE; ++y)
		{
			if(tiles[x][y].id==AIR)
				continue;

			Vector2 position = { static_cast<float>((cx * CHUNK_SIZE + x) * TILE_SIZE),static_cast<float>((cy * CHUNK_SIZE + y) * TILE_SIZE)};
			const int id = tiles[x][y].id;

			renderer.draw(id, position, static_cast<float>(TILE_SIZE));
		}
	}
}

Tile& Chunk::getTile(int localX, int localY)
{
	if (localX >= 0 && localX < CHUNK_SIZE && localY >= 0 && localY < CHUNK_SIZE)
	{
		return tiles[localX][localY];
	}
	else
	{
		throw std::out_of_range("Local coordinates out of range");
	}
}

const Tile& Chunk::getTile(int localX, int localY) const
{
	if (localX >= 0 && localX < CHUNK_SIZE && localY >= 0 && localY < CHUNK_SIZE)
	{
		return tiles[localX][localY];
	}
	else
	{
		throw std::out_of_range("Local coordinates out of range");
	}
}


void Chunk::drawDebug() const
{
	// Calculăm dimensiunea totală a unui chunk în pixeli (16 blocuri * 16 pixeli = 256 pixeli)
	float chunkSizePixels = static_cast<float>(CHUNK_SIZE * TILE_SIZE);

	// Poziția globală în pixeli a colțului stânga-sus al acestui chunk
	float pixelX = static_cast<float>(cx * chunkSizePixels);
	float pixelY = static_cast<float>(cy * chunkSizePixels);

	// Desenăm doar linia de contur (grosime de 1 sau 2 pixeli)
	// Folosim o culoare vizibilă (ex: ROȘU sau VERDE)
	DrawRectangleLinesEx(Rectangle{ pixelX, pixelY, chunkSizePixels, chunkSizePixels }, 1.0f, RED);

	// Opțional: Poți scrie și coordonatele chunk-ului text, direct în centrul lui pentru debug facil
	std::string coords = "(" + std::to_string(cx) + ", " + std::to_string(cy) + ")";
	DrawText(coords.c_str(), pixelX + 5, pixelY + 5, 10, YELLOW);
}
