#pragma once

#include <raylib.h>
#include <string>

#include "Tile.hpp"
#include "FastNoiseLite.h"
#include "Constants.h"
#include "TileRenderer.h"

enum class Biome
{
	PLAINS,
	MOUNTAINS,
	FROZEN,
	OCEAN,
	FOREST
};
class Chunk
{
public:
	Chunk(int chunkX, int chunkY);
	~Chunk() = default;
	void generate();
	void draw(const TileRenderer& renderer) const;

	Tile& getTile(int localX, int localY);
	const Tile& getTile(int localX, int localY) const;
	int getChunkX() const { return cx; }
	int getChunkY() const { return cy; }

	Biome getBiome(int worldX) const;
	std::string getBiomeName();
	static void setSeed(int seedValue) { seed = seedValue; }
	static int getSeed() { return seed; }

	void drawDebug() const;
private:
	int cx, cy;
	inline static int seed = 1234;
	std::string biomeName{};
	Tile tiles[CHUNK_SIZE][CHUNK_SIZE];

	FastNoiseLite terrainNoise{ seed };
	FastNoiseLite detailNoise{ seed };

	FastNoiseLite biomeNoise{ seed };
	FastNoiseLite temperatureNoise{ seed };
	FastNoiseLite mountainNoise{ seed };
};