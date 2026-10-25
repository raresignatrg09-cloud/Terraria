#pragma once

enum TileType
{
    AIR = -1,
    GRASS,
    STONE,
    DIRT,
    WATER,
    SAND,
    LOG,
    LEAVES,
    BEDROCK,
    GLASS,
    SNOW,
    GRASS_SNOW,
    ICE,
    CACTUS,
    GRAVEL,

    // Ores
    COAL_ORE,
    IRON_ORE,
    COPPER_ORE,
    GOLD_ORE,

    // Terrain
    CLAY,
    MOSSY_STONE,
    OBSIDIAN,

    // Other
    TORCH,
    BRICK,
    PLANKS
};

struct Tile
{
	int id = AIR;
};