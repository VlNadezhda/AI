#include "PrintGame.h"
#include <cstdlib>
#include <string>

PrintGame::PrintGame(string filename1, string filename2){
    std::ifstream out;
    vector<vector<char>> Map;
    vector<char> tmp;
    vector<vector<Point>> Path;
    vector<Point> tmp_;
    int j = 0;
    out.open(filename1);
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
                tmp.push_back(str[i]);
            }
            Map.push_back(tmp);
            tmp.clear();
            j++;
        }
        out.close();

    }

    out.open(filename2);
    if (out.is_open())
    {
        std::string str_;
        while (!out.eof())
        {
            Point p;
            int flag;
            string tmp;
            int num1,num2;
            std::getline(out, str_);

            for(int i = 0; i < str_.size(); i++){

                if(i != 0){
                if(flag == 1){
                    tmp += str_[i];
                }else if(flag == 2){
                    tmp += str_[i];
                }else if(flag == 3){
                    p = Point(num1,num2);
                    tmp_.push_back(p);
                }
            }
                if(str_[i] == '('){
                    flag = 1;
                }else if(str_[i] == ';'){
                    flag = 2;
                    num1 = stoi(tmp);
                    tmp.clear();
                }else if(str_[i] == ')'){
                    flag = 3;
                    num2 = stoi(tmp);
                    tmp.clear();
                }
                if(i == str_.size()-1){
                    if(flag == 1){
                        tmp += str_[i];
                    }else if(flag == 2){
                        tmp += str_[i];
                    }else if(flag == 3){
                        p = Point(num1,num2);
                        tmp_.push_back(p);
                    }
                }

                if(str_[i] == '\n'){
                    break;
                }
            }

            Path.push_back(tmp_);
            tmp_.clear();
            j++;
        }
        out.close();
    }

    this->Map = Map;
    this->path = Path;
    for(auto i: Path){
        for(auto v: i){
            cout<<v.x<<","<<v.y<<" |";
        }
        cout<<endl;
    }
}

void PrintGame::Print_vec(vector<vector<char>> T){
    for(auto i: T){
        for(auto j : i){
            cout<<j;
        }
        cout<<endl;
    }
}

void PrintGame::PrintPath(){
    Print_vec(this->Map);
    vector<Point> good;
    std::vector<std::vector<char>> myMap = this->Map;
    bool flag = false;
    vector <Point> ::iterator p;
    for(auto i: this->path){
        for(auto point = i.begin(); point != i.end(); point++){
            p = point;
            for(auto i: good){
                myMap[i.x][i.y] = 'G';
            }
            if(flag){
                if(point == i.end()-2){
                    Point p;
                    for(auto i: this->direction){
                        p = *(point)+i;
                        if(myMap[p.x][p.y] == 'X'){
                            flag = false;
                            myMap[point->x][point->y] = '@';
                            myMap[p.x][p.y] = 'G';
                            good.push_back(Point(p.x,p.y));
                            Print_vec(myMap);
                            myMap[point->x][point->y] = '.';
                            break;
                        }
                    }
                }else{
//                    cout<<point->x<<";"<<point->y<<endl;
                    myMap[point->x][point->y] = '@';
                    p++;
                    myMap[p->x][p->y] = '$';
                    Print_vec(myMap);
                    myMap[point->x][point->y] = '.';
                }
            }else if(myMap[point->x][point->y] == '$'){
                flag = true;
                myMap[point->x][point->y] = '.';
            }else if(flag == false){
                myMap[point->x][point->y] = '@';
                Print_vec(myMap);
                myMap[point->x][point->y] = '.';
            }


        }
    }


}
