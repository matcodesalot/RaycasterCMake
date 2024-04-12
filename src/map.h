#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Map
{
	std::vector<std::vector<int>> grid;
	float cellSize;

public:
	Map(float cellSize, int width, int height);
	Map(float cellSize, std::vector<std::vector<int>> grid);

	void draw(sf::RenderTarget& target);

	const std::vector<std::vector<int>>& getGrid() const;
	float getCellSize() const;
};