#ifndef MCHL16_RB_MAP_TREE
#define MCHL16_RB_MAP_TREE

#include "rb_tree.h"
#include "rb_max_size.h"

namespace mchl16_rb_tree{
    template<typename DataObject>
    class rb_map_tree : public rb_tree<DataObject>{
        using T=decltype(*std::declval<DataObject>().begin());

        using KeyT=std::remove_const_t<std::remove_reference_t\
        <decltype(std::declval<DataObject>().key())>>;
        using ValT=std::remove_reference_t<decltype(std::declval<DataObject>().val())>;

        public:
            ValT& operator[](const KeyT& key){
                if(!this->_root){
                    std::pair<KeyT,ValT> xd=std::make_pair(key,ValT());
                    const KeyT& kek1=xd.first;
                    ValT& kek2=xd.second;
                    std::pair<const KeyT&,ValT&> xd2={kek1,kek2};

                    this->_root=this->_begin=this->_rbegin=\
                    new rb_tree<DataObject>::rb_node(xd2,true);

                    this->_size=1;
                    return this->_root->_data.val();
                }

                auto *pos=this->_root;
                typename rb_tree<DataObject>::rb_node *res;
                
                for(;;){ //fugly but I don't care
                    if(DataObject::compare(key,pos->key())){
                        if(pos->_left()) pos=pos->_left();
                        else{
                            std::pair<KeyT,ValT> xd=std::make_pair(key,ValT());
                            const KeyT& kek1=xd.first;
                            ValT& kek2=xd.second;
                            std::pair<const KeyT&,ValT&> xd2={kek1,kek2};

                            res=new rb_tree<DataObject>::rb_node\
                            (pos->_prev,pos,pos,xd2);

                            pos->_left()=res;
                            if(pos->_prev) pos->_prev->_next=res;
                            pos->_prev=res;
                            break;
                        }
                    }
                    else if(DataObject::compare(pos->key(),key)){
                        if(pos->_right()) pos=pos->_right();
                        else{
                            std::pair<KeyT,ValT> xd=std::make_pair(key,ValT());
                            const KeyT& kek1=xd.first;
                            ValT& kek2=xd.second;
                            std::pair<const KeyT&,ValT&> xd2={kek1,kek2};

                            res=new rb_tree<DataObject>::rb_node\
                            (pos,pos->_next,pos,xd2);

                            pos->_right()=res;
                            if(pos->_next) pos->_next->_prev=res;
                            pos->_next=res;
                            break;
                        }
                    }
                    else return pos->_data.val();
                }

                if(DataObject::compare(key,this->_begin->key())){
                    this->_begin=res;
                }
                if(DataObject::compare(this->_rbegin->key(),key)){
                    this->_rbegin=res;
                }

                ++this->_size;
                this->_root=this->_rebalance_insert(res);
                return res->_data.val();    
            }

    };
}

#endif