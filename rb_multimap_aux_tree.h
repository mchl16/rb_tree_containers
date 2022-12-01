#ifndef MCHL16_RB_MULTIMAP_AUX
#define MCHL16_RB_MULTIMAP_AUX

#include "./tree/rb_multimap_aux_tree.h"
#include "./multimap_aux_tree/rb_multimap_aux_data_object.h"

namespace mchl16_rb_tree{
    template<typename T>
    using multimap_aux_tree= \
    rb_multimap_aux_tree<MultimapAuxDataObject<T>>;
}

#endif