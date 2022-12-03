#ifndef MCHL16_RB_MULTIMAP_DATA_OBJECT
#define MCHL16_RB_MULTIMAP_DATA_OBJECT

#include "../tree/rb_data_type.h"
#include "../rb_multimap_aux_tree.h"
#include <functional>
#include <utility>

namespace mchl16_rb_tree{
    template<typename T,typename Comparer=std::less<T>>
    class MultimapDataObject{
        public:
            using KeyT=decltype(std::declval<T>().first);
            using ValT=decltype(std::declval<T>().second);

        public:
            class iterator;

        protected:
            const data_type<KeyT> _key;
            rb_multimap_aux_tree<MultimapAuxDataObject<ValT>> _vals;

        public:
            MultimapDataObject(const T& key) : _key(data_type<KeyT>(key.first)),\
            _vals(rb_multimap_aux_tree<MultimapAuxDataObject<ValT>>()){
                _vals.insert(key.second,0);
            }

        public:
            typedef T stored_type;
            typedef std::pair<const KeyT&,ValT&> iterator_type;

            size_t size() const{
                return _vals.size();
            }

            const KeyT& key() const{
                return _key.value();
            }
            
            static const KeyT& key(const T& val){
                return val.first;
            }

            rb_multimap_aux_tree<MultimapAuxDataObject<ValT>>& val(){
                return _vals;
            }

            static bool compare(const KeyT& a,const KeyT& b){
                return Comparer{}(a,b);
            }

            iterator begin(){
                return iterator(this,this->_vals.begin());
            }

            iterator rbegin(){
                return iterator(this, \
                (typename rb_multimap_aux_tree<MultimapAuxDataObject<ValT>>::iterator) \
                this->_vals.rbegin());
            }

            bool insert(const T& val){
                return _vals.insert(val.second,_vals.size()).second;
            }

            bool erase(const T& val){
                return _vals.erase(val.second);
            }
    };

    template<typename T,typename Comparer>
    class MultimapDataObject<T,Comparer>::iterator{ 
        const MultimapDataObject<T,Comparer> *obj;

        using KeyT=MultimapDataObject<T,Comparer>::KeyT;

        using ValT=MultimapDataObject<T,Comparer>::ValT;

        typename rb_multimap_aux_tree<MultimapAuxDataObject<ValT>>::iterator pos; 
        
        public:
            iterator(const MultimapDataObject<T,Comparer> *parent,\
            typename rb_multimap_aux_tree<MultimapAuxDataObject<ValT>>::iterator it) : obj(parent),pos(it){}

        public:
            std::pair<const KeyT&,ValT&> operator*() const{
                return std::pair<const KeyT&,ValT&>(obj->key(),*pos);
                /*
                const KeyT& a=obj->key();
                ValT& b=const_cast<ValT&>(*pos);
                return {a,b};
                */
            }

            bool operator++(){
                return ++pos==obj->_vals.end();
            }

            bool operator--(){
                return pos--==obj->_vals.begin();
            }

            bool operator==(const iterator& it) const{
                return obj==it.obj ? pos==it.pos : false;
            }

    };
}

#endif
