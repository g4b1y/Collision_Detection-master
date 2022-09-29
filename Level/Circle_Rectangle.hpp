#ifndef __CIRCLE_RECTANGLE_HPP__
#define __CIRCLE_RECTANGLE_HPP__

#include <math.h> 
#include <vector> 
#include "../Collision/Collision.hpp"

namespace level {
    class LVL_Circle_Rectangle 
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

        inline void collision(sf::CircleShape& c1, sf::RectangleShape& r1) {
            if (col::Collision::CircleRectangleCollision(c1, r1)) { 
                r1.setFillColor(sf::Color(255, 150, 0)); 
                }
            else { 
                r1.setFillColor(sf::Color(0, 150, 255)); 
            }
        }

        inline void draw(sf::RenderWindow& window, sf::CircleShape& c1, sf::RectangleShape& r2) {
            window.clear(sf::Color::White);
            window.draw(r2);
            window.draw(c1);
            window.display();
        }
    public: 
        inline LVL_Circle_Rectangle() = default; 

        LVL_Circle_Rectangle(sf::RenderWindow& window) {
            
            window.setMouseCursorVisible(false); 

            sf::RectangleShape r1;
            r1.setPosition(sf::Vector2f(100, 70));
            r1.setSize(sf::Vector2f(170, 135));

            sf::CircleShape c1(25.f);

            while (window.isOpen()) {
                c1.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                c1.setFillColor(sf::Color(75, 75, 75));
                r1.setFillColor(sf::Color(0, 150, 255));

                event(window);     
                collision(c1, r1); 
                draw(window, c1, r1); 
            }
        }
    };
}; 

#endif 