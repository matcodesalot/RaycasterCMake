#pragma once

#include <SFML/Graphics.hpp>

#include "Player.h"
#include "map.h"

const float SCREEN_W = 1200.0f;
const float SCREEN_H = 675.0f;

class Renderer
{
	sf::Texture wallTexture;
	sf::Sprite wallSprite;

public:
	void init();
	void draw3dView(sf::RenderTarget& target, const Player& player, const Map& map);
	void drawRays(sf::RenderTarget& target, const Player& player, const Map& map);
};