#ifndef MCHL16_RB_MULTIMAP_DATA_OBJECT
#define MCHL16_RB_MULTIMAP_DATA_OBJECT

#include "../tree/rb_data_type.h"
#include "../tree/rb_multimap_aux_tree.h"
#include <functional>
#include <utility>

namespace mchl16_rb_tree{
    template<typename T,typename Comparer=std::less<T>>
    class MultimapDataObject{
        using KeyT=decltype(std::declval<T>().first);
        using ValT=decltype(std::declval<T>().second);

        public:
            class iterator;

        protected:
            const data_type<KeyT> _key;
            multimap_aux_tree<ValT> _vals;

        public:
            MapDataObject(const T& key) : _key(data_type<KeyT>(key.first)),_val(data_type<ValT>(key.second)){}

        public:
            size_t size() const{
                return _vals.size();
            }

            const KeyT& key() const{
                return _key.value();
            }
            
            static const KeyT& key(const T& val){
                return val.first;
            }

            static bool compare(const KeyT& a,const KeyT& b){
                return Comparer{}(a,b);
            }

            iterator begin(){
                return iterator(this->_vals.begin());
            }

            iterator rbegin(){
                return iterator(this->vals.rbegin());
            }

            bool insert(const T& val){
                return _vals.insert(val.second);
            }

            bool erase(const T& val){
                return _vals.erase(val.second);
            }
    };

    template<typename T,typename Comparer>
    class MultimapDataObject<T,Comparer>::iterator{ 
        const MultimapDataObject<T,Comparer> *obj;
        const rb_multimap_aux_tree::iterator pos;
        
        public:
            iterator(const MapDataObject<T,Comparer>& parent,\
            rb_multimap_aux_tree::iterator it) : obj(&parent),pos(it){}

        public:
            std::pair<const KeyT&,ValT&> operator*() const{
                return {obj->key(),*pos};
            }

            bool operator++(){
                return ++pos!=obj->_vals.end();
            }

            bool operator--(){
                return pos--!=obj->_vals.begin();
            }

            bool operator==(const iterator& it) const{
                return obj==it.obj ? pos==it.pos : false;
            }

    };
}

#endif
