#include "editor.h"

void Editor::init(sf::RenderWindow& window)
{
	view = window.getView();
	cell.setFillColor(sf::Color::Transparent);
	cell.setOutlineColor(sf::Color::Green);
	cell.setOutlineThickness(1.0f);
}

void Editor::run(sf::RenderWindow& window, Map& map)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		if (isFirstMouse)
		{
			lastMousePos = mousePos;
			isFirstMouse = false;
		}
		else
		{
			sf::Vector2i mouseDelta = mousePos - lastMousePos;

			view.setCenter(view.getCenter() - (sf::Vector2f)mouseDelta);

			sf::Mouse::setPosition(lastMousePos, window);
		}

		window.setMouseCursorVisible(false);
	}
	else
	{
		isFirstMouse = true;
		window.setMouseCursorVisible(true);
	}

	sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
	sf::Vector2i mapPos = (sf::Vector2i)(worldPos / map.getCellSize());

	//Check if the mouse position is within the bounds of the map
	if (mapPos.x >= 0 && mapPos.y >= 0 && mapPos.x < map.getWidth() && mapPos.y < map.getHeight())
	{
		cell.setSize(sf::Vector2f(map.getCellSize(), map.getCellSize()));
		cell.setPosition((sf::Vector2f)mapPos * map.getCellSize());
		window.draw(cell);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		map.setMapCell(mapPos.x, mapPos.y, sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ? 0 : 1);
	}

	window.setView(view);
}

void Editor::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseWheelScrolled)
	{
		float zoom = 1.0f - 0.1f * event.mouseWheelScroll.delta;
		view.zoom(zoom);
	}
}
