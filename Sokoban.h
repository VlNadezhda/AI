#ifndef AI_SOKOBAN_H
#define AI_SOKOBAN_H

#include <fstream>
#include<map>
#include<algorithm>
#include <iterator>
#include <cmath>
#include <vector>
#include <iostream>
#include "Point.h"
#include "Astar.h"
using namespace std;

class Sokoban {
        std::vector<Point> crates;
        std::vector<Point> marks;
        std::vector<Point> walls;
        Point player;
    public:
        Sokoban(multimap <char,Point> board){
            SetWalls(board);
            SetCrates(board);
            SetMarks(board);
            SetPlayer(board);

        };

        void SetPlayer(multimap <char,Point> range){
        auto temp = range.equal_range('@');
        for(auto i = temp.first; i != temp.second; ++i){
            this->player = i->second;
        }
    };
        void SetWalls(multimap <char,Point> range){
            auto temp = range.equal_range('$');
            for(auto i = temp.first; i != temp.second; ++i){
                this->crates.push_back(i->second);
            }
        };
        void SetMarks(multimap <char,Point> range){
        auto temp = range.equal_range('X');
        for(auto i = temp.first; i != temp.second; ++i){
            this->marks.push_back(i->second);
        }
    };
        void SetCrates(multimap <char,Point> range){
        auto temp = range.equal_range('$');
        for(auto i = temp.first; i != temp.second; ++i){
            this->crates.push_back(i->second);
        }
    };
        const std::vector<Point> GetCrates(){
            return this->crates;
        };
        const std::vector<Point> GetMarks(){
            return this->marks;
        };
        const std::vector<Point> GetWalls(){
            return this->walls;
        };
        const Point GetPlayer(){
            return this->player;
        };

        void Solver(){
            Point a = *(crates.begin()+1);
            Point b = *(marks.begin()+1);
              cout<<a.x<<":"<<a.y<<endl<<b.x<<":"<<b.y<<endl;
            Astar A(a,b,walls);
            std::vector<Point> p = A.findPath();
            for(auto i: p){
                std::cout<<"("<<i.x<<":"<<i.y<<")"<<endl;
            }
        };

};
#endif //AI_SOKOBAN_H
