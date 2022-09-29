#ifndef __MATRIX_TRANSFORMATION_HPP__
#define __MATRIX_TRANSFORMATION_HPP__

#include <math.h> 
#include <vector> 
#include "../Collision/Collision.hpp"

#define M_PI 3.14159265358979323846 

namespace level 
{
    class LVL_Matrix_Transformation
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

        inline void draw(sf::RenderWindow& window, sf::ConvexShape& s1, sf::ConvexShape& s2) {
            window.clear(sf::Color::White);
            window.draw(s1);
            window.draw(s2);
            window.display();
        }

        inline void collision(sf::ConvexShape &p1, sf::ConvexShape &p2) {
            if(col::Collision::PolygonPolygonCollision(p2, p1) || col::Collision::PolygonPolygonCollision(p1, p2)) {
                p2.setFillColor(sf::Color(255, 150, 0));
                p1.setFillColor(sf::Color(255, 150, 0));
            }
            else {
                p2.setFillColor(sf::Color(0, 150, 255));
                p1.setFillColor(sf::Color(0, 150, 255));
            }
        }

        inline void rotate(sf::ConvexShape& p, sf::Vector2f pt, float angleDeg) { 
            std::vector<sf::Vector2f> relativePoints; 
            
            for(int i = 0; i < p.getPointCount(); i++) 
            {
                relativePoints.push_back(
                    sf::Vector2f(
                        p.getPoint(i).x,
                        p.getPoint(i).y
                    )); 

                p.setPoint(i, sf::Vector2f(
                    cos(angleDeg * (M_PI/180)) * (relativePoints.at(i).x - pt.x) - sin(angleDeg * (M_PI/180)) * (relativePoints.at(i).y - pt.y) + pt.x, 
                    sin(angleDeg * (M_PI/180)) * (relativePoints.at(i).x - pt.x) + cos(angleDeg * (M_PI/180)) * (relativePoints.at(i).y - pt.y) + pt.y 
                )); 
            }
        } 

        inline sf::ConvexShape regularPolygon(sf::Vector2f _position, float r, int n) {
            sf::ConvexShape p; 
            p.setPointCount(n); 
            
            sf::Vector2f temp;
            for( int i = 0; i < n; i++)
            {
                temp.x = cos((2 * M_PI * (i )) / (n))  * r;
                temp.y = sin((2 * M_PI * (i )) / (n))  * r;
                p.setPoint(i, temp);
            }

            for(std::size_t i = 0; i < p.getPointCount(); i++) {
                p.setPoint(i, p.getPoint(i) + _position); 
            } 

            return p; 
        }

    public: 
        inline LVL_Matrix_Transformation() = default; 
        
        LVL_Matrix_Transformation(sf::RenderWindow& window) 
        {
            window.setMouseCursorVisible(false); 

            sf::ConvexShape s1 = regularPolygon(sf::Vector2f(400, 360), 100, 4);
            sf::ConvexShape s2 = regularPolygon(sf::Vector2f(620, 360), 150, 4); 

            while(window.isOpen()) {
                rotate(s1, sf::Vector2f(400, 360), 1.2); 
                rotate(s2, sf::Vector2f(620, 360), 1.2);

                event(window); 
                collision(s1, s2); 
                draw(window, s1, s2); 
            }
        }
    }; 
}; 

#endif