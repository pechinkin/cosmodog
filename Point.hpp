#pragma once
using vector_t = sf::Vector2f;

class Point{
    
private:
    vector_t m_speed;
    vector_t m_position;
    const float m_mass;
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
        std::cout << m_position.x << ' ' << m_position.y << ' ' << time << std::endl;
        m_speed.x += acceleration.x * time * 2e4;
        m_speed.y += acceleration.y * time * 2e4;
    };
    
    vector_t getPosition(){
        return m_position;
    };
};
