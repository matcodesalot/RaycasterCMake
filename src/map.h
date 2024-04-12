#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Map
{
	std::vector<std::vector<sf::Color>> grid;
	float cellSize;

public:
	Map(float cellSize, int width, int height);
	Map(float cellSize, const std::string& fileName);

	void draw(sf::RenderTarget& target);

	const std::vector<std::vector<sf::Color>>& getGrid() const;
	float getCellSize() const;
};