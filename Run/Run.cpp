#include "Run.h"

col::Run::Run() {
    getInfo();
    create(_type); 
}

col::Run::Run(int Case) 
{
    if(Case >= 1 && Case <= 12) {
        _type = Case; 
        create(_type);  
    }
    else {
        std::cerr << "Error, please check your input in the ctor" << std::endl; 
    }
} 


void col::Run::create(int type) {
    sf::RenderWindow window(sf::VideoMode(1200, 720), "SFML works!", sf::Style::Resize);
    window.setMouseCursorVisible(true);
    window.setFramerateLimit(90.f);

    switch(type) {
        case 1: { 
            level::LVL_Point_Point p(window); 
        } break;

        case 2: { 
            level::LVL_Point_Circle p(window); 
        } break;

        case 3: {
            level::LVL_Circle_Circle p(window); 
        } break;

        case 4: {
            level::LVL_Point_Rectangle p(window); 
        } break;

        case 5: {
            level::LVL_Rectangle_Rectangle p(window); 
        } break;

        case 6: {
            level::LVL_Circle_Rectangle p(window); 
        } break;

        case 7: {
            level::LVL_Point_Polygon p(window); 
        } break;

        case 8: {
            level::LVL_Circle_Polygon p(window); 
        } break;

        case 9: {
            level::LVL_Rectangle_Polygon p(window);  
        } break;

        case 10: {
            level::LVL_Polygon_Polygon p(window); 
        } break;

        case  11: {
            level::LVL_OOP_Rectangles p(window); 
        } break;

        case  12: {
            level::LVL_Matrix_Transformation p(window);
        } break;
    }
}

void col::Run::getInfo() {
    std::cout << "What simulation would you like to see?\n";
    std::cout <<    "1) Point-Point Collision\n"
                 << "2) Point-Circle Collision\n"
                 << "3) Circle-Circle Collision\n"
                 << "4) Point-Rectangle Collision\n"
                 << "5) Circle-Rectangle Collision\n"
                 << "6) Point-Polygon Collision\n"
                 << "7) Circle-Polygon Collision\n"
                 << "8) Rectangle-Polygon Collision\n"
                 << "9) Polygon-Polygon Collision\n"
                 << "10) Rectangle-Rectangle Collision\n"
                 << "11) OOP-Rectangles Collision\n"
                 << "12) Matrix Transformation\n" << std::endl;
    int a; 

    while(a <= 1 || a > 12) 
    {
        std::cin >> a;
        if(a <= 1 || a > 12) { std::cout << "Try again! Please enter a valid number...\n"; } 
    }
    _type = a;
}




