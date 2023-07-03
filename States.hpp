#pragma once

#include <vector>
#include "Planet.hpp"
#include "Star.hpp"

/*
[class]

	Game State

[methods]

	GameState()

	update (??)

	draw

	processInput
*/

class GameState
{
public:
	
	virtual void draw(sf::RenderWindow& window) const = 0;

	virtual void processInput(float elapsedTime) = 0;

	virtual void update(float elapsedTime) {};

	virtual ~GameState() {};	
};

class PlayScreen : public GameState
{
	std::vector<Planet> m_planets;
	std::vector<Star> m_stars;
	Point m_dog;

public:

	PlayScreen(std::vector<Planet> planets, std::vector<Star> stars, Point dog)
	:
		m_planets{planets},
		m_stars{stars},
		m_dog{dog}
	{}

	void draw(sf::RenderWindow& window) const override
	{
	    for (const Star& star : m_stars)
	    {
	        ::draw(window, star);
	    }
        
        ::draw(window, m_dog);

        for (const Planet& planet : m_planets)
        {
            ::draw(window, planet);
        }   
    }

    void processInput(float elapsedTime) override
    {
    	m_dog.processInput(elapsedTime);
    }

    void update(float elapsedTime) override
    {
    	vector_t acceleration{};

        vector_t dog_position = m_dog.getPosition();
        for (const Planet& planet : m_planets)
        {
            if (AreIntersect(dog_position, planet.getPosition(), planet.getRadius()))
            {
                std::cout << "Game Over\n";
                exit(1);
            }

            acceleration += planet.getAcceleration(dog_position);
        }

        m_dog.update(acceleration, elapsedTime);

        animate(m_stars);
    };
};
