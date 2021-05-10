#include <iostream>
#include "Sokoban.h"
#include "Point.h"
#include "PrintGame.h"
using namespace std;

multimap <char,Point> ReadFile(string filename){
    multimap <char,Point> board;
    std::ifstream out;
    vector<vector<char>> Map;
    vector<char> tmp;
    int j = 0;
    out.open(filename);
    if (out.is_open())
    {
        std::string str;
        while (!out.eof())
        {
            std::getline(out, str);
            for(int i = 0; i < str.size(); i++){
                if(str[i] == ' '){
                    break;
                }
                board.insert(pair<char,Point>(str[i],Point(j,i)));
                tmp.push_back(str[i]);
            }
            Map.push_back(tmp);
            tmp.clear();
            j++;
        }
        out.close();

    }
    return board;
}

int main() {
    string filename = "/home/nadezhda/CLionProjects/AI/g_map4.txt";
    string filename_ = "/home/nadezhda/CLionProjects/AI/solve.txt";
    multimap <char,Point> map1 = ReadFile(filename);
    Sokoban sok(map1);
    sok.Solver();
    PrintGame P(filename,filename_);
    P.PrintPath();
}
