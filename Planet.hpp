#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

using vector_t = sf::Vector2f;

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

	std::cout << "Distance to the moon: " << length(vec_object_to_planet) << '\n';

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