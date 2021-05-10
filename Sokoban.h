#ifndef AI_SOKOBAN_H
#define AI_SOKOBAN_H

#include <fstream>
#include<map>
#include <unordered_map>
#include<algorithm>
#include <iterator>
#include <cmath>
#include <vector>
#include <iostream>
#include "Point.h"
#include "Astar.h"

using namespace std;

class Way_BM{
//    позиция игрока перед движением бочки
    Point target_player;
    Point barrel;
    Point marks;
//    путь от бочки до цели
    vector<Point> way;
public:
    Way_BM(): barrel(0, 0), marks(0, 0), way(){}
    Way_BM(Point crates_, Point marks_, vector<Point> way_): barrel(crates_), marks(marks_), way(way_){
        this->SetTarget();
        vector<Point> it = this->GetWay();
        reverse(it.begin(), it.end());
        it.push_back(this->GetTarget());
        reverse(it.begin(), it.end());
        this->way.swap(it);
    }

    Point GetBarrel(){
        return this->barrel;
    }
    Point GetMarks(){
        return this->marks;
    }
    vector<Point> GetWay(){
        return this->way;
    }
//    куда встать игроку чтобы двигать бочку
    void SetTarget(){
        if (this->GetWay()[0].x < this->GetWay()[1].x) {
            this->target_player = Point(this->GetWay()[0].x - 1, this->GetWay()[0].y);
        } else if (this->GetWay()[0].x > this->GetWay()[1].x) {
            this->target_player = Point(this->GetWay()[0].x + 1, this->GetWay()[0].y);
        } else if (this->GetWay()[0].y < this->GetWay()[1].y) {
            this->target_player = Point(this->GetWay()[0].x, this->GetWay()[0].y - 1);
        } else if (this->GetWay()[0].y > this->GetWay()[1].y) {
            this->target_player = Point(this->GetWay()[0].x, this->GetWay()[0].y + 1);
        }
    }
    Point GetTarget(){
        return this->target_player;
    }
    friend bool operator==(const Way_BM& w1, const Way_BM& w2){
       return(w1.barrel.x == w2.barrel.x && w1.barrel.y == w2.barrel.y && w1.marks.x == w2.marks.x && w1.marks.y == w2.marks.y);
    };

};

class Sokoban {
        std::vector<Point> barrel;
        std::vector<Point> marks;
        std::vector<Point> walls;
        Point player;
    public:
        Sokoban(multimap <char,Point> board){
            SetWalls(board);
            SetBarrel(board);
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
            auto temp = range.equal_range('#');
            for(auto i = temp.first; i != temp.second; ++i){
                this->walls.push_back(i->second);
            }
        };
        void SetMarks(multimap <char,Point> range){
        auto temp = range.equal_range('X');
        for(auto i = temp.first; i != temp.second; ++i){
            this->marks.push_back(i->second);
        }
    };
        void SetBarrel(multimap <char,Point> range){
        auto temp = range.equal_range('$');
        for(auto i = temp.first; i != temp.second; ++i){
            this->barrel.push_back(i->second);
        }
    };
        const std::vector<Point> GetCrates(){
            return this->barrel;
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

       vector<Way_BM> path_bar_mark(vector<Point> Marks_, vector<Point> Barrel_);
        vector<Point> Find_barrier(vector<Way_BM> SortList);
        void Solver();
        void Write_to_File(vector<vector<Point>> MainWay);
};
#endif //AI_SOKOBAN_H
