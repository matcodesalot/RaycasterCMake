#include <SFML/Graphics.hpp>

#include "map.h"
#include "Player.h"
#include "renderer.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H), "Raycaster", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(60);

    sf::Clock deltaClock;

    Map map(48.0f, "../resources/map.png");

    Player player;
    player.position = Vec2(50.0f, 50.0f);

    Renderer renderer;
    renderer.init();

    while (window.isOpen())
    {
        float deltaTime = deltaClock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            //pass the event to ImGui to be parsed
            //ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }
        }

        player.update(deltaTime);

        //render
        window.clear();

        renderer.draw3dView(window, player, map);

        /*map.draw(window);
        renderer.drawRays(window, player, map);
        player.draw(window);*/

        window.display();
    }

    return 0;
}