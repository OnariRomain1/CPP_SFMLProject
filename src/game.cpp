#include <SFML/Graphics.hpp>
#include <optional>

void processInput(sf::CircleShape& circle)
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        circle.move({-1.0f, 0.0f});
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        circle.move({1.0f, 0.0f});
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        circle.move({0.0f, -1.0f});
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        circle.move({0.0f, 1.0f});
    }
}

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({800, 600}),
        "SFML Learning"
    );

    window.setFramerateLimit(60);

    sf::CircleShape circle(50.0f);
    circle.setPosition({375.0f, 275.0f});

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (
                event->is<sf::Event::Closed>() ||
                (
                    event->is<sf::Event::KeyPressed>() &&
                    event->getIf<sf::Event::KeyPressed>()->code ==
                        sf::Keyboard::Key::Escape
                )
            )
            {
                window.close();
            }
        }

        processInput(circle);

        window.clear();
        window.draw(circle);
        window.display();
    }

    return 0;
}