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
	BEDROCK
};

struct Item
{
	ItemType type = ItemType::NONE;
	std::string name = "None";
	int maxStackSize = 64;

	bool isStackable = true;
	bool isConsumable = false;
	bool isEquippable = false;
	bool isUsable = false;
	bool isCraftable = false;
	bool isDroppable = true;
	bool isPlaceable = false;
};