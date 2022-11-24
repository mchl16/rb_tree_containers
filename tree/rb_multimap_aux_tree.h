#ifndef MCHL16_RB_MULTIMAP_AUX_TREE
#define MCHL16_RB_MULTIMAP_AUX_TREE

namespace mchl16_rb_tree{
    template<typename DataObject>
    class rb_multimap_aux_tree : public rb_tree<DataObject>{
        using KeyT=std::remove_const_t<std::remove_reference_t\
        <decltype(std::declval<DataObject>().key())>>;

        public:
            pair<iterator,bool> insert(const KeyT& val,size_t index){
                if(!_root){
                    this->_root=this->_begin=this->_rbegin=\
                    new rb_tree<DataObject>::rb_node(val,true);

                    this->_size=1;
                    return std::make_pair(rb_tree<DataObject>::iterator(_root),true);
                }

                auto *pos=_root;
                rb_tree<DataObject>::rb_node *res;

                for(;;){
                    int n=pos->_left ? _pos->_left->_data.size() : 0;
                    if(n<=pos->_data.index){
                        if(pos->_left()) pos=pos->_left();
                        else{
                            res=new rb_tree<DataObject>::rb_node(pos->_prev,pos,pos,val);
                            pos->_left()=res;
                            if(pos->_prev) pos->_prev->_next=res;
                            pos->_prev=res;
                            break;
                        }
                    }
                    else if(pos->_right()){
                        index-=n;
                        pos=pos->_right();
                    }
                    else{
                        res=new rb_tree<DataObject>::rb_node(pos,pos->_next,pos,val);
                        pos->_right()=res;
                        if(pos->_next) pos->_next->_prev=res;
                        pos->_next=res;
                        break;
                    }
                }

                if(DataObject::compare(DataObject::key(val),this->_begin->key())){
                    this->_begin=res;
                }
                if(DataObject::compare(this->_rbegin->key(),DataObject::key(val))){
                    this->_rbegin=res;
                }
                ++_size;
                _root=_rebalance_insert(res);
                return std::make_pair(rb_tree<DataObject>::iterator(res),true);
            }

            const T& operator[](const size_t& index){
                auto pos=_root;
                for(;;){
                    int n=pos->_left ? _pos->_left->_data.size() : 0;
                    if(n<index) pos=pos->_left();
                    else if(n==index) return pos->_key();
                    else if(pos->_right()){
                        index-=n;
                        pos=pos->_right();
                    }
                    else throw new std::invalid_argument("Index out of range\n");
                }
            }

            
    };
}

#endif