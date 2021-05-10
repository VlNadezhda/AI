#ifndef AI_PRINTGAME_H
#define AI_PRINTGAME_H

#include <vector>
#include <iostream>
#include "Sokoban.h"
#include "Point.h"


class PrintGame {
   std::vector<std::vector<char>> Map;
    const Point direction[4] =  {{0,1},{1,0},{0,-1},{-1,0}};
    vector<vector<Point>> path;
public:
    PrintGame(string filename1, string filename2);
    void Print_vec(vector<vector<char>> T);
    void PrintPath();
};


#endif //AI_PRINTGAME_H
