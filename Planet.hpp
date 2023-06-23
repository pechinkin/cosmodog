#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

using vector_t = sf::Vector2f;

float dot(const vector_t& left, const vector_t& right)
{
	return left.x * right.x + left.y * right.y;
}

vector_t normalize(const vector_t& vec)
{
	return vec / (sqrt(dot(vec, vec)));
}

std::ostream& operator<<(std::ostream& cout, const vector_t& vec)
{
	cout << '[' << vec.x << ", " << vec.y << ']';
}

class Planet
{
	static const float GravityConst;
	const float m_mass;
	const vector_t m_position;

public:

	Planet(const vector_t& position, float mass = 1)
	:
		m_position{position},
		m_mass{mass}
	{}

	vector_t getAcceleration(const vector_t& object_position) const;

	vector_t getPosition() const;
};

const float Planet::GravityConst = 1; 

vector_t Planet::getAcceleration(const vector_t& object_position) const
{
	vector_t vec_object_to_planet = m_position - object_position; 
	float coef = (GravityConst * m_mass) / (dot(vec_object_to_planet, vec_object_to_planet));

	return coef * normalize(vec_object_to_planet); 
}

vector_t Planet::getPosition() const
{
	return m_position;
}

std::ostream& operator<<(std::ostream& cout, const Planet& planet)
{
	cout << planet.getPosition();
}