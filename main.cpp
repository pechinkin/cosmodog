#include <iostream>
#include <SFML/Graphics.hpp>
#include "Point.hpp"
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

int main()
{

    sf::CircleShape spaceship; //point of spaceship
    spaceship.setRadius(10);
    Point dog(30, 20, 3, 20, 20);
    sf::RenderWindow window(sf::VideoMode(500, 500), "cosmodog");
    window.setFramerateLimit(60);
    sf::Clock clock; //to measure time of the cycle
    while (window.isOpen())
    {
        sf::Time loop = clock.getElapsedTime();
        clock.restart();
        dog.update(vector_t(0,0), loop.asSeconds());
        spaceship.setPosition(dog.getPosition());
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(spaceship);
        window.display();

    }

    return 0;
}

