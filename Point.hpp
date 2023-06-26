#pragma once

#include <cmath>

using vector_t = sf::Vector2f;
using shape_t = sf::ConvexShape;
using key_tt = sf::Keyboard::Key;

#define RAD           M_PI/180

class Point
{
    
private:
    vector_t m_speed;
    vector_t m_position;
    shape_t m_ship;
    const float m_mass;

    void dump() const
    {
        std::cout << "Position: " << m_position.x << ' ' << m_position.y << ' ' << time << std::endl;
        std::cout << "Speed: " << m_speed.x << ' ' << m_speed.y << ' ' << time << std::endl << std::endl;
    }

public:
    
    Point(vector_t coordinates, vector_t v, float mass): m_position{coordinates},
        m_speed{v},
        m_mass{mass}
    {
        m_ship.setPointCount(3);
        m_ship.setPoint(0, vector_t(0, 0));
        m_ship.setPoint(1, vector_t(0, 10));
        m_ship.setPoint(2, vector_t(30, 5));
        m_ship.setOrigin(10, 5);
        m_ship.setPosition(m_position);
    };
    
    void update(vector_t acceleration, float time)
    {
        m_position += m_speed * time;
        m_ship.setPosition(m_position);
        addVelocity(acceleration, time);
    };

    vector_t getPosition() const
    {
        return m_position;
    };
    
    shape_t getShape() const
    {
        return m_ship;
    };

    void setVelocity(const vector_t& new_velocity)
    {
        m_speed = new_velocity;
    };
    
    void addVelocity(vector_t boost, float time)
    {
        m_speed += boost * time;
    }
    
    void processInput(float time)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            m_ship.rotate(1);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            m_ship.rotate(-1);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            float angle_of_ship = m_ship.getRotation()*RAD;
            addVelocity(vector_t(2*std::cos(angle_of_ship),
                                 2*std::sin(angle_of_ship)), time);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            float angle_of_ship = m_ship.getRotation()*RAD;
            addVelocity(vector_t(-2*std::cos(angle_of_ship),
                                 -2*std::sin(angle_of_ship)), time);
        }
    };
    
};

const void draw (sf::RenderWindow& window, const Point& dog)
{
    window.draw(dog.getShape());
};
