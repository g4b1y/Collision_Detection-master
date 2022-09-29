#ifndef __RECTANGLE_POLYGON_HPP__
#define __RECTANGLE_POLYGON_HPP__

#include <math.h> 
#include <vector> 
#include "../Collision/Collision.hpp"

namespace level
{
    class LVL_Rectangle_Polygon 
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

        inline void collision(sf::RectangleShape& c1, sf::ConvexShape& p1) {
            if (col::Collision::RectanglePolygonCollision(c1, p1)) { 
                p1.setFillColor(sf::Color(255, 150, 0)); 
                }
            else { 
                p1.setFillColor(sf::Color(0, 150, 255)); 
            }
        }

        inline void draw(sf::RenderWindow& window, sf::RectangleShape& r1, sf::ConvexShape& r2) {
            window.clear(sf::Color::White);
            window.draw(r2);
            window.draw(r1);
            window.display();
        }

        inline sf::ConvexShape init_Polygon() {
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

            p.setFillColor(sf::Color(0, 150, 255));
            return p; 
        }

        inline sf::RectangleShape init_Rectangle() 
        {
            sf::RectangleShape r;
            r.setPosition(sf::Vector2f(50, 70));
            r.setSize(sf::Vector2f(35, 35));
            r.setFillColor(sf::Color(75, 75, 75));

            return r; 
        }

    public: 
        inline LVL_Rectangle_Polygon() = default; 

        LVL_Rectangle_Polygon(sf::RenderWindow& window) {
            window.setMouseCursorVisible(false); 
           
            sf::ConvexShape p = init_Polygon(); 
            sf::RectangleShape r = init_Rectangle(); 

            while (window.isOpen()) {
                r.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                r.setFillColor(sf::Color(75, 75, 75));
                p.setFillColor(sf::Color(0, 150, 255));

                event(window);        
                collision(r, p); 
                draw(window, r, p); 
            }
        }
    };
};

#endif

