#pragma once

#include <raylib.h>
#include "Hitbox.hpp"

class Player
{
public:
	Player() = default;
	Player(Vector2 position);
	~Player();
	void update(float dt);
	void draw() const;

private:
	Vector2 position{};
	Vector2 velocity{};
	Vector2 size{};
	Hitbox hitbox;

	float speed;

	float scale = 0.1f;
	float hitboxScale = 1.f;
};