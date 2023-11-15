#include <Character.hpp>
#include <Drawer.hpp>
#include <stdio.h>

int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "cosmodog");

	csd::Character dog{{250, 250}, 60, M_PI/2};

	dog.growTail();

		dog.growTail();

		dog.growTail();

			dog.growTail();

	while (window.isOpen())
    {
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
                        dog.makeStep();
                    }

                    break;


                default:

                    break;
            }
        }

    // [draw]

        window.clear();

        for (const csd::Segment& segment : dog.tail_)
        {
        	draw(window, segment);
        }

        window.display();
    }
}