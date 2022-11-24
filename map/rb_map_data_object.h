#ifndef MCHL16_RB_MAP_DATA_OBJECT
#define MCHL16_RB_MAP_DATA_OBJECT

#include "../tree/rb_data_type.h"
#include <functional>
#include <utility>

namespace mchl16_rb_tree{
    template<typename T,typename Comparer=std::less<T>>
    class MapDataObject{
        using KeyT=decltype(std::declval<T>().first);
        using ValT=decltype(std::declval<T>().second);

        public:
            class iterator;

        protected:
            const data_type<KeyT> _key;
            data_type<ValT> _val;

        public:
            MapDataObject(const T& key) : _key(data_type<KeyT>(key.first)),_val(data_type<ValT>(key.second)){}

        public:
            size_t size() const{
                return 1;
            }

            const KeyT& key() const{
                return _key.value();
            }
            
            static const KeyT& key(const T& val){
                return val.first;
            }

            ValT& val() const{
                return _val.value();
            }

            static bool compare(const KeyT& a,const KeyT& b){
                return Comparer{}(a,b);
            }

            iterator begin(){
                return iterator(*this);
            }

            iterator rbegin(){
                return iterator(*this);
            }

            bool insert(const T& val,const bool replace=false){
                if(replace) _val.value()=val.second;
                return false;
            }

            bool erase(const T& val){
                return true;
            }
    };

    template<typename T,typename Comparer>
    class MapDataObject<T,Comparer>::iterator{ //this one is quite quirky tbh
        const MapDataObject<T,Comparer> *obj;
        
        public:
            iterator(const MapDataObject<T,Comparer>& parent) : obj(&parent){}

        public:
            std::pair<const KeyT&,ValT&> operator*() const{
                return {obj->key(),obj->val()};
            }

            bool operator++(){
                return true;
            }

            bool operator--(){
                return true;
            }

            bool operator==(const iterator& it) const{
                return obj==it.obj;
            }

    };
}

#endif
