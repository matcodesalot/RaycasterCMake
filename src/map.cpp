#include "map.h"

Map::Map(float cellSize, int width, int height)
	: cellSize(cellSize)
	, grid(height, std::vector(width, 0))
{
}

Map::Map(float cellSize, std::vector<std::vector<int>> grid)
	: cellSize(cellSize)
	, grid(grid)
{
}

void Map::draw(sf::RenderTarget& target)
{
	if (grid.empty()) { return; }

	sf::RectangleShape background(sf::Vector2f((float)grid[0].size() * cellSize, (float)grid.size() * cellSize));
	background.setFillColor(sf::Color::Black);

	target.draw(background);

	sf::RectangleShape cell(sf::Vector2f(cellSize * 0.95f, cellSize * 0.95f));

	for (size_t y = 0; y < grid.size(); y++)
	{
		for (size_t x = 0; x < grid[y].size(); x++)
		{
			if (grid[y][x] == 0)
			{
				cell.setFillColor(sf::Color(70, 70, 70));
			}
			else if (grid[y][x] == 1)
			{
				cell.setFillColor(sf::Color::Green);
			}

			cell.setPosition(sf::Vector2f(x, y) * cellSize + sf::Vector2f(cellSize * 0.025, cellSize * 0.025));

			target.draw(cell);
		}
	}
}

const std::vector<std::vector<int>>& Map::getGrid() const
{
	return grid;
}

float Map::getCellSize() const
{
	return cellSize;
}
