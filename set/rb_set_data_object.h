#ifndef MCHL16_RB_SET_DATA_OBJECT
#define MCHL16_RB_SET_DATA_OBJECT

#include "../tree/rb_data_type.h"
#include <functional>
#include <utility>

namespace mchl16_rb_tree{
    template<typename T,typename Comparer=std::less<T>>
    class SetDataObject{
        public:
            class iterator;

        protected:
            const data_type<T> _key;

        public:
            SetDataObject(const T& key) : _key(data_type<T>(key)){}

        public:
            typedef T stored_type;
            typedef T KeyT;

            size_t size() const{
                return 1;
            }

            static const T& key(const T& val){
                return val;
            }

            const T& key() const{
                return _key.value();
            }

            static bool compare(const T& a,const T& b){
                return Comparer{}(a,b);
            }

            iterator begin(){
                return iterator(*this);
            }

            iterator rbegin(){
                return iterator(*this);
            }

            bool insert(const T& val){
                return false;
            }

            bool erase(const T& val){
                return true;
            }
    };

    template<typename T,typename Comparer>
    class SetDataObject<T,Comparer>::iterator{ //this one is quite quirky tbh
        const SetDataObject<T,Comparer> *obj;
        
        public:
            iterator(const SetDataObject<T,Comparer>& parent) : obj(&parent){}

        public:
            const T& operator*() const{
                return obj->key();
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
