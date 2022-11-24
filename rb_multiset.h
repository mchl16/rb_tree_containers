#include "./tree/rb_tree.h"
#include "./multiset/rb_multiset_data_object.h"

namespace mchl16_rb_tree{
    template<typename T,typename Comparer=std::less<T>>
    using multiset=rb_tree<MultisetDataObject<T,Comparer>>;
}