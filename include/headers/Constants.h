#pragma once

// World height in tiles
constexpr int WORLD_HEIGHT = 200;

// Chunk and tile dimensions
constexpr int CHUNK_SIZE = 16;
constexpr int TILE_SIZE = 32;
constexpr int CHUNK_PIXEL_SIZE = CHUNK_SIZE * TILE_SIZE;
constexpr int ATLAS_COLUMNS = 8;

// Chunk coordinates (top-down, matching Raylib)
constexpr int MIN_CHUNK_Y = 0;
constexpr int MAX_CHUNK_Y = (WORLD_HEIGHT - 1) / CHUNK_SIZE; // 12

// Terrain coordinates (bottom-up)
constexpr int SURFACE_Y = 100;
constexpr int HEIGHT_VARIATION = 5;
constexpr int DIRT_DEPTH = 5;
constexpr int BEDROCK_Y = 0;