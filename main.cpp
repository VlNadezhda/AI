#include <iostream>
#include "Sokoban.cpp"
#include "Point.h"
using namespace std;

multimap <char,Point> ReadFile(){
    string filename = "/home/nadezhda/CLionProjects/AI/g_map.txt";
    multimap <char,Point> board;
    std::ifstream out;
    char ch;
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
            }
            j++;
        }
        out.close();

    }
    return board;
}

int main() {
    multimap <char,Point> map1 = ReadFile();
    Sokoban sok(map1);
    sok.Solver();

}
