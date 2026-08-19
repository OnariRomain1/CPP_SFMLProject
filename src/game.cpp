#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>

using namespace std;

sf::CircleShape SpawnCircle(
    sf::CircleShape circle)
{
    sf:: Vector2f position = {100, 100};
    circle.setPosition(position);
   
    return circle;
}





void checkWindowCollision(sf::CircleShape& circle, sf::RenderWindow& window){
    //i am trying to check if the circle is colliding with the window boundaries
     sf::Vector2f position = circle.getPosition();
    sf::Vector2u windowSize = window.getSize();

    float radius = circle.getRadius();
    float diameter = radius * 2.0f;
    sf::Vector2f yEdge = {0, position.y};
    sf::Vector2f xEdge = {position.x, 0};
    sf::Vector2f rightEdge = {800 - diameter, position.y};
    sf::Vector2f bottomEdge = {position.x ,600 - diameter};
    sf::Vector2f cornerEdge = {800 - diameter,600 - diameter};
  
    /*
Cause error because the if edge handling is wrong
    if (position.x<0){
        circle.setPosition(yEdge);
    }
    if (position.y < 0){
        circle.setPosition(xEdge);
    }
    if (diameter + position.x > 800){

        circle.setPosition(rightEdge);
    }
    if (diameter + position.y > 600){
        circle.setPosition(bottomEdge);
    }

    if ((diameter + position.y >600) && (diameter + position.x > 800)){
         circle.setPosition(bottomEdge);
    }
*/

    if (position.x < 0)
    {
        position.x = 0;
    }

    if (position.y < 0)
    {
        position.y = 0;
    }

    if (position.x + diameter > windowSize.x)
    {
        position.x = windowSize.x - diameter;
    }

    if (position.y + diameter > windowSize.y)
    {
        position.y = windowSize.y - diameter;
    }

    circle.setPosition(position);
}
void checkObjectCollision(sf::CircleShape& circle, sf::CircleShape& object, float deltaTime){
    sf::Vector2f position = circle.getPosition();
    sf::Vector2f objectPosition = object.getPosition();

    
    float radius = circle.getRadius();
    float objectRadius = object.getRadius();
    float diameter = radius * 2.0f;
    float objectDiameter = objectRadius * 2.0f;
    float xOffset = 10;
    float yOffset = 10;
    float speed = 200.0f;
    if ((position.x + diameter) == (objectPosition.x +diameter)){
        
       position.x = (objectPosition.x - diameter) - xOffset ;
    
    }
     if ((position.y + diameter) == (objectPosition.y +diameter)){
        
       position.y =(objectPosition.y - diameter) - yOffset ;
    
    }
}


    

void processInput(sf::CircleShape& circle, float deltaTime)
{
    float speed = 200.0f; // pixels per second

   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        circle.move({-deltaTime * speed, 0.0f});
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        circle.move({deltaTime * speed, 0.0f});
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        circle.move({0.0f, -deltaTime * speed});
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        circle.move({0.0f, deltaTime * speed});
    }
}

int main()
{
    sf::Clock clock;
    sf::RenderWindow window(
        sf::VideoMode({800, 600}),
        "SFML Learning"
    );

    window.setFramerateLimit(60);

    sf::CircleShape circle(50.0f);
    circle.setPosition({375.0f, 275.0f});
    sf::CircleShape circleCopy = SpawnCircle(circle);
      sf::Vertex vertices[]
{
    {{  0.0f,   0.0f}, sf::Color::Red, { 0.0f,  0.0f}},
    {{  0.0f, 100.0f}, sf::Color::Red, { 0.0f, 10.0f}},
    {{100.0f, 100.0f}, sf::Color::Red, {10.0f, 10.0f}},
    {{  0.0f,   0.0f}, sf::Color::Red, { 0.0f,  0.0f}},
    {{100.0f, 100.0f}, sf::Color::Red, {10.0f, 10.0f}},
    {{100.0f,   0.0f}, sf::Color::Red, {10.0f,  0.0f}}
};
sf::Vertex Bluevertices[]
{
    {{  100.0f,   100.0f}, sf::Color::Blue, { 0.0f,  0.0f}},
    {{  100.0f, 200.0f}, sf::Color::Blue, { 0.0f, 10.0f}},
    {{200.0f, 200.0f}, sf::Color::Blue, {10.0f, 10.0f}},
    {{  100.0f,   100.0f}, sf::Color::Blue, { 0.0f,  0.0f}},
    {{200.0f, 200.0f}, sf::Color::Blue, {10.0f, 10.0f}},
    {{200.0f,   100.0f}, sf::Color::Blue, {10.0f,  0.0f}}
};

sf::Vertex LineVertices[]{
     {{ 300.0f, 300.0f}, sf::Color::Blue, { 0.0f,  0.0f}},
      {{300.0f,500.0f}, sf::Color::Blue, { 0.0f,  0.0f}},
    
       {{ 300.0f, 300.0f}, sf::Color::Blue, { 0.0f,  0.0f}},
      {{300.0f,500.0f}, sf::Color::Blue, { 0.0f,  0.0f}},

       {{ 300.0f, 600.0f}, sf::Color::Blue, { 0.0f,  0.0f}},
      {{600.0f,300.0f}, sf::Color::Blue, { 0.0f,  0.0f}},
    

};
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

        processInput(circle,deltaTime);
        cout << "Circle Position: (" << circle.getPosition().x << ", " << circle.getPosition().y << ")" << std::endl;
        
        checkWindowCollision(circle, window);

        
        checkObjectCollision(circle,circleCopy,deltaTime);

        window.clear();
        window.draw(vertices, 6, sf::PrimitiveType::Triangles);
         window.draw(Bluevertices, 6, sf::PrimitiveType::Triangles);
         window.draw(LineVertices, 6, sf::PrimitiveType::Lines);
        window.draw(circle);
        window.draw(circleCopy);
        
       
        window.display();
    }

    return 0;
}