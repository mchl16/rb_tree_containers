#ifndef MCHL16_RB_MAP
#define MCHL16_RB_MAP

#include "./tree/rb_map_tree.h"
#include "./map/rb_map_data_object.h"

namespace mchl16_rb_tree{
    template<typename T,typename U,typename Comparer=std::less<T>>
    using map=rb_map_tree<MapDataObject<std::pair<T,U>,Comparer>>;
}

#endif