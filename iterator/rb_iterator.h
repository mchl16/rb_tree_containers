#ifndef MCHL16_RB_TREE_ITERATOR
#define MCHL16_RB_TREE_ITERATOR

#include "../tree/rb_tree_def.h"
#include "rb_iterator_base.h"

namespace mchl16_rb_tree{
    template<typename DataObject>
    class rb_tree<DataObject>::iterator : public rb_tree<DataObject>::iterator_base{
        public:
            iterator(rb_tree<DataObject>::rb_node* n,typename DataObject::iterator it) : iterator_base(n,it){}

            iterator(rb_tree<DataObject>::rb_node* n) : iterator_base(n){}

        public:
            iterator operator++(){
                rb_tree<DataObject>::iterator_base::move_next();
                return *this;
            }

            iterator operator++(int){
                iterator res=*this;
                rb_tree<DataObject>::iterator_base::move_next();
                return res;
            }

            iterator operator--(){
                rb_tree<DataObject>::iterator_base::move_prev();
                return *this;
            }

            iterator operator--(int){
                iterator res=*this;
                rb_tree<DataObject>::iterator_base::move_prev();
                return res;
            }
    };
}

#endif