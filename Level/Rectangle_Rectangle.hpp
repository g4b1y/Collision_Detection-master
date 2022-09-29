#ifndef __RECTANGLE_RECTANGLE_HPP__
#define __RECTANGLE_RECTANGLE_HPP__

#include <math.h> 
#include <vector> 
#include "../Collision/Collision.hpp"

namespace level 
{
    class LVL_Rectangle_Rectangle 
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

        inline void collision(sf::RectangleShape& r1, sf::RectangleShape& r2) {
            if (col::Collision::RectangleRectangleCollision(r2, r1) || col::Collision::RectangleRectangleCollision(r1, r2)) { 
                r1.setFillColor(sf::Color(255, 150, 0)); 
                }
            else { 
                r1.setFillColor(sf::Color(0, 150, 255)); 
            }
        }

        inline void draw(sf::RenderWindow& window, sf::RectangleShape& r1, sf::RectangleShape& r2) {
            window.clear(sf::Color::White);
            window.draw(r2);
            window.draw(r1);
            window.display();
        }
    public: 
        inline LVL_Rectangle_Rectangle() = default; 

        LVL_Rectangle_Rectangle(sf::RenderWindow& window) {

            window.setMouseCursorVisible(false); 
            sf::RectangleShape r1;
            r1.setPosition(sf::Vector2f(100, 70));
            r1.setSize(sf::Vector2f(170, 130));

            sf::RectangleShape r2;
            r2.setPosition(sf::Vector2f(50, 70));
            r2.setSize(sf::Vector2f(35, 35));


            while (window.isOpen()) {
                r2.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                r2.setFillColor(sf::Color(75, 75, 75));
                r1.setFillColor(sf::Color(0, 150, 255));


                event(window);     
                collision(r1, r2); 
                draw(window, r2, r1); 
            }
        }
    }; 
}; 

#endif 