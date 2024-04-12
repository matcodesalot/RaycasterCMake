#include "renderer.h"

const float PI = 3.14159265359f;
const float PLAYER_FOV = 60;
const size_t MAX_RAYCAST_DEPTH = 16;
const size_t NUM_RAYS = 600;
const float COLUMN_WIDTH = SCREEN_W / (float)NUM_RAYS;

struct Ray
{
	sf::Vector2f hitPosition;
	float distance;
	bool hit;
	bool isHitVertical;
};

static Ray castRay(sf::Vector2f start, float angleInDegrees, const Map& map);

void Renderer::draw3dView(sf::RenderTarget& target, const Player& player, const Map& map)
{
	//ceiling
	sf::RectangleShape rectangle(sf::Vector2f(SCREEN_W, SCREEN_H / 2.0f));
	rectangle.setFillColor(sf::Color(100, 170, 250));
	target.draw(rectangle);

	//floor
	rectangle.setPosition(0.0f, SCREEN_H / 2);
	rectangle.setFillColor(sf::Color(70, 70, 70));
	target.draw(rectangle);

	sf::Vector2f pPos = { player.position.x, player.position.y };

	float angle = player.angle - PLAYER_FOV / 2.0f;
	float angleIncrement = PLAYER_FOV / (float)NUM_RAYS;
	float maxRenderDistance = MAX_RAYCAST_DEPTH * map.getCellSize();
	for (size_t i = 0; i < NUM_RAYS; i++, angle += angleIncrement)
	{
		Ray ray = castRay(pPos, angle, map);


		if (ray.hit)
		{
			ray.distance *= std::cos((player.angle - angle) * PI / 180.0f); //fish eye fix

			float wallHeight = (map.getCellSize() * SCREEN_H) / ray.distance;
			if (wallHeight > SCREEN_H)
			{
				wallHeight = SCREEN_H;
			}

			float brightness = 1.0f - (ray.distance / maxRenderDistance);
			if (brightness < 0.0f)
			{
				brightness = 0.0f;
			}

			float shade = (ray.isHitVertical ? 0.8f : 1.0f) * brightness;

			float wallOffset = SCREEN_H / 2.0f - wallHeight / 2.0f;

			sf::RectangleShape column(sf::Vector2f(COLUMN_WIDTH, wallHeight));
			column.setPosition(i * COLUMN_WIDTH, wallOffset);
			column.setFillColor(sf::Color(255 * shade, 255 * shade, 255 * shade));
			target.draw(column);
		}
	}
	
}

void Renderer::drawRays(sf::RenderTarget& target, const Player& player, const Map& map)
{
	sf::Vector2f pPos = { player.position.x, player.position.y };

	for (float angle = player.angle - PLAYER_FOV / 2.0f; angle < player.angle + PLAYER_FOV; angle += 1.0f)
	{
		Ray ray = castRay(pPos, angle, map);


		if (ray.hit)
		{
			sf::Vertex line[] = {

			sf::Vertex(pPos),
			sf::Vertex(ray.hitPosition)
			};

			target.draw(line, 2, sf::Lines);
		}
	}

}

Ray castRay(sf::Vector2f start, float angleInDegrees, const Map& map)
{
	float angle = angleInDegrees * PI / 180.0f; //angle in radians
	float vTan = -std::tan(angle);
	float hTan = -1 / std::tan(angle);
	float cellSize = map.getCellSize();

	bool hit = false;

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
		vRayPos.x = std::floor(start.x / cellSize) * cellSize + cellSize;
		vRayPos.y = (start.x - vRayPos.x) * vTan + start.y;
		offset.x = cellSize;
		offset.y = -offset.x * vTan;
	}
	else if (std::cos(angle) < -0.001f)
	{
		vRayPos.x = std::floor(start.x / cellSize) * cellSize - 0.001f;
		vRayPos.y = (start.x - vRayPos.x) * vTan + start.y;
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
			hit = true;
			vdist = std::sqrt((vRayPos.x - start.x) * (vRayPos.x - start.x)
				+ (vRayPos.y - start.y) * (vRayPos.y - start.y));
			break;
		}

		vRayPos += offset;
	}

	//-------------------------------HORIZONTAL---------------------------------------

	if (sin(angle) > 0.001f)
	{
		hRayPos.y = std::floor(start.y / cellSize) * cellSize + cellSize;
		hRayPos.x = (start.y - hRayPos.y) * hTan + start.x;
		offset.y = cellSize;
		offset.x = -offset.y * hTan;
	}
	else if (sin(angle) < -0.001f)
	{
		hRayPos.y = std::floor(start.y / cellSize) * cellSize - 0.001f;
		hRayPos.x = (start.y - hRayPos.y) * hTan + start.x;
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
			hit = true;
			hdist = std::sqrt((hRayPos.x - start.x) * (hRayPos.x - start.x)
				+ (hRayPos.y - start.y) * (hRayPos.y - start.y));
			break;
		}

		hRayPos += offset;
	}

	sf::Vector2f vRPos = { vRayPos.x, vRayPos.y };
	sf::Vector2f hRPos = { hRayPos.x, hRayPos.y };

	return Ray{ hdist < vdist ? hRPos : vRPos, std::min(hdist, vdist), hit, vdist < hdist };
}