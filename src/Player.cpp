#include "Player.h"
#include <cmath>

constexpr float PI = 3.14159265359f;
constexpr float TURN_SPEED = PLAYER_TURN_SPEED;
constexpr float MOVE_SPEED = 100.0f;

void Player::draw(sf::RenderTarget& target)
{
	sf::CircleShape circle(8.0f);
	circle.setPosition(position.x, position.y);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	circle.setFillColor(sf::Color::Blue);

	sf::RectangleShape line(sf::Vector2f(24.0f, 2.0f));
	line.setPosition(position.x, position.y);
	line.setFillColor(sf::Color::Blue);
	line.setRotation(angle);

	target.draw(circle);
	target.draw(line);
}

void Player::update(float deltaTime)
{
	//turning left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		angle -= TURN_SPEED * deltaTime;
	}

	//turning right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		angle += TURN_SPEED * deltaTime;
	}

	//moving forward
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		float radians = angle * PI / 180.0f;

		position.x += cos(radians) * MOVE_SPEED * deltaTime;
		position.y += sin(radians) * MOVE_SPEED * deltaTime;
	}

	//moving backward
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		float radians = angle * PI / 180.0f;

		position.x -= cos(radians) * MOVE_SPEED * deltaTime;
		position.y -= sin(radians) * MOVE_SPEED * deltaTime;
	}
}
