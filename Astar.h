#include "Point.cpp"
#ifndef AI_ASTAR_H
#define AI_ASTAR_H
#include <vector>
#include <cmath>
#include <set>

class Node{
public:
    Point coordinates = Point(0, 0);
    Node *parent;
    Node *child;

    Node(Point coord, Node *parent_){
        parent = parent_;
        coordinates = coord;
        g = h = 0;
    }

    float g;
    float h;
    float f;

    float getScore(){
        return g+h;
    }
};

class Astar {
    bool flag;
    std::vector<Node*> NodeSet;
    std::vector<Point> CoordinateList;
    std::vector<Point> walls;
    Point Sourse;
    Point Target;
    const Point direction[4] =  {{0,1},{1,0},{0,-1},{-1,0}};
public:

    Astar(Point source_, Point target_, std::vector<Point> wall_,bool flag_): Sourse(source_), Target(target_), walls(wall_),flag(flag_){}

    std::vector<Point> findPath();
    Node* findNodeOnList(std::vector<Node*>& node, Point coord);

  float getDelta(Point source, Point target)
  {
      return sqrt(pow((source.x - target.x),2) + pow((source.y - target.y),2));
  }

  bool detectCollision(Point p, Point wall);

};

#endif //AI_ASTAR_H
