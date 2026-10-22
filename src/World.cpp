#include "headers/World.h"
#include <cmath>

int World::PixelToChunkCoord(float pixelCoord)
{
	constexpr float CHUNK_PIXEL_SIZE = static_cast<float>(CHUNK_SIZE * TILE_SIZE);
	return static_cast<int>(std::floor(pixelCoord / CHUNK_PIXEL_SIZE));
}

int World::PixelToTileCoord(float pixelCoord)
{
	return static_cast<int>(std::floor(pixelCoord / TILE_SIZE));
}

int World::PixelToTileCoord(Vector2 pixelCoord)
{
	return static_cast<int>(std::floor(pixelCoord.x / TILE_SIZE));
}

Tile* World::getTileAt(float tileX, float tileY)
{
	int chunkX = static_cast<int>(std::floor(static_cast<float>(tileX) / CHUNK_SIZE));
	int chunkY = static_cast<int>(std::floor(static_cast<float>(tileY) / CHUNK_SIZE));

	uint64_t key = getChunkKey(chunkX, chunkY);

	auto it = chunks.find(key);
	if (it == chunks.end())
	{
		return nullptr;
	}

	int localTileX = static_cast<int>(tileX) - chunkX * CHUNK_SIZE;
	int localTileY = static_cast<int>(tileY) - chunkY * CHUNK_SIZE;

	return &it->second->getTile(localTileX, localTileY);
}

void World::update(const Camera2D& camera)
{
	Vector2 topLeft = GetScreenToWorld2D({ 0,0 }, camera);
	Vector2 bottomRight = GetScreenToWorld2D({ static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) }, camera);

	int startChunkX = PixelToChunkCoord(topLeft.x) - 1;
	int endChunkX = PixelToChunkCoord(bottomRight.x) + 1;
	int startChunkY = PixelToChunkCoord(topLeft.y) - 1;
	int endChunkY = PixelToChunkCoord(bottomRight.y) + 1;

	for (int cx = startChunkX; cx <= endChunkX; ++cx)
	{
		for (int cy = startChunkY; cy <= endChunkY; ++cy)
		{
			if (cy < MIN_CHUNK_Y || cy > MAX_CHUNK_Y)
				continue;

			uint64_t key = getChunkKey(cx, cy);
			if (chunks.find(key) == chunks.end())
			{
				chunks[key] = std::make_unique<Chunk>(cx, cy);
			}
		}
	}

	// Remove chunks that are no longer in view
}

void World::draw(const TileRenderer& renderer, bool drawDebug) const
{
	for(const auto& pair: chunks)
	{
		pair.second->draw(renderer);

#if defined(_DEBUG) || !defined(NDEBUG)
		if (drawDebug)
		{
			pair.second->drawDebug();
		}
#endif
	}
}