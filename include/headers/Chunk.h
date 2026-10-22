#pragma once

#include <raylib.h>
#include "Tile.hpp"
#include "FastNoiseLite.h"
#include "Constants.h"
#include "TileRenderer.h"

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

	void drawDebug() const;
private:
	int cx, cy;
	Tile tiles[CHUNK_SIZE][CHUNK_SIZE];

	FastNoiseLite noise{1234};
};