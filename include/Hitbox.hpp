#pragma once

#include <raylib.h>

class Hitbox
{
public:
    void setSize(Vector2 spriteSize, float scale)
    {
        hitboxSize = {
            spriteSize.x * scale,
            spriteSize.y * scale
        };
    }

    void setPosition(Vector2 position, Vector2 spriteSize)
    {
        hitbox.x = position.x + (spriteSize.x - hitboxSize.x) / 2.0f;
        hitbox.y = position.y + (spriteSize.y - hitboxSize.y) / 2.0f;
        hitbox.width = hitboxSize.x;
        hitbox.height = hitboxSize.y;
    }

    Rectangle getHitbox() const
    {
        return hitbox;
    }

    void draw() const
    {
        DrawRectangleLinesEx(hitbox, 2.0f, RED);
    }

private:
    Vector2 hitboxSize{};
    Rectangle hitbox{};
};