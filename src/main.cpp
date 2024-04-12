#include <SFML/Graphics.hpp>

#include "map.h"
#include "Player.h"
#include "renderer.h"

int main()
{
    const int wWidth = 1200;
    const int wHeight = 675;
    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "Raycaster");
    window.setFramerateLimit(60);

    sf::Clock deltaClock;

    //Map map(32.0f, 16, 16); //makes a 16x16 map filled with 0's

    std::vector<std::vector<int>> grid = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    Map map(48.0f, grid);

    Player player;
    player.position = Vec2(50.0f, 50.0f);

    Renderer renderer;

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

        map.draw(window);
        renderer.drawRays(window, player, map);
        player.draw(window);

        window.display();
    }

    return 0;
}