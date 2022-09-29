#ifndef __OOP_RECTANGLE_HPP__
#define __OOP_RECTANGLE_HPP__

#include <math.h> 
#include <vector> 
#include "../Collision/Collision.hpp"

namespace level 
{
    class LVL_OOP_Rectangles 
    {
    private:
        inline void draw(sf::RenderWindow& window, sf::CircleShape& c, std::vector<sf::RectangleShape>& rects) 
        {
            window.clear(sf::Color::White);
            for(int i = 0; i < rects.size(); i++)
                window.draw(rects.at(i));
            window.draw(c);
            window.display();
        } 

        inline void event(sf::RenderWindow& window) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                    window.close();
            }
        }

        inline void collision( sf::CircleShape& c, std::vector<sf::RectangleShape>& rects) {
            for(int i = 0; i < rects.size(); i++)
            {
                if(col::Collision::CircleRectangleCollision(c, rects.at(i))) {
                    rects.at(i).setFillColor((sf::Color(255,150,0)));
                }
                else {
                    rects.at(i).setFillColor((sf::Color(0,150,255)));
                }
            }
        } 
        
        std::vector<sf::RectangleShape> init_rects(sf::RenderWindow& window) 
        {
            std::vector<sf::RectangleShape> rects; 

            for(int i = 0; i < 90; i++)
            {
                float x = static_cast<int> ((rand() % (window.getSize().x - 100) + 50) /50) * 50;
                float y = static_cast<int> ((rand() %(window.getSize().y -100) + 50) /50) * 50;
                std::cout << x << '\t'  << y << std::endl;
                sf::RectangleShape temp(sf::Vector2f(50,50));
                temp.setPosition(sf::Vector2f(x, y));
                temp.setFillColor(sf::Color(0,150,255));
                rects.push_back(temp);
            }
            return rects; 
        }
    public: 
        LVL_OOP_Rectangles() = default; 

        LVL_OOP_Rectangles(sf::RenderWindow& window)
        {
            window.setMouseCursorVisible(false); 

            sf::CircleShape c(30.f);
            c.setFillColor(sf::Color(75,75,75));


            std::vector<sf::RectangleShape> rects = init_rects(window); 
            
            while (window.isOpen()) {
                c.setPosition(sf::Vector2f(sf::Mouse::getPosition(window).x - c.getRadius(), sf::Mouse::getPosition(window).y - c.getRadius()));

                event(window);    
                collision(c, rects); 
                draw(window, c, rects); 
            }
        }
    }; 
}; 

#endif