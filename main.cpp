#include <iostream>
#include <SFML/Graphics.hpp>
#include "Point.hpp"
#include "Planet.hpp"
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

int main()
{
    Point dog(100, 50, 3, 20, 0); //spaceship
    Planet satellite(vector_t(100, 100));
    
    sf::CircleShape spaceship; //point of spaceship
    sf::CircleShape moon; //point of planet
    spaceship.setRadius(10);
    moon.setRadius(20);
    moon.setFillColor(sf::Color(100, 250, 50));
    moon.setPosition(satellite.getPosition());
    
    
    sf::RenderWindow window(sf::VideoMode(500, 500), "cosmodog");
    window.setFramerateLimit(60);
    sf::Clock clock; //to measure time of the cycle
    while (window.isOpen())
    {
        sf::Time loop = clock.getElapsedTime();
        clock.restart();
        spaceship.setPosition(dog.getPosition());
        dog.update(satellite.getAcceleration(dog.getPosition()), loop.asSeconds());
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(spaceship);
        window.draw(moon);
        window.display();

    }

    return 0;
}

// test compapibility


