#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

using vector_t = sf::Vector2f;
using color_t = sf::Color;
using circle_t = sf::CircleShape;

float dot(const vector_t& left, const vector_t& right)
{
	return left.x * right.x + left.y * right.y;
}

float length(const vector_t& vec)
{
	return sqrt(dot(vec, vec));
}

vector_t normalize(const vector_t& vec)
{
	return vec / length(vec);
}

std::ostream& operator<<(std::ostream& cout, const vector_t& vec)
{
	cout << '[' << vec.x << ", " << vec.y << ']';
}

circle_t createPlanet(const vector_t& position, float R, const color_t& color)
{
	circle_t planet_view;
	planet_view.setRadius(R);
    planet_view.setOrigin(R/2, R/2);
    planet_view.setFillColor(color);
    planet_view.setPosition(position);

    return planet_view;
}

class Planet
{
// [default parameters]

	static const float GravityConst;
	static const float DefaultRadius;
	static const float DefaultMass;
	static const color_t DefaultColor;

// [model]

	const float m_mass;
    const float m_radius;
	const vector_t m_position;

// [view]
    
    circle_t m_planet_view;

public:

    Planet(	const vector_t& position,
    		float radius = DefaultRadius,
    		const color_t& color = DefaultColor,
    		float mass = DefaultMass);

	vector_t getAcceleration(const vector_t& object_position) const;

	vector_t getPosition() const;

	circle_t getPlanetView() const;
};

const float Planet::GravityConst = 1;
const float Planet::DefaultRadius = 30;
const float Planet::DefaultMass = 1;
const color_t Planet::DefaultColor = color_t::Green;

Planet::Planet(	const vector_t& position,
	    		float radius,
	    		const color_t& color,
	    		float mass)
:
	m_position{position},
	m_mass{mass},
    m_radius{radius},
    m_planet_view{createPlanet(position, radius, color)}
{}

vector_t Planet::getAcceleration(const vector_t& object_position) const
{
	vector_t vec_object_to_planet = m_position - object_position; 
	float coef = (GravityConst * m_mass) / (dot(vec_object_to_planet, vec_object_to_planet));

	std::cout << "Distance to the moon: " << length(vec_object_to_planet) << '\n';

	return coef * normalize(vec_object_to_planet); 
}

vector_t Planet::getPosition() const
{
	return m_position;
}

circle_t Planet::getPlanetView() const
{
	return m_planet_view;
}

std::ostream& operator<<(std::ostream& cout, const Planet& planet)
{
	cout << planet.getPosition();
}

/*
acceleration for rotating around:
	
	a = v^2 / R

	v = sqrt(a*R)
*/
vector_t computeVelocityForRotating(const vector_t& planet_position,
									const vector_t& object_position,
									const vector_t& acceleration)
{
	vector_t distance = planet_position - object_position; 
	float R_square = dot(distance, distance);
	float a_square = dot(acceleration, acceleration);

	vector_t velocity = normalize(vector_t{distance.y, -distance.x});
	velocity *= sqrt(sqrt(a_square * R_square));

	return velocity;
}

bool AreIntersect(const vector_t& point, const vector_t& circle_center, float R)
{
	vector_t distance = point - circle_center;
	return dot(distance, distance) <= R*R;
}

void draw(sf::RenderWindow& window, const Planet& planet)
{
	window.draw(planet.getPlanetView());
}
