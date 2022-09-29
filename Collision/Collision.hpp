
#ifndef __COLLISIONDETECTION_COLLISION_HPP__
#define __COLLISIONDETECTION_COLLISION_HPP__

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>


namespace col
{
    typedef struct {
        float x; 
        float y; 
    } vec2; 

    class Collision
    {
    private:
        static bool pointCircle(float px, float py, float cx, float cy, float r);
        static bool linePoint(float x1, float y1, float x2, float y2, float px, float py);
        static bool lineCircle(float x1, float y1, float x2, float y2, float cx, float cy, float r);
        static bool lineRect(float x1, float y1, float x2, float y2, float rx, float ry, float rw, float rh);
        static bool lineLine(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
        static bool polygonPoint(std::vector<sf::Vector2f> vertices, float px, float py);
        static bool polyLine(std::vector<sf::Vector2f> vertices, float x1, float y1, float x2, float y2);
    public:
        static bool PointCollision(sf::CircleShape& p1, sf::CircleShape& p2);
        static bool PointCircleCollision(sf::CircleShape& p, sf::CircleShape& c);
        static bool CircleCircleCollision(sf::CircleShape& c1, sf::CircleShape& c2);
        static bool PointRectangleCollision(sf::CircleShape& p, sf::RectangleShape& r);
        static bool RectangleRectangleCollision(sf::RectangleShape& r1, sf::RectangleShape &r2);
        static bool CircleRectangleCollision(sf::CircleShape &c1, sf::RectangleShape& r1);
        static bool PointPolygonCollision(sf::CircleShape& c, sf::ConvexShape& p);
        static bool CirclePolygonCollision(sf::CircleShape& c, sf::ConvexShape& p);
        static bool RectanglePolygonCollision(sf::RectangleShape& r, sf::ConvexShape& p);
        static bool PolygonPolygonCollision(sf::ConvexShape& p1, sf::ConvexShape& p2);
    };
};

#endif
