#ifndef COLLISIONDETECTION_RUN_H
#define COLLISIONDETECTION_RUN_H

#include "../Collision/Collision.hpp"

#include "../Level/Polygon_Polygon.hpp"
#include "../Level/Point_Point.hpp"
#include "../Level/Point_Circle.hpp"
#include "../Level/Circle_Circle.hpp"
#include "../Level/Point_Rectangle.hpp"
#include "../Level/Rectangle_Rectangle.hpp"
#include "../Level/Circle_Rectangle.hpp"
#include "../Level/Point_Polygon.hpp"
#include "../Level/Circle_Polygon.hpp"
#include "../Level/Rectangle_Polygon.hpp"
#include "../Level/OOP_Rectangles.hpp"
#include "../Level/Matrix_Transformation.hpp"



#include <iostream>
#include <vector> 

namespace col
{
    class Run
    {
    private:
        int _type = 0;
    
        void create(int _type);
        void getInfo();
    public:
        Run();
        Run(int); 
    };
};

#endif
