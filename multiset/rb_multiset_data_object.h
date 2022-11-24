#ifndef MCHL16_RB_MULTISET_DATA_OBJECT
#define MCHL16_RB_MULTISET_DATA_OBJECT

#include "../tree/rb_data_type.h"
#include <functional>
#include <utility>

namespace mchl16_rb_tree{
    template<typename T,typename Comparer=std::less<T>>
    class MultisetDataObject{
        public:
            class iterator;

        protected:
            const data_type<T> _key;
            size_t _size;

        public:
            MultisetDataObject(const T& key) : _key(data_type<T>(key)),_size(1){}

        public:
            size_t size() const{
                return _size;
            }

            const T& key() const{
                return _key.value();
            }
            
            static const T& key(const T& val){
                return val;
            }

            static bool compare(const T& a,const T& b){
                return Comparer{}(a,b);
            }

            iterator begin(){
                return iterator(*this,0);
            }

            iterator rbegin(){
                return iterator(*this,_size-1);
            }

            bool insert(const T& val){
                ++_size;
                return true;
            }

            bool erase(const T& val){
                return --size==0;
            }
    };

    template<typename T,typename Comparer>
    class MultisetDataObject<T,Comparer>::iterator{ //this one is quite quirky tbh
        const MultisetDataObject<T,Comparer> *obj;
        size_t offset;

        public:
            iterator(const MultisetDataObject<T,Comparer>& parent,size_t off) : obj(&parent),offset(off){}

        public:
            const T& operator*() const{
                return obj->key();
            }

            bool operator++(){
                return ++offset==obj->_size;
            }

            bool operator--(){
                return --offset==-1;
            }

            bool operator==(const iterator& it) const{
                return ((obj==it.obj) && (offset==it.offset));
            }
    };
}

#endif