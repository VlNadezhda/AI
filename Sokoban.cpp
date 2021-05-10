#include "Sokoban.h"
#include <fstream>
#include<map>
#include<algorithm>
#include <iterator>
#include <cmath>
#include <vector>
#include "Point.h"

#define DEBAG

void Sokoban::Solver() {
    vector<vector<Point>> MainWay;
//    Находим кратчайший путь от бочки до цели
    vector SortList = path_bar_mark(this->marks, this->barrel);
//    Находим есть ли на пути другая бочка
    vector sequence = Find_barrier(SortList);
    vector newBarrel = sequence;
//    Новый порядок обхода бочек с учётом преград
        for (uint i = 0; i < barrel.size(); ++i) {
            if (find(newBarrel.begin(), newBarrel.end(), barrel[i]) == newBarrel.end()) {
                newBarrel.push_back(barrel[i]);
            }
#ifdef DEBAG
            cout<<"После поиска повторов: bar:"<<barrel[i].x<<";"<<barrel[i].y<<endl;
#endif

        }
        SortList = path_bar_mark(this->marks, newBarrel);
#ifdef DEBAG
        cout<<"Пути от бочки до цели"<<endl;
        for (auto i: SortList) {
            cout << "_________" << endl;
            for (auto j: i.GetWay()) {
                cout << "<" << j.x << ":" << j.y << ">" << endl;
            }
        }
#endif
//            sequence = Find_barrier(SortList);

    vector<Point> players_path;
        Way_BM first;
    for (auto i: SortList) {
        vector way = Astar(player, i.GetTarget(), walls, false).findPath();
        if (players_path.empty() || players_path.size() > way.size()) {
            players_path = way;
            first = i;
        }
    }
    reverse(players_path.begin(),players_path.end());
    MainWay.push_back(players_path);
    MainWay.push_back(first.GetWay());
    auto it = find(barrel.begin(),barrel.end(),first.GetBarrel());
    if(it != barrel.end()){barrel.erase(it);}
    it = find(marks.begin(),marks.end(),first.GetMarks());
    if(it != marks.end()){marks.erase(it);}


#ifdef DEBAG
    cout<<"Путь от игрока до первой бочки и до первой цели"<<endl;
    for(auto i: MainWay) {
        cout<<"......"<<endl;
        for (auto j: i) {
            cout << "(" << j<< ")" << endl;
        }
    }
#endif

    for(auto it = SortList.begin(); it != SortList.end(); it++){
        if(it->GetTarget() == first.GetTarget() && SortList.size() > 2){
          SortList.erase(it);
        }
    }
    for(auto i: SortList) {
        cout << "(" << i.GetTarget()<< ")" << endl;
        cout << "(" << i.GetBarrel()<<"."<<i.GetMarks()<< ")" << endl;
        for(auto j: i.GetWay()){
            cout << "<" << j << ">" << endl;
        }
    }
    while (!SortList.empty() || !barrel.empty() || !marks.empty()){
        vector Walls = walls;
        Walls.reserve(Walls.size()+barrel.size());
        Walls.insert(Walls.end(),barrel.begin(),barrel.end());

        auto it1 = SortList.begin();
        auto player_ = (MainWay.end() - 1)->end() - 1;

        auto tar = it1->GetTarget();
        vector p = Astar(*player_,tar,Walls,false).findPath();
#ifdef DEBAG

        cout<<"pl tar"<<endl;
        cout<<*player_<<" "<<tar<<endl;
        for (auto j: p){
            cout << "*" << j<< "*" << endl;
        }
#endif
            reverse(p.begin(),p.end());
            MainWay.push_back(p);
            MainWay.push_back(it1->GetWay());


//        удаляем из рассмотрения бочку до которой добавили путь
        auto bar_it = find(barrel.begin(),barrel.end(),it1->GetBarrel());
        if(bar_it != barrel.end()){barrel.erase(bar_it);}
//        удаляем из рассмотрения марку
        auto mar_it = find(marks.begin(),marks.end(),it1->GetMarks());
        if(mar_it != marks.end()){marks.erase(mar_it);}
        it1++;
        SortList.erase(SortList.begin());

//        auto it = SortList.end();
//        Добавляем к основной цепочки с координатами путь от бочки до цели
//        for (auto i: SortList) {
////            cout<<i.GetTarget()<<endl;
//            if (i.GetTarget() == player_) {
////                cout<<i.GetTarget()<<"this"<<endl;
//                vector temp = i.GetWay();
//                auto iter = temp.begin()+temp.size()-1;
//                temp.erase(iter);
//                MainWay.push_back(temp);
//                it = find(SortList.begin(), SortList.end(), i);
//            }
//        }
//#ifdef DEBAG
//        cout<<"Бочка"<<it->GetBarrel()<<";"<<it->GetMarks()<<endl;
//        for(auto i: it->GetWay()){
//            cout<<"["<<i<<"]"<<endl;
//        }
//#endif
////        удаляем из рассмотрения бочку до которой добавили путь
//        auto bar_it = find(barrel.begin(),barrel.end(),it->GetBarrel());
//        if(bar_it != barrel.end()){barrel.erase(bar_it);}
////        удаляем из рассмотрения марку
//        auto mar_it = find(marks.begin(),marks.end(),it->GetMarks());
//        if(mar_it != marks.end()){marks.erase(mar_it);}
//
//        SortList.erase(it);
//        if(SortList.empty()){
//            break;
//        }
//        players_path.clear();
//        player_ = MainWay.back().back();
//
//        vector Walls = walls;
//        Walls.reserve(Walls.size()+barrel.size());
//        Walls.insert(Walls.end(),barrel.begin(),barrel.end());
//        for (auto i: SortList) {
//            vector way = Astar(player_, i.GetTarget(), Walls, true).findPath();
//            if (players_path.empty() || players_path.size() > way.size()) {
//                players_path = way;
//            }
//        }
//        reverse(players_path.begin(),players_path.end());
//#ifdef DEBAG
//        cout<<"Путь от игрока до бочек"<<endl;
//        for(auto i: players_path){
//            cout<<"<"<<i.x<<";"<<i.y<<">"<<endl;
//        }
//#endif
//        MainWay.push_back(players_path);
//        Walls.clear();
//
//        player_ = SortList.begin()->GetTarget();
//        cout<<player_<<endl;
    }

    for(auto i: MainWay) {
        cout<<"_________"<<endl;
        for (auto j: i) {
            cout << "(" << j<< ")" << endl;
        }
    }
    Write_to_File(MainWay);

}

vector<Point> Sokoban::Find_barrier(vector<Way_BM> SortList) {
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
//                cout<<"sec"<<i.x<<"::"<<i.y<<endl;
//            }
    temp.clear();
    return sequence;
}

vector<Way_BM> Sokoban::path_bar_mark(vector<Point> Marks_, vector<Point> Barrel_) {
    vector<Way_BM> SortList;
    for(unsigned  int i = 0; i < Barrel_.size(); ++i){
        vector<Point> short_way;
        int mmarks;
        for(unsigned  int j = 0; j < Marks_.size(); ++j){
            vector way = Astar(Barrel_[i], Marks_[j], walls, true).findPath();
            if(short_way.empty() || short_way.size() > way.size()){
                short_way = way;
                mmarks = j;
            }
        }
        reverse(short_way.begin(),short_way.end());
        SortList.push_back(Way_BM(Barrel_[i], Marks_[mmarks], short_way));
        auto it = find(Marks_.begin(), Marks_.end(), Marks_[mmarks]);
        Marks_.erase(it);
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