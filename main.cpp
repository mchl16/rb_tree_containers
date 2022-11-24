#include <iostream>
#include <set>
#include <map>
#include <random>

#include "rb_set.h"
#include "rb_multiset.h"
#include "rb_map.h"
using namespace std;

int main(){
    std::random_device _rnd;
    std::mt19937 _rng{_rnd()};
    std::uniform_int_distribution<> _dis{0,std::numeric_limits<int>::max()};

    struct cmp{
        bool operator()(const int& a,const int& b) const{return a>b;}
    };
    //std::map<int,int> t;
    mchl16_rb_tree::map<int,int,cmp> t;
    for (int i=1;i<=10;++i){
       // cout << i << endl;
       // t.insert({i,i});
       // ++t[i];
       t[i]^=5;
       ++t[i];
    }

    
    // int cnt=0;
    // for(int i=0;i<1000000;++i) if(t.contains(i)) ++cnt;
    // cout << cnt;

    for(auto i:t) cout << i.first << " " << i.second << "\n";

    // for (int i=0;i<10;++i) cout << t.count(i) << " "; cout << "\n";
}