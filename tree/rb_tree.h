#ifndef MCHL16_RB_TREE
#define MCHL16_RB_TREE

#include "rb_tree_def.h"
#include "rb_node.h"
#include "../iterator/rb_iterator.h"
#include "../iterator/rb_reverse_iterator.h"
#include <utility>

namespace mchl16_rb_tree{
    template<typename DataObject>
    typename rb_tree<DataObject>::iterator 
    rb_tree<DataObject>::begin() const{
        return iterator(_begin);
    }

    template<typename DataObject>
    typename rb_tree<DataObject>::iterator 
    rb_tree<DataObject>::end() const{
        return iterator(_rbegin->_next);
    }

    template<typename DataObject>
    typename rb_tree<DataObject>::reverse_iterator 
    rb_tree<DataObject>::rbegin() const{
        return iterator(_rbegin);
    }

    template<typename DataObject>
    typename rb_tree<DataObject>::reverse_iterator 
    rb_tree<DataObject>::rend() const{
        return iterator(_begin->_prev);
    }

    template<typename DataObject>
    const typename rb_tree<DataObject>::iterator 
    rb_tree<DataObject>::cbegin() const{
        return iterator(_begin);
    }

    template<typename DataObject>
    const typename rb_tree<DataObject>::iterator 
    rb_tree<DataObject>::cend() const{
        return iterator(_rbegin->_next);
    }

    template<typename DataObject>
    const typename rb_tree<DataObject>::reverse_iterator 
    rb_tree<DataObject>::crbegin() const{
        return iterator(_rbegin);
    }

    template<typename DataObject>
    const typename rb_tree<DataObject>::reverse_iterator 
    rb_tree<DataObject>::crend() const{
        return iterator(_begin->_prev);
    }

    template<typename DataObject>
    size_t rb_tree<DataObject>::size() const{
        return _size;
    }

    template<typename DataObject>
    bool rb_tree<DataObject>::empty() const{
        return _size==0;
    }

    template<typename DataObject>
    void rb_tree<DataObject>::clear(){
        delete _root;
        _size=0;
    }

    template<typename DataObject>
    const typename rb_tree<DataObject>::iterator
    rb_tree<DataObject>::find(const KeyT& val) const{
        auto pos=_root;
        while(pos){
            if(DataObject::compare(DataObject::key(val),pos->key())) pos=pos->_left();
            else if(DataObject::compare(pos->key(),DataObject::key(val))) pos=pos->_right();
            else return iterator(pos);
        }
        return cend();
    }

    template<typename DataObject>
    size_t rb_tree<DataObject>::count(const KeyT& val) const{
        auto pos=_root;
        while(pos){
            if(DataObject::compare(DataObject::key(val),pos->key())) pos=pos->_left();
            else if(DataObject::compare(pos->key(),DataObject::key(val))) pos=pos->_right();
            else return pos->_data.size();
        }
        return 0;
    }

    template<typename DataObject>
    bool rb_tree<DataObject>::contains(const KeyT& val) const{
        return find(val)!=cend();
    }

    template<typename DataObject>
    const typename rb_tree<DataObject>::iterator 
    rb_tree<DataObject>::lower_bound(const KeyT& val) const{
        auto pos=_root;
        while(pos){
            if(DataObject::compare(DataObject::key(val),pos->key())){
                if(pos->_left()) pos=pos->_left();
                else return pos;
            }
            else if(DataObject::compare(pos->key(),DataObject::key(val))){
                if(pos->_right()) pos=pos->_right();
                else return pos->_next;
            }
            else return iterator(pos);
        }
        return cend();
    }

    template<typename DataObject>
    const typename rb_tree<DataObject>::iterator 
    rb_tree<DataObject>::upper_bound(const KeyT& val) const{
        auto pos=_root;
        while(pos){
            if(DataObject::compare(DataObject::key(val),pos->key())){
                if(pos->_left()) pos=pos->_left();
                else return pos;
            }
            else if(DataObject::compare(pos->key(),DataObject::key(val))){
                if(pos->_right()) pos=pos->_right();
                else return pos->_next;
            }
            else return iterator(pos->_next);
        }
        return cend();
    }

    template<typename DataObject>
    std::pair<const typename rb_tree<DataObject>::iterator,bool> 
    rb_tree<DataObject>::insert(const T& val){
        if(!_root){
            _root=_begin=_rbegin=new rb_tree<DataObject>::rb_node(val,true);
            _size=1;
            return std::make_pair(rb_tree<DataObject>::iterator(_root),true);
        }

        auto *pos=_root;
        rb_tree<DataObject>::rb_node *res;
        
        for(;;){ //fugly but I don't care
            if(DataObject::compare(DataObject::key(val),pos->key())){
                if(pos->_left()) pos=pos->_left();
                else{
                    res=new rb_tree<DataObject>::rb_node(pos->_prev,pos,pos,val);
                    pos->_left()=res;
                    if(pos->_prev) pos->_prev->_next=res;
                    pos->_prev=res;
                    break;
                }
            }
            else if(DataObject::compare(pos->key(),DataObject::key(val))){
                if(pos->_right()) pos=pos->_right();
                else{
                    res=new rb_tree<DataObject>::rb_node(pos,pos->_next,pos,val);
                    pos->_right()=res;
                    if(pos->_next) pos->_next->_prev=res;
                    pos->_next=res;
                    break;
                }
            }
            else{
                bool f=pos->_data.insert(val);
                _size+=f;
                return std::make_pair(rb_tree<DataObject>::iterator(pos,pos->_data.rbegin()),f);
            }
        }

        if(DataObject::compare(DataObject::key(val),_begin->key())) _begin=res;
        if(DataObject::compare(_rbegin->key(),DataObject::key(val))) _rbegin=res;
        ++_size;
        _root=_rebalance_insert(res);
        return std::make_pair(rb_tree<DataObject>::iterator(res),true);
    }

    template<typename DataObject>
    typename rb_tree<DataObject>::rb_node*
    rb_tree<DataObject>::_rebalance_insert(rb_tree<DataObject>::rb_node* pos){
        rb_node *pos2;
        while(pos->_parent){
            pos2=pos->_parent;
            if(pos2->_black) return _root;
            const int s1=DataObject::compare(pos->key(),pos2->key());
            
            if(pos2->_parent) pos=pos2->_parent;
            else{
                pos2->_black=true;
                return pos2;
            }

            const int s2=DataObject::compare(pos2->key(),pos->key());

            rb_node *uncle=pos->_children[s2];
            if(!uncle || uncle->_black){
                if(s1!=s2){
                    pos2=pos2->_rotate(static_cast<typename rb_node::Direction>(s1)); //inner child, an extra rotation is needed
                }
                pos->_black=false;
                pos2->_black=true;
                pos2=pos->_rotate(static_cast<typename rb_node::Direction>(s2));
                return (pos2->_parent ? _root : pos2);
            }
            else{
                pos->_black=false;
                pos2->_black=true;
                uncle->_black=true;
            }
        }
        pos->_black=true;
        return pos;
    }

    template<typename DataObject>
    void rb_tree<DataObject>::DFS(){ //to be removed 
            
        _root->DFS();
    }
}

#endif