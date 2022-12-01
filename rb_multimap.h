#ifndef MCHL16_RB_MULTIMAP
#define MCHL16_RB_MULTIMAP

#include "./tree/rb_map_tree.h"
#include "./multimap/rb_multimap_data_object.h"

namespace mchl16_rb_tree{
    template<typename T,typename U,typename Comparer=std::less<T>>
    using multimap=rb_map_tree<MultimapDataObject<std::pair<T,U>,Comparer>>;
}

#endif