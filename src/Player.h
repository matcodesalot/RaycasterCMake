#pragma once

#include <SFML/Graphics.hpp>
#include "Vec2.h"

class Player
{
public:
	Vec2 position = { 0.0f, 0.0f };
	float angle = 0.0f;

	void draw(sf::RenderTarget& target);
	void update(float deltaTime);
};