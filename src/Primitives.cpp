#include <SFML/Graphics.hpp>
#include <glad/gl.h>

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({800, 600}),
        "Primitives"
    );

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();

        // OpenGL / drawing code here

        window.display();
    }

    return 0;
}