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
	BEDROCK
};

struct Tile
{
	int id = AIR;
};