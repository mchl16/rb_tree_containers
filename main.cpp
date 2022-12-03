#include <iostream>
#include <set>
#include <map>
#include <random>
#include <vector>
#include <exception>

#include "rb_set.h"
#include "rb_multiset.h"
#include "rb_map.h"
#include "rb_multimap.h"
using namespace std;

int main(){
    std::random_device _rnd;
    std::mt19937 _rng{_rnd()};
    std::uniform_int_distribution<> _dis{0,std::numeric_limits<int>::max()};

    struct cmp{
        bool operator()(const int& a,const int& b) const{return a>b;}
    };
    // mchl16_rb_tree::set<int> t;
    mchl16_rb_tree::multimap<int,int> t;
    // std::multimap<int,int> t;
    vector<int> v;

    for (int i=1;i<=10;++i){
        t.insert({i,2*i});
        t.insert({i,3*i});
       // cout << t[i][0] << " " << t[i][1] << ", ";
       // t[i][1]=4*i;
       // cout << t[i][0] << " " << t[i][1] << "\n";
    }
    
    // int cnt=0;
    // for(int i=0;i<1000000;++i) if(t.contains(i)) ++cnt;
    // cout << cnt;
    
    for(auto i:t) i.second=5;
    for(auto i:t) cout << i.first << " " << i.second << "\n";

    // for (int i=0;i<10;++i) cout << t.count(i) << " "; cout << "\n";
}