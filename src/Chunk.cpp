#include "headers/Chunk.h"
#include "headers/TileRenderer.h"

#include <stdexcept>
#include <string>
#include <cmath>

Chunk::Chunk(int chunkX, int chunkY)
	: cx(chunkX), cy(chunkY)
{
	terrainNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	terrainNoise.SetFrequency(0.1f);
	terrainNoise.SetFractalType(FastNoiseLite::FractalType_FBm);
	terrainNoise.SetFractalOctaves(4);
	terrainNoise.SetFractalLacunarity(2.0f);
	terrainNoise.SetFractalGain(0.5f);

	detailNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	detailNoise.SetFrequency(0.04f);
	detailNoise.SetFractalType(FastNoiseLite::FractalType_FBm);
	detailNoise.SetFractalOctaves(2);

	biomeNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	biomeNoise.SetFrequency(0.003f);

	temperatureNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	temperatureNoise.SetFrequency(0.002f);

	mountainNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	mountainNoise.SetFrequency(0.015f);
	mountainNoise.SetFractalType(FastNoiseLite::FractalType_FBm);
	mountainNoise.SetFractalOctaves(4);

    moistureNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    moistureNoise.SetFrequency(0.0025f);
    moistureNoise.SetFractalType(FastNoiseLite::FractalType_FBm);
    moistureNoise.SetFractalOctaves(3);

	generate();
}

void Chunk::generate()
{
    for (int x = 0; x < CHUNK_SIZE; ++x)
    {
        const int worldX = cx * CHUNK_SIZE + x;
        const Biome biome = getBiome(worldX);

        const int surfaceY = getSurfaceHeight(worldX, biome);

        for (int y = 0; y < CHUNK_SIZE; ++y)
        {
            const int screenTileY = cy * CHUNK_SIZE + y;
            const int worldY = WORLD_HEIGHT - 1 - screenTileY;

            int block = AIR;

            if (worldY < 0 || worldY >= WORLD_HEIGHT)
            {
                tiles[x][y].id = AIR;
                continue;
            }

            if (worldY == BEDROCK_Y)
            {
                tiles[x][y].id = BEDROCK;
                continue;
            }

            if (worldY > surfaceY)
            {
                // Fill the ocean between the seabed and sea level.
                if (biome == Biome::OCEAN && worldY <= SEA_LEVEL)
                {
                    block = WATER;
                }
                else
                {
                    block = AIR;
                }
            }
            else
            {
                const int depth = surfaceY - worldY;

                if (depth == 0)
                {
                    switch (biome)
                    {
                    case Biome::PLAINS:
                    case Biome::FOREST:
                        block = GRASS;
                        break;

                    case Biome::MOUNTAINS:
                        block = surfaceY >= SNOW_LINE ? SNOW : STONE;
                        break;

                    case Biome::OCEAN:
                        block = SAND;
                        break;

                    case Biome::FROZEN:
                        block = SNOW;
                        break;
                    }
                }
                else if (biome == Biome::OCEAN && depth <= DIRT_DEPTH)
                {
                    block = SAND;
                }
                else if (biome == Biome::FROZEN && depth <= 3)
                {
                    block = GRASS_SNOW; // Replace with ice or permafrost if you add those tiles.
                }
                else if (biome == Biome::MOUNTAINS)
                {
                    block = STONE;
                }
                else if (depth <= DIRT_DEPTH)
                {
                    block = DIRT;
                }
                else
                {
                    block = STONE;
                }
            }

            tiles[x][y].id = block;
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


Biome Chunk::getBiome(int worldX) const
{
    const float x = static_cast<float>(worldX);
    const float region = biomeNoise.GetNoise(x, 0.0f);
    const float temperature = temperatureNoise.GetNoise(x, 0.0f);
    const float moisture = moistureNoise.GetNoise(x, 0.0f);

    if (region < -0.55f)
        return Biome::OCEAN;

    if (temperature < -0.4f)
        return Biome::FROZEN;

    if (region > 0.45f)
        return Biome::MOUNTAINS;

    if (moisture > 0.1f)
        return Biome::FOREST;

	return Biome::PLAINS;
}

std::string Chunk::getBiomeName()
{
    return "ba";
}

int Chunk::getSurfaceHeight(int worldX, Biome biome) const
{
    const float x = static_cast<float>(worldX);

    const float broad = terrainNoise.GetNoise(x, 0.0f);
    const float detail = detailNoise.GetNoise(x, 0.0f);

    float height = static_cast<float>(SURFACE_Y);

    switch (biome)
    {
    case Biome::PLAINS:
        height += broad * HEIGHT_VARIATION * 0.5f;
        height += detail * 1.5f;
        break;

    case Biome::FOREST:
        height += broad * HEIGHT_VARIATION;
        height += detail * 2.0f;
        break;

    case Biome::MOUNTAINS:
    {
        const float ridge = getRidgedNoise(static_cast<float>(worldX));
        const float base = broad * HEIGHT_VARIATION * 0.5f;
        const float peaks = (ridge - 0.45f) * HEIGHT_VARIATION * 5.0f;
        height += base + peaks;
        break;
    }

    case Biome::OCEAN:
        height = SEA_LEVEL - OCEAN_DEPTH + broad * 3.0f;
        break;

    case Biome::FROZEN:
        height += broad * HEIGHT_VARIATION;
        height += detail;
        break;
    }

    return static_cast<int>(std::round(height));
}

float Chunk::getRidgedNoise(float worldX) const
{
    float n = mountainNoise.GetNoise(worldX, 0.0f);
    n = 1.f - std::abs(n);
    return n * n;
}

void Chunk::drawDebug() const
{
	float chunkSizePixels = static_cast<float>(CHUNK_SIZE * TILE_SIZE);

	float pixelX = static_cast<float>(cx * chunkSizePixels);
	float pixelY = static_cast<float>(cy * chunkSizePixels);

	DrawRectangleLinesEx(Rectangle{ pixelX, pixelY, chunkSizePixels, chunkSizePixels }, 1.0f, RED);
}
