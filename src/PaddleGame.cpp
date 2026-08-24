#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>
using namespace std;

void ProcessInput(sf::RectangleShape& PlayerRect, float deltaTime){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        PlayerRect.move({-deltaTime * 200, 0.0f });  

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        PlayerRect.move({deltaTime * 200, 0.0f});  

    }
   
}
void ClamptoWindow(sf::RectangleShape& Rect, sf::RenderWindow& window){
    sf::Vector2f position = Rect.getPosition();
    sf::Vector2u windowSize = window.getSize();

    float width = Rect.getSize().x;
    float height = Rect.getSize().y;

    if (position.x < 0)
    {
        position.x = 0;
    }

    if (position.y < 0)
    {
        position.y = 0;
    }

    if (position.x + width > windowSize.x)
    {
        position.x = windowSize.x - width;
    }

    if (position.y + height > windowSize.y)
    {
        position.y = windowSize.y - height;
    }

    Rect.setPosition(position);
}
void ProcessEnemyInput(sf::RectangleShape& EnemyRect, sf::Vector2f direction, float deltaTime){

    float speed = 100.0f; // pixels per second
    float xOffset = 10.0f;
     if (direction.x < 0)
    {
        EnemyRect.move({(-speed - xOffset) * deltaTime, 0.0f});
    }
    else if (direction.x > 0)
    {
        EnemyRect.move({(speed + xOffset) * deltaTime, 0.0f});
    }
   
}

void gameLoop(){
    sf::Clock clock;
    sf::Clock gameClock;
    sf::RectangleShape PlayerRect(
    sf::Vector2f(100.0f, 50.0f));
    PlayerRect.setFillColor(sf::Color::Green);
    PlayerRect.setPosition({350.0f, 540.0f});
    
    sf::RectangleShape EnemyRect(
    sf::Vector2f(100.0f, 50.0f));
    EnemyRect.setFillColor(sf::Color::Red);
    EnemyRect.setPosition({350.0f, 10.0f});
    
    sf::CircleShape ball(50.0f);
    ball.setFillColor(sf::Color::Blue);
    ball.setPosition({350.0f, 300.0f});
    const sf::Font font("src/Fonts/Vampire Wars Italic.ttf");
        
    sf::Text text(font,"timer: ");
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setPosition({10.0f, 10.0f});

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Paddle Game");
     window.setFramerateLimit(60);
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
       
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

        window.clear();
        ProcessInput(PlayerRect, deltaTime);
        ProcessEnemyInput(EnemyRect, PlayerRect.getPosition() - EnemyRect.getPosition(), deltaTime); 
        ClamptoWindow(EnemyRect, window);
        text.setString("timer: " + std::to_string(static_cast<int>(gameClock.getElapsedTime().asSeconds())));
        window.draw(PlayerRect);
        window.draw(EnemyRect);    
        window.draw(ball);
        window.draw(text);

        window.display();

    }
}
int main(){
    gameLoop();
    return 0;

}