#include "renderer.h"

const float PI = 3.14159265359f;
const size_t MAX_RAYCAST_DEPTH = 16;

struct Ray
{
	sf::Vector2f hitPosition;
	float distance;
};

Ray castRay(sf::Vector2f start, float angleInDegrees);

void Renderer::drawRays(sf::RenderTarget& target, const Player& player, const Map& map)
{
	float angle = player.angle * PI / 180.0f; //angle in radians
	float vTan = -std::tan(angle);
	float hTan = -1 / std::tan(angle);
	float cellSize = map.getCellSize();

	Vec2 vRayPos;
	Vec2 hRayPos;
	Vec2 offset;

	size_t vdof = 0;
	size_t hdof = 0;

	float vdist = std::numeric_limits<float>::max();
	float hdist = std::numeric_limits<float>::max();
	
	//-------------------------------VERTICAL---------------------------------------

	if (std::cos(angle) > 0.001f)
	{
		vRayPos.x = std::floor(player.position.x / cellSize) * cellSize + cellSize;
		vRayPos.y = (player.position.x - vRayPos.x) * vTan + player.position.y;
		offset.x = cellSize;
		offset.y = -offset.x * vTan;
	}
	else if (std::cos(angle) < -0.001f)
	{
		vRayPos.x = std::floor(player.position.x / cellSize) * cellSize - 0.001f;
		vRayPos.y = (player.position.x - vRayPos.x) * vTan + player.position.y;
		offset.x = -cellSize;
		offset.y = -offset.x * vTan;
	}
	else
	{
		vdof = MAX_RAYCAST_DEPTH;
	}

	const auto& grid = map.getGrid();

	for (; vdof < MAX_RAYCAST_DEPTH; vdof++)
	{
		int mapX = (int)(vRayPos.x / cellSize);
		int mapY = (int)(vRayPos.y / cellSize);

		if (mapY < grid.size() && mapX < grid[mapY].size() && grid[mapY][mapX])
		{
			vdist = std::sqrt((vRayPos.x - player.position.x) * (vRayPos.x - player.position.x)
				+ (vRayPos.y - player.position.y) * (vRayPos.y - player.position.y));
			break;
		}

		vRayPos += offset;
	}

	//-------------------------------HORIZONTAL---------------------------------------

	if (sin(angle) > 0.001f)
	{
		hRayPos.y = std::floor(player.position.y / cellSize) * cellSize + cellSize;
		hRayPos.x = (player.position.y - hRayPos.y) * hTan + player.position.x;
		offset.y = cellSize;
		offset.x = -offset.y * hTan;
	}
	else if (sin(angle) < -0.001f)
	{
		hRayPos.y = std::floor(player.position.y / cellSize) * cellSize - 0.001f;
		hRayPos.x = (player.position.y - hRayPos.y) * hTan + player.position.x;
		offset.y = -cellSize;
		offset.x = -offset.y * hTan;
	}
	else
	{
		hdof = MAX_RAYCAST_DEPTH;
	}

	for (; hdof < MAX_RAYCAST_DEPTH; hdof++)
	{
		int mapX = (int)(hRayPos.x / cellSize);
		int mapY = (int)(hRayPos.y / cellSize);

		if (mapY < grid.size() && mapX < grid[mapY].size() && grid[mapY][mapX])
		{
			hdist = std::sqrt((hRayPos.x - player.position.x) * (hRayPos.x - player.position.x)
				+ (hRayPos.y - player.position.y) * (hRayPos.y - player.position.y));
			break;
		}

		hRayPos += offset;
	}

	sf::Vector2f pPos = { player.position.x, player.position.y };
	sf::Vector2f vRPos = { vRayPos.x, vRayPos.y };
	sf::Vector2f hRPos = { hRayPos.x, hRayPos.y };

	sf::Vertex line[] = {
		
		sf::Vertex(pPos),
		sf::Vertex(hdist < vdist ? hRPos : vRPos)
	};

	target.draw(line, 2, sf::Lines);
}

//Ray castRay(sf::Vector2f start, float angleInDegrees)
//{
//
//}