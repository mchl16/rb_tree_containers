#include "rb_data_type.h"

namespace mchl16_rb_tree{
    template<typename T,typename ValueObject>
    class DataObject{
        public:
            class iterator;

        protected:
            data_type<T> _key;

            ValueObject _val;

        public:
            size_t size() const{
                return _val.size();
            }

            const T& operator[](size_t k) const{
                return _val[k];
            }

            static bool compare(const T& a,const T& b){
                return _val.compare(a,b);
            }
    };

    template<typename T,typename ValueObject>
    class DataObject<T,ValueObject>::iterator{ //this one is quite quirky tbh
        protected:
            void *_value; 

        
    };
}


