#pragma once

#include <cstdint>
#include <string>

enum class ItemType :std::uint16_t
{
	NONE,
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

struct Item
{
	ItemType type = ItemType::NONE;
	std::string name = "None";
	int maxStackSize = 64;

	bool isStackable  = true;
	bool isConsumable = false;
	bool isEquippable = false;
	bool isUsable     = false;
	bool isCraftable  = false;
	bool isDroppable  = true;
	bool isPlaceable  = false;
};