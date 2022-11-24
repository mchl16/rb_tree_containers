#ifndef MCHL16_RB_SET
#define MCHL16_RB_SET

#include "./tree/rb_tree.h"
#include "./set/rb_set_data_object.h"

namespace mchl16_rb_tree{
    template<typename T,typename Comparer=std::less<T>>
    using set=rb_tree<SetDataObject<T,Comparer>>;
}

#endif