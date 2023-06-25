#pragma once
using vector_t = sf::Vector2f;

class Point{
    
private:
    vector_t m_speed;
    vector_t m_position;
    const float m_mass;

    void dump() const
    {
        std::cout << "Position: " << m_position.x << ' ' << m_position.y << ' ' << time << std::endl;
        std::cout << "Speed: " << m_speed.x << ' ' << m_speed.y << ' ' << time << std::endl << std::endl;
    }

public:
    
    Point(float x, float y, float mass, float vx, float vy): m_mass{mass} {
        m_position.x = x;
        m_position.y = y;
        m_speed.x = vx;
        m_speed.y = vy;
    };
    
    void update(vector_t acceleration, float time){
        m_position.x += m_speed.x * time;
        m_position.y += m_speed.y * time;
        m_speed.x += acceleration.x * time;
        m_speed.y += acceleration.y * time;

        std::cout << "Acceleration: " << acceleration.x << ' ' << acceleration.y << ' ' << time << std::endl;
        dump();
    };

    vector_t getPosition(){
        return m_position;
    };

    void setVelocity(const vector_t& new_velocity)
    {
        m_speed = new_velocity;
    };
    
    void addVelocity(vector_t boost, float time)
    {
        m_position.x += boost.x * time;
        m_position.y += boost.y * time;
    }
};
