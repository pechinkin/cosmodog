#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include "Point.hpp"
#include "Planet.hpp"
#include "Star.hpp"
#include "States.hpp"

int main()
{
    srand(time(0)); //for randomizing
    std::vector<Star> stars
    {
        {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}
    };

    std::vector<Planet> planets
    {
        {{80, 150}, 10, color_t{220, 220, 220}, 1000}, // Mercury
        {{120, 250}, 15, color_t{220, 20, 60}, 12000}, // Venus
        {{250, 250}, 14, color_t::Green, 20000}, // Earth
        {{330, 450}, 20, color_t::Red, 15000}  // Mars
    };

    Planet satellite(vector_t{100, 100});
    
    vector_t dog_position{300, 100};
    vector_t dog_velocity{0, 0};

    Point dog(dog_position, dog_velocity, 1);
    
    sf::RenderWindow window(sf::VideoMode(500, 500), "cosmodog");
    window.setFramerateLimit(60);
    sf::Clock clock; //to measure time of the cycle

    PlayScreen playScreen{planets, stars, dog};

    while (window.isOpen())
    {
    // [events]

        float time = clock.getElapsedTime().asSeconds();
        clock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:

                    window.close();
                    
                    break;

                case sf::Event::KeyPressed:

                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        window.close();
                    }

                    break;
            
                default:

                    break;
            }
        }

        playScreen.processInput(time);

    // [update model]

        playScreen.update(time);
        
    // [backgroud update]
        

    // [draw]

        window.clear();
        
        playScreen.draw(window);
        
        window.display();
    }

    return 0;
}
