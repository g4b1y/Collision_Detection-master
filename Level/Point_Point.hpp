#ifndef __POINT_POINT_HPP__
#define __POINT_POINT_HPP__

#include <math.h> 
#include <vector> 
#include "../Collision/Collision.hpp"

namespace level 
{
    class LVL_Point_Point 
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

        inline void collision(sf::RenderWindow& window, sf::CircleShape& c1, sf::CircleShape& c2) {
            if(col::Collision::PointCollision(c2, c1) || col::Collision::PointCollision(c1, c2)) {
                window.clear(sf::Color(255, 150, 0)); 
            }
            else {
                window.clear(sf::Color(255, 255, 255)); 
            }
        }
    
        inline void draw(sf::RenderWindow& window, sf::CircleShape& c1, sf::CircleShape& c2) {
            window.draw(c2);
            window.draw(c1);
            window.display();
        } 
    public: 
        inline LVL_Point_Point() = default; 

        LVL_Point_Point(sf::RenderWindow& window) 
        {
            window.setMouseCursorVisible(false); 
            sf::CircleShape p1(20.f);
            sf::CircleShape p2(20.f);
            p2.setPosition((window.getSize().x / 2) - p2.getRadius(), (window.getSize().y / 2) - p2.getRadius());

            while (window.isOpen()) {
                p1.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                p1.setFillColor(sf::Color(75, 75, 75));
                p2.setFillColor(sf::Color(0, 150, 255));

                event(window); 
                collision(window, p1, p2); 
                draw(window, p1, p2); 
            }
        }
    }; 
}; 

#endif 