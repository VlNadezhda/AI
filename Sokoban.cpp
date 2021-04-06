#include "Sokoban.h"
#include <fstream>
#include<map>
#include<algorithm>
#include <iterator>
#include <cmath>
#include <vector>
#include "Point.h"

void Sokoban::Solver() {
    vector<vector<Point>> MainWay;
    vector<Way_bar_mar> SortList = path_barrel_to_memark(this->marks, this->barrel);
    vector<Point> sequence = Find_false_path(SortList);
    vector<Point> newBarrel = sequence;
    for(unsigned  int i = 0; i < barrel.size(); ++i){
        if(find(newBarrel.begin(), newBarrel.end(), barrel[i]) == newBarrel.end()){
            newBarrel.push_back(barrel[i]);
        }
    }
    SortList = path_barrel_to_memark(this->marks,newBarrel);
//            sequence = Find_false_path(SortList);

    vector<Point> players_path;
    Point player_;
    for (auto i: SortList) {
        i.SetTarget();
        vector<Point> way = Astar(player, i.GetTarget(), walls, false).findPath();
        if (players_path.empty() || players_path.size() > way.size()) {
            players_path = way;
        }
    }
    reverse(players_path.begin(),players_path.end());
    MainWay.push_back(players_path);
    while (!SortList.empty()) {
        player_ = *(MainWay.back().begin()+MainWay.back().size()-1);
//                cout<<player_.x<<";;"<<player_.y<<endl;
        auto it = SortList.end();
        for (auto i: SortList) {
            i.SetTarget();
            string flag;
            if (i.GetTarget() == player_) {
                vector<Point> temp = i.GetWay();
                auto iter = temp.begin()+temp.size()-1;
                temp.erase(iter);
                MainWay.push_back(temp);
                it = find(SortList.begin(), SortList.end(), i);
            }
        }
        auto bar_it = find(barrel.begin(),barrel.end(),it->GetBarrel());
        if(bar_it != barrel.end()){barrel.erase(bar_it);}
        auto mar_it = find(marks.begin(),marks.end(),it->GetMarks());
        if(mar_it != marks.end()){marks.erase(mar_it);}

        SortList.erase(it);
        if(SortList.empty()){
            break;
        }
        players_path.clear();
        player_ = MainWay.back().back();
//                cout<<"Player="<<player_.x<<":"<<player_.y<<endl;

        vector<Point> Walls = walls;
        Walls.reserve(Walls.size()+barrel.size());
        Walls.insert(Walls.end(),barrel.begin(),barrel.end());
        for (auto i: SortList) {
            i.SetTarget();
            vector<Point> way = Astar(player_, i.GetTarget(), Walls, true).findPath();
            if (players_path.empty() || players_path.size() > way.size()) {
                players_path = way;
            }
        }
        reverse(players_path.begin(),players_path.end());
        MainWay.push_back(players_path);
        Walls.clear();
    }

    for(auto i: MainWay) {
        cout<<"_________"<<endl;
        for (auto j: i) {
            cout << "<" << j.x << ":" << j.y << ">" << endl;
        }
    }
    Write_to_File(MainWay);

}

vector<Point> Sokoban::Find_false_path(vector<Way_bar_mar> SortList) {
    vector<Point> sequence;
    vector<Point> temp;
    for (auto i: SortList) {
        temp.push_back(i.GetBarrel());
        for (auto w: i.GetWay()) {
            if (find(barrel.begin(), barrel.end(), w) != barrel.end() && !(w == *i.GetWay().begin()) && find(temp.begin(), temp.end(), w) == temp.end()) {
                sequence.push_back(w);
            }
        }
    }
//            for(auto i:sequence){
//                cout<<i.x<<"::"<<i.y<<endl;
//            }
    temp.clear();
    return sequence;
}

vector<Way_bar_mar> Sokoban::path_barrel_to_memark(vector<Point> Marks_, vector<Point> Barrel_) {
    vector<Way_bar_mar> SortList;
    vector<Point> marks_ = Marks_;
    vector<Point> barrel_ = Barrel_;
    for(unsigned  int i = 0; i < barrel_.size(); ++i){
        vector<Point> short_way;
        int mmarks;
        for(unsigned  int j = 0; j < marks_.size(); ++j){
            vector<Point> way = Astar(barrel_[i], marks_[j], walls, true).findPath();
            if(short_way.empty() || short_way.size() > way.size()){
                short_way = way;
                mmarks = j;
            }
        }
        reverse(short_way.begin(),short_way.end());
        SortList.push_back(Way_bar_mar(barrel_[i], marks_[mmarks], short_way));
        auto it = find(marks_.begin(), marks_.end(), marks_[mmarks]);
        marks_.erase(it);
    }
    return SortList;
}

void Sokoban::Write_to_File(vector<vector<Point>> MainWay){
    ofstream f("/home/nadezhda/CLionProjects/AI/solve.txt");
    for(auto i: MainWay)
    {
        for(auto way: i) {
          f << "(" << way.x << ";" << way.y << ")";
        }
        f<<"\n";
    }
    f.close();
}