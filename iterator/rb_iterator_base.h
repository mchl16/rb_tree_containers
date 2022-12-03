#ifndef MCHL16_RB_ITERATOR_BASE
#define MCHL16_RB_ITERATOR_BASE


#include "../tree/rb_tree_def.h"

namespace mchl16_rb_tree{
    template<typename DataObject>
    class rb_tree<DataObject>::iterator_base{
        protected:
            rb_tree<DataObject>::rb_node *node;

            typename DataObject::iterator pos;

        protected:
            iterator_base(rb_tree<DataObject>::rb_node *n,typename DataObject::iterator it) : node(n),pos(it){}

            iterator_base(rb_tree<DataObject>::rb_node *n) : node(n),pos(n->_data.begin()){}

        public:
            typedef typename DataObject::iterator_type T;
            T operator*() const{
                return *pos;
            }

            T operator->() const{
                return *pos;
            }

        protected:
            void move_next(){
                if(++pos){
                    node=node->_next;
                    if(node) pos=node->_data.begin();
                }
            }

            void move_prev(){
                if(--pos){
                    node=node->_prev;
                    if(node) pos=node->_data.rbegin();
                }
            }

        public:
            bool operator==(const iterator_base& it) const{
                if(node==it.node){
                    return node ? pos==it.pos : true;
                }
                else return false;
            }

            bool operator!=(const iterator_base& it) const{
                return !(*this==it);
            }
    };
}

#endif