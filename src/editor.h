#pragma once

#include "SFML/Graphics.hpp"
#include "map.h"

class Editor
{
	sf::RectangleShape cell;
	bool isFirstMouse{};
	sf::Vector2i lastMousePos;
	sf::View view;

public:
	void init(sf::RenderWindow& window);
	void run(sf::RenderWindow& window, Map& map);

	void handleEvent(const sf::Event& event);
};