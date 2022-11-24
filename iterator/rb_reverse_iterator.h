#ifndef MCHL16_RB_TREE_REV_ITERATOR
#define MCHL16_RB_TREE_REV_ITERATOR

#include "../tree/rb_tree_def.h"
#include "rb_iterator_base.h"

namespace mchl16_rb_tree{
    template<typename DataObject>
    class rb_tree<DataObject>::reverse_iterator : public rb_tree<DataObject>::iterator_base{
        public:
            reverse_iterator(rb_tree<DataObject>::rb_node* n,typename DataObject::iterator it) : iterator_base(n,it){}

            reverse_iterator(rb_tree<DataObject>::rb_node* n) : iterator_base(n){}

        public:
            reverse_iterator operator--(){
                return rb_tree<DataObject>::iterator_base::move_next();
            }

            reverse_iterator operator--(int){
                iterator res=*this;
                rb_tree<DataObject>::iterator_base::move_next();
                return res;
            }

            reverse_iterator operator++(){
                return rb_tree<DataObject>::iterator_base::move_prev();
            }

            reverse_iterator operator++(int){
                iterator res=*this;
                rb_tree<DataObject>::iterator_base::move_prev();
                return res;
            }
    };
}

#endif