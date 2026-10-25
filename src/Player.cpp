#include "headers/Player.h"
#include "headers/Constants.h"
#include <raymath.h>
#include <cmath>

Player::Player(Vector2 position)
	: position(position), size({ static_cast<float>(TILE_SIZE), static_cast<float>(TILE_SIZE) }), speed(1000.0f), velocity({ 0.0f, 0.0f })
{
	hitbox.setSize(size, hitboxScale);
	hitbox.setPosition(position, size);
}

Player::~Player()
{
}

void Player::update(float dt)
{
	velocity = { 0.0f, 0.0f };

	if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
	{
		velocity.x = -1;
	}

	if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
	{
		velocity.x = 1;
	}

	if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
	{
		velocity.y = -1;
	}

	if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
	{
		velocity.y = 1;
	}

	if (Vector2Length(velocity) > 0)
	{
		velocity = Vector2Normalize(velocity);
	}

	velocity = Vector2Scale(velocity, speed);
	
	position = Vector2Add(position, Vector2Scale(velocity, dt));

	hitbox.setPosition(position, size);
}

void Player::draw(bool drawDebug) const
{
	DrawRectangleV(position, size, BLUE);

#if defined(_DEBUG) || !defined(NDEBUG)
	if (drawDebug)
	{
		hitbox.draw();
	}
#endif
}

Vector2 Player::getTilePosition() const
{
	return {
		std::floor((position.x + size.x / 2.0f) / TILE_SIZE),
		WORLD_HEIGHT - 1 - std::floor((position.y + size.y / 2.0f) / TILE_SIZE)
	};
}
