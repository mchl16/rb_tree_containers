#ifndef MCHL16_RB_MULTIMAP_AUX_TREE
#define MCHL16_RB_MULTIMAP_AUX_TREE

#include "rb_tree.h"
#include <bitset>

namespace mchl16_rb_tree{
    template<typename DataObject>
    class rb_multimap_aux_tree : public rb_tree<DataObject>{
        using T=DataObject::KeyT;
        using rb_node=typename rb_tree<DataObject>::rb_node;
        
        public:
            std::pair<typename rb_tree<DataObject>::iterator,bool> insert(const T& val,size_t index){
                typename rb_tree<DataObject>::rb_node *res=\
                new rb_tree<DataObject>::rb_node(val);

                if(!this->_root){
                    res->_black=true;
                    this->_begin=this->_rbegin=this->_root=res;
                    this->_size=1;
                    return std::make_pair(typename rb_tree<DataObject>::iterator(this->_root),true);
                }

                auto *pos=this->_root;

                if(index==0) this->_begin=res;
                if(index==this->_size) this->_rbegin=res;

                std::bitset<256> bs;
                int depth=0;
                for(;;++depth){
                    size_t n=pos->_left() ? pos->_left()->_data.subtree_size : 0;
                    ++pos->_data.subtree_size;

                    if(n>=index){
                        bs[depth]=true;
                        if(pos->_left()) pos=pos->_left();
                        else{
                            res->_parent=pos;
                            res->_prev=pos->_prev;
                            res->_next=pos;
                            pos->_left()=res;
                            if(pos->_prev) pos->_prev->_next=res;
                            pos->_prev=res;
                            break;
                        }
                    }
                    else if(pos->_right()){
                        //bs[depth]=true;
                        index-=(n+1);
                        pos=pos->_right();
                    }
                    else{
                        res->_parent=pos;
                        res->_prev=pos;
                        res->_next=pos->_next;
                        pos->_right()=res;
                        if(pos->_next) pos->_next->_prev=res;
                        pos->_next=res;
                        break;
                    }
                }

                ++this->_size;
                this->_root=this->_rebalance_insert(res,bs,depth);
                return std::make_pair(typename rb_tree<DataObject>::iterator(res),true);
            }

            T& operator[](size_t index){
                auto pos=this->_root;
                for(;;){
                    size_t n=pos->_left() ? pos->_left()->_data.subtree_size : 0;
                    if(n>index) pos=pos->_left();
                    else if(n==index) return pos->_data.key();
                    else if(pos->_right()){
                        index-=(n+1);
                        pos=pos->_right();
                    }
                    else throw new std::invalid_argument("Index out of range\n");  //is it really needed?
                }
            }

        protected:
            static rb_node *_rotate(rb_node *node,const int dir,const int parent_dir){
                rb_node *_tmp=node->_children[dir^1];
                _tmp->_parent=node->_parent;
                node->_children[dir^1]=_tmp->_children[dir];
                if(node->_children[dir^1]) node->_children[dir^1]->_parent=node;
                _tmp->_children[dir]=node;
                
                if(node->_parent) node->_parent->_children[parent_dir]=_tmp;
                node->_parent=_tmp;

                _tmp->_data.subtree_size=node->_data.subtree_size--;
                node->_data.subtree_size-=_tmp->_children[dir^1] ? \
                _tmp->_children[dir^1]->_data.subtree_size : 0;

                return _tmp;
            }

            typename rb_tree<DataObject>::rb_node*
            _rebalance_insert(typename rb_tree<DataObject>::rb_node* pos,std::bitset<256>& bs,int depth){
                typename rb_tree<DataObject>::rb_node *pos2;
                while(pos->_parent){
                    pos2=pos->_parent;
                    if(pos2->_black) return this->_root;
                    
                    
                    if(pos2->_parent) pos=pos2->_parent;
                    else{
                        pos2->_black=true;
                        return pos2;
                    }

                    const int s1=bs[depth--];
                    const int s2=bs[depth];
                    typename rb_tree<DataObject>::rb_node *uncle=pos->_children[s2];

                    if(!uncle || uncle->_black){
                        if(s1!=s2) pos2=_rotate(pos2,s1,s2^1); //inner child, an extra rotation is needed

                        pos->_black=false;
                        pos2->_black=true;

                        pos2=_rotate(pos,s2,depth ? bs[depth-1]^1 : 0);

                        return (pos2->_parent ? this->_root : pos2);
                    }
                    else{
                        pos->_black=false;
                        pos2->_black=true;
                        uncle->_black=true;
                    }
                    --depth;
                }
                pos->_black=true;
                return pos;
            }
    };
}

#endif