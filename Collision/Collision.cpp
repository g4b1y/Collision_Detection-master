#include "Collision.hpp"

float dist(float px, float py, float x1, float x2) {
    return sqrt(pow(px - x1, 2) + pow(py - x2, 2));
}

bool col::Collision::pointCircle(float px, float py, float cx, float cy, float r) {
    float distX = px - cx;
    float distY = py - cy;
    float distance = sqrt( (distX*distX) + (distY*distY) );

    if (distance <= r) {
        return true;
    }
    return false;
}

bool col::Collision::linePoint(float x1, float y1, float x2, float y2, float px, float py) {
    float d1 = dist(px,py, x1,y1);
    float d2 = dist(px,py, x2,y2);

    float lineLen = dist(x1,y1, x2,y2);
    float buffer = 0.001;

    if (d1+d2 >= lineLen-buffer && d1+d2 <= lineLen+buffer) {
        return true;
    }
    return false;
}

bool col::Collision::lineCircle(float x1, float y1, float x2, float y2, float cx, float cy, float r) {
    bool inside1 = pointCircle(x1,y1, cx,cy,r);
    bool inside2 = pointCircle(x2,y2, cx,cy,r);
    if (inside1 || inside2) return true;

    float distX = x1 - x2;
    float distY = y1 - y2;
    float len = sqrt( (distX*distX) + (distY*distY) );

    float dot = ( (cx-x1)*(x2-x1) + (cy-y1)*(y2-y1) ) / pow(len,2);

    float closestX = x1 + (dot * (x2-x1));
    float closestY = y1 + (dot * (y2-y1));

    bool onSegment = linePoint(x1,y1,x2,y2, closestX,closestY);
    if (!onSegment) return false;

    distX = closestX - cx;
    distY = closestY - cy;
    float distance = sqrt( (distX*distX) + (distY*distY) );

    if (distance <= r) {
        return true;
    }
    return false;
}

bool col::Collision::lineRect(float x1, float y1, float x2, float y2, float rx, float ry, float rw, float rh) {
    bool left =   lineLine(x1,y1,x2,y2, rx,ry,rx, ry+rh);
    bool right =  lineLine(x1,y1,x2,y2, rx+rw,ry, rx+rw,ry+rh);
    bool top =    lineLine(x1,y1,x2,y2, rx,ry, rx+rw,ry);
    bool bottom = lineLine(x1,y1,x2,y2, rx,ry+rh, rx+rw,ry+rh);

    // if ANY of the above are true,
    // the line has hit the rectangle
    if (left || right || top || bottom) {
        return true;
    }
    return false;
}

bool col::Collision::lineLine(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
    float uA = ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
    float uB = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));

    if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {
        return true;
    }
    return false;
}

bool col::Collision::polygonPoint(std::vector<sf::Vector2f> vertices, float px, float py) {
    bool collision = false;

    int next = 0;
    for (int current=0; current<vertices.size(); current++) {
        next = current+1;
        if (next == vertices.size()) next = 0;

        sf::Vector2f vc = vertices[current];
        sf::Vector2f vn = vertices[next];

        if (((vc.y > py && vn.y < py) || (vc.y < py && vn.y > py)) &&
            (px < (vn.x-vc.x)*(py-vc.y) / (vn.y-vc.y)+vc.x)) {
            collision = !collision;
        }
    }
    return collision;
}

bool col::Collision::polyLine(std::vector<sf::Vector2f> vertices, float x1, float y1, float x2, float y2) {
    int next = 0;
    for (int current=0; current<vertices.size(); current++)
    {
        next = current+1;
        if (next == vertices.size()) {next = 0; }

        float x3 = vertices[current].x;
        float y3 = vertices[current].y;
        float x4 = vertices[next].x;
        float y4 = vertices[next].y;

        bool hit = lineLine(x1, y1, x2, y2, x3, y3, x4, y4);
        if (hit) {
            return true;
        }
    }
    return false;
}

// ---------------------------------Public --------------------------------------------
bool col::Collision::PointCollision(sf::CircleShape& p1, sf::CircleShape& p2) {
    if(p1.getPosition().x == p2.getPosition().x && p1.getPosition().y == p2.getPosition().y) {
        return true;
    }
    return false;
}

bool col::Collision::PointCircleCollision(sf::CircleShape &p, sf::CircleShape &c) {
    const vec2 _c = {
            c.getPosition().x + c.getRadius(),
            c.getPosition().y + c.getRadius()
    };

    const vec2 _p = {
            p.getPosition().x,
            p.getPosition().y
    };

    const float radius = c.getRadius();

    float distX = _p.x - _c.x;
    float distY = _p.y - _c.y;
    float distance = std::sqrt((distX * distX) + (distY * distY));

    if(distance <= radius) {return true; }
    return false;
}

bool col::Collision::CircleCircleCollision(sf::CircleShape& c1, sf::CircleShape& c2) {
    const vec2 c1Center = {
            c1.getPosition().x + c1.getRadius(),
            c1.getPosition().y + c1.getRadius()
    };
    const vec2 c2Center = {
            c2.getPosition().x + c2.getRadius(),
            c2.getPosition().y + c2.getRadius()
    };

    float distX = c1Center.x - c2Center.x;
    float distY = c1Center.y - c2Center.y;
    float distance = sqrt((distX * distX) + (distY * distY));

    if(distance <= c1.getRadius() + c2.getRadius()) {
        return  true;
    }
    return false;
}

bool col::Collision::PointRectangleCollision(sf::CircleShape &p, sf::RectangleShape &r) {
    const float px = p.getPosition().x;
    const float py = p.getPosition().y;

    const float rx = r.getPosition().x;
    const float ry = r.getPosition().y;
    const float rw = r.getSize().x;
    const float rh = r.getSize().y;

    if( (px >= rx) && (px <= rx + rw) &&
        (py >= ry) && (py <= ry + rh)) {
        return true;
    }
    return false;
}

bool col::Collision::RectangleRectangleCollision(sf::RectangleShape &r1, sf::RectangleShape &r2) {
    float r1x = r1.getPosition().x;
    float r1y = r1.getPosition().y;
    float r1w = r1.getSize().x;
    float r1h = r1.getSize().y;

    float r2x = r2.getPosition().x;
    float r2y = r2.getPosition().y;
    float r2w = r2.getSize().x;
    float r2h = r2.getSize().y;

    if( (r1x + r1w >= r2x ) && (r1x <= r2x + r2w ) &&
        (r1y + r1h >= r2y ) && (r1y <= r2y + r2h)) {
        return true;
    }
    return false;
}

bool col::Collision::CircleRectangleCollision(sf::CircleShape &c, sf::RectangleShape &r) {
    float cx = c.getPosition().x + c.getRadius();
    float cy = c.getPosition().y + c.getRadius();
    float radius = c.getRadius();

    float rx = r.getPosition().x;
    float ry = r.getPosition().y;
    float rw = r.getSize().x;
    float rh = r.getSize().y;

    float testX = cx;
    float testY = cy;

    if (cx < rx)         { testX = rx; }
    else if (cx > rx+rw) { testX = rx+rw; }
    if (cy < ry)         { testY = ry; }
    else if (cy > ry+rh) { testY = ry+rh; }

    float distX = cx-testX;
    float distY = cy-testY;
    float distance = sqrt( (distX*distX) + (distY*distY) );

    if (distance <= radius) {
        return true;
    }
    return false;
}

bool col::Collision::PointPolygonCollision(sf::CircleShape &c, sf::ConvexShape &p) {

    std::vector<sf::Vector2f> vertices;
    for(int i = 0; i < p.getPointCount(); i++)
    {
        vertices.push_back(p.getPoint(i));
    }
    float px = c.getPosition().x;
    float py = c.getPosition().y;


    bool collision = false;
    int next = 0;

    for(int current = 0; current < vertices.size(); current++)
    {
        next = current + 1;
        if (next == vertices.size()) { next = 0; }

        sf::Vector2f vc = vertices[current];
        sf::Vector2f vn = vertices[next];

        if (((vc.y >= py && vn.y < py) || (vc.y < py && vn.y >= py)) &&
            (px < (vn.x-vc.x)*(py-vc.y) / (vn.y-vc.y)+vc.x)) {
            collision = !collision;
        }
    }
    return collision;
}

bool col::Collision::CirclePolygonCollision(sf::CircleShape &c, sf::ConvexShape &p) {
    float cx = c.getPosition().x + c.getRadius();
    float cy = c.getPosition().y + c.getRadius();
    float r = c.getRadius();

    std::vector<sf::Vector2f> vertices;
    for(int i = 0; i < p.getPointCount(); i++)
    {
        vertices.push_back(p.getPoint(i));
    }
    std::cout << std::endl;

    int next = 0;
    for (int current = 0; current < vertices.size(); current++)
    {
        next = current + 1;
        if (next == vertices.size()) { next = 0; }

        sf::Vector2f vc = vertices[current];
        sf::Vector2f vn = vertices[next];


        bool collision = lineCircle(vc.x,vc.y, vn.x,vn.y, cx,cy,r) ||PointPolygonCollision(c, p);

        if (collision) { return true; }
    }
    return false;
}

bool col::Collision::RectanglePolygonCollision(sf::RectangleShape &r, sf::ConvexShape &p) {
    std::vector<sf::Vector2f> vertices;
    
    for(int i = 0; i < p.getPointCount(); i++) 
    {
        vertices.push_back(p.getPoint(i));
    }

    float rx = r.getPosition().x;
    float ry = r.getPosition().y;
    float rw = r.getSize().x;
    float rh = r.getSize().y;

    int next = 0;
    for (int current=0; current<vertices.size(); current++)
    {
        next = current+1;
        if (next == vertices.size()) {
            next = 0;
        }

        sf::Vector2f vc = vertices[current];
        sf::Vector2f vn = vertices[next];

        bool collision = lineRect(vc.x,vc.y,vn.x,vn.y, rx,ry,rw,rh);
        if (collision) {
            return true;
        }

        bool inside = polygonPoint(vertices, rx,ry);
        if (inside) {
            return true;
        }
    }
    return false;
}

bool col::Collision::PolygonPolygonCollision(sf::ConvexShape& p1, sf::ConvexShape& p2) {
    std::vector<sf::Vector2f> p1Vertices;
    std::vector<sf::Vector2f> p2Vertices;

    for(int i = 0; i < p1.getPointCount(); i++)
    {
        p1Vertices.push_back(p1.getPoint(i));
    }
    for(int i = 0; i < p2.getPointCount() ; i++)
    {
        p2Vertices.push_back(p2.getPoint(i));
    }


    int next = 0;
    for(int current = 0; current < p1.getPointCount(); current++)
    {
        next = current + 1;
        if(next == p1.getPointCount()) {next = 0; }

        sf::Vector2f vc = p1.getPoint(current);
        sf::Vector2f vn = p1.getPoint(next);

        bool collision = polyLine(p2Vertices, vc.x, vc.y, vn.x, vn.y);
        if(collision) {return true; }

        collision = polygonPoint(p1Vertices, p2.getPoint(0).x, p2.getPoint(0).y);
        if(collision) {return true; }
    }
    return false;
}










