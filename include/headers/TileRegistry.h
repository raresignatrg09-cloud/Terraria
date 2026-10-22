#pragma once

#include "Tile.hpp"
#include "Item.hpp"

struct TileDefinition
{
	const char* name;
	ItemType drop;
	int dropCount;
	bool breakable;
	bool solid;
    int textureIndex;
};

inline constexpr TileDefinition TILE_DEFINITIONS[] =
{
    { "Grass",   ItemType::GRASS,   1, true,  true, 0  }, // 0
    { "Stone",   ItemType::STONE,   1, true,  true, 1  }, // 1
    { "Dirt",    ItemType::DIRT,    1, true,  true, 2  }, // 2
    { "Water",   ItemType::WATER,   1, true,  false,3  }, // 3
    { "Sand",    ItemType::SAND,    1, true,  true, 4  }, // 4
    { "Log",     ItemType::LOG,     1, true,  true, 5  }, // 5
    { "Leaves",  ItemType::LEAVES,  1, true,  true, 6  }, // 6
    { "Bedrock", ItemType::NONE,    0, false, true, 7  }  // 7
};

inline constexpr int TILE_DEFINITION_COUNT = sizeof(TILE_DEFINITIONS) / sizeof(TILE_DEFINITIONS[0]);

inline const TileDefinition* getTileDefinition(int id)
{
    if (id < 0 || id >= TILE_DEFINITION_COUNT)
        return nullptr;

    return &TILE_DEFINITIONS[id];
}

inline int getTextureIndexFromItem(ItemType type)
{
    for (const auto& def : TILE_DEFINITIONS)
    {
        if (def.drop == type)
            return def.textureIndex;
    }

    return -1;
}


inline TileType getTileFromItem(ItemType type)
{
    for (int i = 0; i < TILE_DEFINITION_COUNT; ++i)
    {
        if (TILE_DEFINITIONS[i].drop == type &&
            type != ItemType::NONE)
        {
            return static_cast<TileType>(i);
        }
    }

    return AIR;
}
