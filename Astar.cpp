
#include "Astar.h"
#include "Sokoban.h"

std::vector<Point> Astar::findPath() {
    Point source = this->Sourse;
    Point target = this->Target;
    Node *current = nullptr;
    std::vector<Node*> openSet, closedSet;
    openSet.push_back(new Node(source, nullptr));

    while(!openSet.empty()){
        auto current_it = openSet.begin();
        current = *current_it;

        for(auto it = openSet.begin(); it != openSet.end(); it++){
            auto node = *it;
            if(node->getScore() <= current->getScore()){
                current = node;
                current_it = it;
            }
        }

        if(current->coordinates == Target){
            break;
        }

        closedSet.push_back(current);
        openSet.erase(current_it);
//исправить если появиться возможность передвигаться по диагонали
        for(unsigned  int i = 0; i < 4; ++i){
            Point newCoord(current->coordinates+direction[i]);
            Point player = current->coordinates-direction[i];
            if(detectCollision(newCoord, player) || findNodeOnList(closedSet,newCoord)){
                continue;
            }

            unsigned  int totalCost = current->g + ((i<4)? 10: 14);

            Node *success = findNodeOnList(openSet, newCoord);
            if(success == nullptr){
                success = new Node(newCoord,current);
                success->g = totalCost;
                success->h = getDelta(success->coordinates, Target);
                openSet.push_back(success);
            }else if(totalCost < success->g){
                success->parent = current;
                success->g = totalCost;
            }
          }
        }
        std::vector<Point> path;
        while(current != nullptr){
            path.push_back(current->coordinates);
            current = current->parent;
    }
        return path;

}

bool Astar::detectCollision(Point coord, Point player) {
    if (std::find(walls.begin(), walls.end(), coord) != walls.end() && flag == false) {
        return true;
    }else if((std::find(walls.begin(), walls.end(), coord) != walls.end() || std::find(walls.begin(), walls.end(), player) != walls.end() ) && flag == true){
        return true;
    }
     return false;

}

Node *Astar::findNodeOnList(std::vector<Node*>& nodes, Point coord) {
    for(auto node: nodes){
        if(node->coordinates == coord){
           return node;
        }
    }
    return nullptr;
}


