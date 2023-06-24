#include <iostream>
#include <SFML/Graphics.hpp>
#include "Point.hpp"
#include "Planet.hpp"
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

int main()
{
    Planet satellite(vector_t(100, 100), 500000);
    
    vector_t dog_position{50, 50};
    vector_t velocity = computeVelocityForRotating( satellite.getPosition(),
                                                    dog_position,
                                                    satellite.getAcceleration(dog_position));

    velocity = velocity * 1.0f;

    Point dog(dog_position.x, dog_position.y, 1, velocity.x, velocity.y); //spaceship

    sf::CircleShape spaceship; //point of spaceship
    sf::CircleShape moon; //point of planet
    spaceship.setRadius(10);
    spaceship.setOrigin(5, 5);
    moon.setRadius(20);
    moon.setOrigin(10, 10);
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


