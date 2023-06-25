#include <iostream>
#include <SFML/Graphics.hpp>
#include "Point.hpp"
#include "Planet.hpp"
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <vector>

int main()
{
    std::vector<Planet> planets
    {
        {{80, 80}, 10, color_t{220, 220, 220}, 100}, // Mercury
        {{120, 120}, 15, color_t{220, 20, 60}, 1200}, // Venus
        {{250, 250}, 14, color_t::Green, 3000}, // Earth
        {{330, 330}, 20, color_t::Red, 1500}  // Mars
    };

    Planet satellite(vector_t{100, 100});
    
    vector_t dog_position{50, 50};
    vector_t velocity = computeVelocityForRotating( satellite.getPosition(),
                                                    dog_position,
                                                    satellite.getAcceleration(dog_position));
    velocity = velocity * 1.0f;
    
    shape_t dog_shape;
    Point dog(dog_position, velocity, 1, dog_shape);
    
    sf::RenderWindow window(sf::VideoMode(500, 500), "cosmodog");
    window.setFramerateLimit(60);
    sf::Clock clock; //to measure time of the cycle
    while (window.isOpen())
    {
        sf::Time loop = clock.getElapsedTime();
        clock.restart();
        float time = loop.asSeconds();
        
        vector_t acceleration{};

        vector_t dog_position = dog.getPosition();
        for (const Planet& planet : planets)
        {
            acceleration += planet.getAcceleration(dog_position);
        }

        dog.update(acceleration, time);
        dog.processInput(time);
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(dog_shape);

        for (const Planet& planet : planets)
        {
            draw(window, planet);
        }
        
        window.display();
    }

    return 0;
}
