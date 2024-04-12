#pragma once

#include <SFML/Graphics.hpp>

#include "Player.h"
#include "map.h"

class Renderer
{
public:
	void drawRays(sf::RenderTarget& target, const Player& player, const Map& map);
};