#ifndef MCHL16_RB_MULTIMAP_AUX_DATA_OBJECT
#define MCHL16_RB_MULTIMAP_AUX_DATA_OBJECT

#include "../tree/rb_data_type.h"
#include "../set/rb_set_data_object.h"
#include <functional>
#include <utility>

namespace mchl16_rb_tree{
    template<typename T>
    class MultimapAuxDataObject{
        public:
            class iterator;

        protected:
            data_type<T> _key;
            
        public:
            size_t subtree_size;

        public:
            MultimapAuxDataObject(const T& key) : _key(data_type<T>(key)),subtree_size(1){}

        public:
            typedef T stored_type;
            typedef T KeyT;

            size_t size() const{
                return 1;
            }

            static const T& key(const T& val){
                return val;
            }

            T& key() const{
                return _key.value();
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

    template<typename T>
    class MultimapAuxDataObject<T>::iterator{ //this one is quite quirky tbh
        const MultimapAuxDataObject<T> *obj;
        
        public:
            iterator(const MultimapAuxDataObject<T>& parent) : obj(&parent){}

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
