#ifndef __CIRCLE_POLYGON_HPP__
#define __CIRCLE_POLYGON_HPP__

#include <math.h> 
#include <vector> 
#include "../Collision/Collision.hpp"

namespace level
{
    class LVL_Circle_Polygon 
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

        inline void collision(sf::CircleShape& c1, sf::ConvexShape& p1) {
            if (col::Collision::CirclePolygonCollision(c1, p1)) { 
                p1.setFillColor(sf::Color(255, 150, 0)); 
                }
            else { 
                p1.setFillColor(sf::Color(0, 150, 255)); 
            }
        }

        inline void draw(sf::RenderWindow& window, sf::CircleShape& r1, sf::ConvexShape& r2) {
            window.clear(sf::Color::White);
            window.draw(r2);
            window.draw(r1);
            window.display();
        }

        inline sf::ConvexShape init() {
            std::vector<sf::Vector2f> vertices(4);
            vertices[0] = sf::Vector2f(150, 100);
            vertices[1] = sf::Vector2f(350, 130);
            vertices[2] = sf::Vector2f(300, 300);
            vertices[3] = sf::Vector2f(200, 300);

            sf::ConvexShape p;
            p.setPointCount(vertices.size());
            for (int _p = 0; _p < vertices.size(); _p++) {
                p.setPoint(_p, vertices.at(_p));
            }

            return p; 
        }
    public: 
        inline LVL_Circle_Polygon() = default; 

        LVL_Circle_Polygon(sf::RenderWindow& window) {
            window.setMouseCursorVisible(false); 
           
            sf::ConvexShape p = init();
            sf::CircleShape c(15.f);

            c.setFillColor(sf::Color(75, 75, 75));
            p.setFillColor(sf::Color(0, 150, 255));

            while (window.isOpen()) {
                c.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                c.setFillColor(sf::Color(75, 75, 75));
                p.setFillColor(sf::Color(0, 150, 255));

                event(window);       
                collision(c, p);
                draw(window, c, p); 
            }
        }
    };
}; 

#endif