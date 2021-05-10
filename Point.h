#ifndef AI_POINT_H
#define AI_POINT_H
#include <iostream>
using namespace std;

class Point{
public:
    int x;
    int y;


    Point() : x(0.0), y(0.0) {}
    Point(int X, int Y){
        this->x = X;
        this->y = Y;
    };

    friend Point operator+( const Point &p1, const Point& p2){
        int x = p1.x+p2.x;
        int y = p1.y+p2.y;
        return Point(x,y);
    };
    friend Point operator-(const Point& p1,const Point& p2){
        int x = p1.x-p2.x;
        int y = p1.y-p2.y;
        return Point(x,y);
    };

    bool operator == (const Point& coordinates)
    {
        return (x == coordinates.x && y == coordinates.y);
    };

    friend std::ostream& operator<< (std::ostream &out, const Point &point){
        out << "(" << point.x << "," << point.y << ")";
        return out;
    };

};


#endif //AI_POINT_H
