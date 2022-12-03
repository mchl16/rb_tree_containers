#ifndef MCHL16_RB_TREE_DEF
#define MCHL16_RB_TREE_DEF

#include <utility>
#include <functional>

namespace mchl16_rb_tree{
    template<typename DataObject>
    class rb_tree{
        using T=typename DataObject::stored_type;
        //using KeyT=decltype(std::declval<DataObject>().key());
        using KeyT=typename DataObject::KeyT;
        
        protected:
            class iterator_base;

        public:
            class iterator;
            class reverse_iterator;
            
            class rb_node;

        protected:
            rb_node *_root;

            rb_node *_begin,*_rbegin;

            size_t _size;

        public:
            rb_tree() : _root(nullptr),_begin(nullptr),_rbegin(nullptr),_size(0){}
            
            virtual ~rb_tree(){}

        public:
            iterator begin() const;
            iterator end() const;

            reverse_iterator rbegin() const;
            reverse_iterator rend() const;

            const iterator cbegin() const;
            const iterator cend() const;

            const reverse_iterator crbegin() const;
            const reverse_iterator crend() const;

            size_t size() const;
            bool empty() const;

            void clear();

            const iterator find(const KeyT& val) const;
            bool contains(const KeyT& val) const;
            const iterator lower_bound(const KeyT& val) const;
            const iterator upper_bound(const KeyT& val) const;
            std::pair<const iterator,const iterator> equal_range(const KeyT& val) const;

            size_t count(const KeyT& val) const;

            std::pair<const iterator,bool> insert(const T& val);
            iterator erase(const iterator& it);
            size_t erase(const KeyT& val);

            void DFS();

        protected:
            rb_node *_rebalance_insert(rb_node* init_pos);
            rb_node *_rebalance_erase(rb_node* init_pos);
    };
}

#endif