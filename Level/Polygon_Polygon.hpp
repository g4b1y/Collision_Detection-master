#ifndef __POLYGON_POLYGON_HPP__
#define __POLYGON_POLYGON_HPP__


#include <math.h> 
#include <vector> 
#include "../Collision/Collision.hpp"

namespace level 
{
    class LVL_Polygon_Polygon
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

        inline void collision(sf::ConvexShape &p1, sf::ConvexShape &p2) {
            if(col::Collision::PolygonPolygonCollision(p2, p1) || col::Collision::PolygonPolygonCollision(p1, p2)) {
                p2.setFillColor(sf::Color(255, 150, 0));
            }
            else {
                p1.setFillColor(sf::Color(75, 75, 75));
                p2.setFillColor(sf::Color(0, 150, 255));
            }
        }

        inline void draw(sf::RenderWindow& window, sf::ConvexShape& c1, sf::ConvexShape& c2) {
            window.clear(sf::Color::White);
            window.draw(c2);
            window.draw(c1);
            window.display();
        } 
    public: 

        inline LVL_Polygon_Polygon() = default; 

        LVL_Polygon_Polygon(sf::RenderWindow& window)
        {
            window.setMouseCursorVisible(false); 

            sf::ConvexShape pentagon;
            pentagon.setPointCount(5); 

            sf::Vector2f temp; 
            for( int i = 0; i < 5; i++) {
                temp.x = cos((2 * 3.1415 * (i)) / (5))  * 150;
                temp.y = sin((2 * 3.1415 * (i)) / (5))  * 150;
                pentagon.setPoint(i, temp);
            }


            sf::Vector2f newPos(window.getSize().x / 3, window.getSize().y / 2); 
            for(std::size_t i = 0; i < pentagon.getPointCount(); i++) {
                pentagon.setPoint(i, pentagon.getPoint(i) + newPos); 
            }
                

            sf::ConvexShape randomPolygon;
            randomPolygon.setPointCount(7);

            for (int i = 0; i < 5; i++) {
                float x = 100 + cos(rand() % 50 + 15) * 45;
                float y = 50 + sin(rand() % 50 + 15) * 45;
                randomPolygon.setPoint(i, sf::Vector2f(x, y));
            }   

            pentagon.setFillColor(sf::Color(255, 150, 0));
            randomPolygon.setFillColor(sf::Color(75, 75, 75));
            
            while (window.isOpen()) {
                sf::Vector2f mouse(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                sf::Vector2f diff(mouse.x - randomPolygon.getPoint(0).x, mouse.y - randomPolygon.getPoint(0).y);
                for (int i = 0; i < randomPolygon.getPointCount(); i++) {
                    randomPolygon.setPoint(i, randomPolygon.getPoint(i) + diff);
                }
            
                event(window); 
                collision(randomPolygon, pentagon); 
                draw(window, randomPolygon, pentagon); 
            }
        } 
    };
}; 



#endif 