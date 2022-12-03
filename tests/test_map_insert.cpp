#include <random>
#include <map>
#include "../rb_map.h"

constexpr int n=3000000;

/** 
 * Random insertion test
*/

int main(){
    std::map<int,int> s1;
    mchl16_rb_tree::map<int,int> s2;

    std::random_device _rnd;
    std::mt19937 _rng{_rnd()};
    std::uniform_int_distribution<> _dis{0,std::numeric_limits<int>::max()};

    for(int i=0;i<n;++i){
        auto x=_dis(_rng);
        s1.insert({x,i});
        s2.insert({x,i});
        s1.insert({x,x});
        s2.insert({x,x});
    }

    auto it=s1.begin();
    auto jt=s2.begin();
    for(;it!=s1.end();++it,++jt){
        if(it->first!=jt->first || it->second!=jt->second) exit(1);
    }

    for(int i=0;i<n;++i){
        auto x=_dis(_rng);
        s1.insert({x,x});
        s2.insert({x,x});
    }

    auto it=s1.begin();
    auto jt=s2.begin();
    for(;it!=s1.end();++it,++jt){
        if(it->first!=jt->first || it->second!=jt->second) exit(1);
    }
    exit(0);
}