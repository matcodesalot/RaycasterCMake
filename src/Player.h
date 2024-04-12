#pragma once

#include <SFML/Graphics.hpp>
#include "Vec2.h"

constexpr float PLAYER_TURN_SPEED = 100.0f;

class Player
{
public:
	sf::Vector2f position = { 0.0f, 0.0f };
	float angle = 0.0f;

	void draw(sf::RenderTarget& target);
	void update(float deltaTime);
};