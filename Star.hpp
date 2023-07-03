#pragma once

class Star
{
private:
    const int num_of_vertex;
    const int m_radius;
    const int m_sizechanger;
    shape_t star;
    
public:
    Star():
    num_of_vertex{rand() % 6 + 4},
    m_radius{rand() % 10 + 10},
    m_sizechanger{rand() % 2}
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
        star.setFillColor(color_t(rand()%50, rand()%50, rand()%50));
    };
    
    shape_t getShape() const
    {
        return star;
    };
    
    void scale(float n)
    {
        star.setScale(n * m_sizechanger, n * m_sizechanger);
    };
    
};

const void draw(sf::RenderWindow& window, const Star& star)
{
    window.draw(star.getShape());
};

void resize(Star& star, float n)
{
        star.scale(n);
};



void animate(std::vector<Star>& stars_vector)
{
    static int counter = 0;

    if(counter % 50 == 0)
    {
        for(Star& star_ex : stars_vector)
        {
            resize(star_ex, (counter% 100 == 0)?0.9:1.1);
        };
    }
    counter++;
};
