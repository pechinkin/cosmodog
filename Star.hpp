#pragma once

class Star
{
private:
    const int num_of_vertex;
    const int m_radius;
    shape_t star;
    
public:
    Star():
    num_of_vertex{rand() % 10 + 4},

    m_radius{rand() % 6 + 20}

    {
        star.setPointCount(2 * num_of_vertex);
        float phi = 180.0/num_of_vertex*RAD;
        for(int i = 0; i != num_of_vertex; i++)
        {
            int m = i*2;
            star.setPoint(m, vector_t(m_radius*std::cos(phi*m),
                                      m_radius*std::sin(phi*m)));
            star.setPoint(m+1, vector_t(m_radius/3*std::cos(phi*(m+1)),
                                        m_radius/3*std::sin(phi*(m+1))));
        };
        star.setPosition(rand() % 500, rand() % 500);
        star.setFillColor(color_t(rand()%256, rand()%256, rand()%256));
    };
    
    shape_t getShape() const
    {
        return star;
    };
};

const void draw (sf::RenderWindow& window, const Star& star)
{
    window.draw(star.getShape());
};
