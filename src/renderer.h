#pragma once

#include <SFML/Graphics.hpp>

#include "Player.h"
#include "map.h"

constexpr float SCREEN_W = 960.0f;
constexpr float SCREEN_H = 540.0f;

class Renderer
{
	sf::Texture wallTexture;
	sf::Texture skyTexture;
	sf::Image floorImage;

	sf::Texture floorBuffer;
	sf::Sprite floorBufferSprite;

public:
	void init();
	void draw3dView(sf::RenderTarget& target, const Player& player, const Map& map);
};