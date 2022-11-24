#ifndef MCHL16_RB_DATA_TYPE
#define MCHL16_RB_DATA_TYPE

#include "rb_max_size.h"
#include <cstring>

namespace mchl16_rb_tree{
    template<typename T>
    class data_type{
        T *_value=nullptr;    

        public:
            data_type(const T& key){
                if(sizeof(T)<=MAX_SIZE) memcpy(&_value,&key,sizeof(T));
                else _value=new T(key);
            }
            
            T& value() const{
                if(sizeof(T)<=MAX_SIZE){
                    return *const_cast<T*>(reinterpret_cast<const T*>(&_value)); //pathological
                }
                else return *_value;
            }

            const T& operator=(const T& val){
                if(sizeof(T)<=MAX_SIZE) memcpy(&_value,&val,sizeof(T));
                else _value=new T(val);
                return value();
            }

            const T& operator=(const T&& val){
                if(sizeof(T)<=MAX_SIZE) memcpy(&_value,&val,sizeof(T));
                else _value=&val;
                return value();
            }
    };  
}

#endif