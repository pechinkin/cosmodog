#include <iostream>
#include <SFML/Graphics.hpp>
#include "Point.hpp"
#include "Planet.hpp"
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>


int main()
{
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
        
        dog.update(satellite.getAcceleration(dog.getPosition()), time);
        dog.processInput(time);
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(dog_shape);
        draw(window, satellite);
        window.display();
    }

    return 0;
}
