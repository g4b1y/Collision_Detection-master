#ifndef __POINT_RECTANGLE_HPP__
#define __POINT_RECTANGLE_HPP__

#include <math.h> 
#include <vector> 
#include "../Collision/Collision.hpp"

namespace level 
{
    class LVL_Point_Rectangle 
    {
    private:
        inline void event(sf::RenderWindow& window) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                    window.close();
            }
        } 

        inline void collision(sf::RectangleShape& r1, sf::CircleShape& c1) {
            if (col::Collision::PointRectangleCollision(c1, r1)) { 
                r1.setFillColor(sf::Color(255, 150, 0)); 
            } else { 
                r1.setFillColor(sf::Color(0, 150, 255)); 
            }
        }
    
        inline void draw(sf::RenderWindow& window, sf::RectangleShape& r1, sf::CircleShape& c1) {
            window.clear(sf::Color::White); 
            window.draw(r1);
            window.draw(c1);
            window.display();
        } 

    public: 
        LVL_Point_Rectangle() = default; 

        LVL_Point_Rectangle(sf::RenderWindow& window) 
        {
            window.setMouseCursorVisible(false); 

            sf::RectangleShape r1;
            r1.setPosition(sf::Vector2f(100, 70));
            r1.setSize(sf::Vector2f(210, 170));

            sf::CircleShape p1(3.f);

            while(window.isOpen()) 
            {
                p1.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                p1.setFillColor(sf::Color(75, 75, 75));
                r1.setFillColor(sf::Color(0, 150, 255));

                event(window); 
                collision(r1, p1); 
                draw(window, r1, p1); 
            }
        }
    }; 
}; 

#endif 
