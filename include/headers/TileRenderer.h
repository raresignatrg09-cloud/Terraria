
#pragma once

#include <raylib.h>
#include "Constants.h"

class TileRenderer
{
public:
    void setTexture(const Texture2D& texture)
    {
        this->texture = texture;
    }

    void draw(int textureID, Vector2 position, float size,
        Color tint = WHITE) const
    {
        if (textureID < 0 || texture.id == 0)
            return;

        Rectangle source = {
            static_cast<float>((textureID % ATLAS_COLUMNS) * TILE_SIZE),
            static_cast<float>((textureID / ATLAS_COLUMNS) * TILE_SIZE),
            static_cast<float>(TILE_SIZE),
            static_cast<float>(TILE_SIZE)
        };

        Rectangle destination = { position.x,position.y,size,size };

        DrawTexturePro(texture, source, destination, Vector2{ 0.0f, 0.0f }, 0.0f, tint);
    }

private:
    Texture2D texture{};
};
