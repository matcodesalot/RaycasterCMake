#include <SFML/Graphics.hpp>

#include "map.h"
#include "Player.h"
#include "renderer.h"
#include "editor.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H), "Raycaster", sf::Style::Close | sf::Style::Titlebar);
    //window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    sf::Clock deltaClock;

    Map map(48.0f, "../resources/map.png");

    Player player{};
    player.position = sf::Vector2f(50.0f, 50.0f);

    Renderer renderer{};
    renderer.init();

    Editor editor{};
    editor.init(window);

    enum class State {Editor, Game} state = State::Game;

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

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::G)
            {
                state = state == State::Game ? State::Editor : State::Game;
            }

            if (state == State::Editor)
            {
                editor.handleEvent(event);
            }
        }

        //render
        window.clear();

        if (state == State::Game)
        {
            window.setView(window.getDefaultView());
            player.update(deltaTime);
            renderer.draw3dView(window, player, map);
        }
        else
        {
            map.draw(window);
            editor.run(window, map);
        }

        window.display();

        window.setTitle("Raycaster | " + std::to_string(1.0f / deltaTime));
    }

    return 0;
}