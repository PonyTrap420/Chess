#include "pch.h"
#include "game.h"

constexpr unsigned int HEIGHT = 800;
constexpr unsigned int WIDTH = 800;

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window = sf::RenderWindow{ { WIDTH, HEIGHT }, "Chess", sf::Style::Default, settings};
    window.setVerticalSyncEnabled(true);


    Game g(window, BOARD_WIDTH, BOARD_HEIGHT);

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                break;
                case sf::Event::MouseButtonReleased:
                    g.MousePressed();
                break;
            }
        }
        
        window.clear();

        window.draw(g);

        window.display();
    }
}