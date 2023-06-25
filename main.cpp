#include <iostream>
#include <SFML/Graphics.hpp>
#include "Point.hpp"
#include "Planet.hpp"
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <cmath>

int main()
{
    Planet satellite(vector_t(100, 100), 500000);
    
    vector_t dog_position{50, 50};
    vector_t velocity = computeVelocityForRotating( satellite.getPosition(),
                                                    dog_position,
                                                    satellite.getAcceleration(dog_position));

    velocity = velocity * 1.0f;

    Point dog(dog_position.x, dog_position.y, 1, velocity.x, velocity.y); //spaceship
    sf::ConvexShape spaceship;
    spaceship.setPointCount(5);
    spaceship.setPoint(0, vector_t(0, 0));
    spaceship.setPoint(1, vector_t(0, 10));
    spaceship.setPoint(2, vector_t(30, 5));
    spaceship.setOrigin(10, 5);
    spaceship.setPosition(dog.getPosition());
    sf::CircleShape moon; //point of planet
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
        dog.update(satellite.getAcceleration(dog.getPosition()),
                                             loop.asSeconds());
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            spaceship.rotate(1);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            spaceship.rotate(-1);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
//            float angle_of_ship = spaceship.getRotation();
//            dog.addVelocity(vector_t(0, 0), loop.asSeconds());
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
//            float angle_of_ship = spaceship.getRotation();
//            dog.addVelocity(vector_t(0, 0), loop.asSeconds());
        }
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


