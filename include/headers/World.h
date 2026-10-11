#pragma once

#include <raylib.h>
#include <unordered_map>
#include <memory>
#include <cstdint>
#include "Chunk.h"
#include "Constants.h"

class World
{
public:
	World() = default;
	~World() = default;
	
	void update(const Camera2D& camera);
	void draw(const Texture2D& tileset, bool drawDebug = false) const;

	static int PixelToChunkCoord(float pixelCoord);
	static int PixelToTileCoord(float pixelCoord);

private:
	std::unordered_map<std::uint64_t, std::unique_ptr<Chunk>> chunks;

	uint64_t getChunkKey(int chunkX, int chunkY) const
	{
		return (static_cast<uint64_t>(static_cast<uint32_t>(chunkX)) << 32) | static_cast<uint32_t>(chunkY);
	}
};