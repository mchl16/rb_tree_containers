#include <iostream>

namespace mchl16_rb_tree{
    template<typename DataObject>
    class rb_tree<DataObject>::rb_node{
        public:
            DataObject _data;

            rb_node *_children[2];

            rb_node*& _left(){
                return _children[0];
            }

            rb_node*& _right(){
                return _children[1];
            }

            rb_node *_prev,*_next;

            rb_node *_parent;

            bool _black;

        public:
            using T=typename DataObject::stored_type;
            using KeyT=decltype(std::declval<DataObject>().key());

            rb_node(rb_node* prev,rb_node* next,rb_node* parent,\
            const T& val,bool black=false) \
            : _data(DataObject(val)),_children{nullptr,nullptr}, \
            _prev(prev),_next(next),_parent(parent),_black(black){}

            rb_node(const T& val,bool black=false)\
             : rb_node(nullptr,nullptr,nullptr,val,black){}

            const KeyT& key() const{
                return _data.key();
            }

            rb_node *_rotate(const int dir){
                rb_node *_tmp=_children[dir^1];
                _tmp->_parent=_parent;
                _children[dir^1]=_tmp->_children[dir];
                if(_children[dir^1]) _children[dir^1]->_parent=this;
                _tmp->_children[dir]=this;
                
               if(_parent) _parent->_children[DataObject::compare(_parent->key(),key())]=_tmp;
                // if(_parent) _parent->_children[dir^1]=_tmp;
                _parent=_tmp;
                return _tmp;
            }

            void DFS(){
                std::cout << key() << " - entering (" << (_black ? "black" : "red")  << ")\n";
                
                if(_left()){
                    std::cout << key() << " - entering left\n";
                    _left()->DFS();
                }
                
                if(_right()){
                    std::cout << key() << " - entering right\n";
                    _right()->DFS();
                } 
                std::cout << key() << " - leaving\n";
            }

            
    };
}