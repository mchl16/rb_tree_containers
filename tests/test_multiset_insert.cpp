#include <random>
#include <set>
#include "../rb_multiset.h"

constexpr int n=3000000;

/** 
 * Random insertion test
*/

int main(){
    std::multiset<int> s1;
    mchl16_rb_tree::multiset<int> s2;

    std::random_device _rnd;
    std::mt19937 _rng{_rnd()};
    std::uniform_int_distribution<> _dis{0,std::numeric_limits<int>::max()};

    for(int i=0;i<n;++i){
        auto x=_dis(_rng);
        s1.insert(x);
        s2.insert(x);
    }

    auto it=s1.begin();
    auto jt=s2.begin();
    for(;it!=s1.end();++it,++jt){
        if(*it!=*jt) exit(1);
    }
    exit(0);
}