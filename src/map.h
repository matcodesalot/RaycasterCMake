#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

typedef std::vector<std::vector<int>> MapGrid;

class Map
{
	MapGrid grid;
	float cellSize;

public:
	Map(float cellSize, int width, int height);
	Map(float cellSize, const std::string& fileName);

	void draw(sf::RenderTarget& target);
	void setMapCell(int x, int y, int value);

	const MapGrid& getGrid() const;
	float getCellSize() const;

	size_t getWidth();
	size_t getHeight();
};