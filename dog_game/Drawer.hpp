#pragma once

#include <Character.hpp>
#include <SFML/Graphics.hpp>

namespace csd
{
	void draw(sf::RenderWindow& window, const Segment& segment)
	{
		sf::CircleShape circle{20};
		circle.setFillColor(sf::Color(100, 250, 50));
		circle.setPosition({segment.x, 500 - segment.y});

		window.draw(circle);
	}
};