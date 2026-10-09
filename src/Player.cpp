#include "headers/Player.h"
#include <raymath.h>

Player::Player(Vector2 position)
	: position(position), size({ 50.0f, 50.0f }), speed(400.0f), velocity({ 0.0f, 0.0f })
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

	// Get current hitbox
	Rectangle rect = hitbox.getHitbox();

	// Keep player inside screen
	if (rect.x < 0)
		position.x -= rect.x;

	if (rect.x + rect.width > GetScreenWidth())
		position.x -= (rect.x + rect.width) - GetScreenWidth();

	if (rect.y < 0)
		position.y -= rect.y;

	if (rect.y + rect.height > GetScreenHeight())
		position.y -= (rect.y + rect.height) - GetScreenHeight();

	// Update hitbox again after correcting position
	hitbox.setPosition(position, size);
}

void Player::draw() const
{
	DrawRectangleV(position, size, BLUE);

#ifdef _DEBUG
	hitbox.draw();
#endif
}