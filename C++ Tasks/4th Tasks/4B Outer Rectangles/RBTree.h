#pragma once

#include <functional>

#include "Segment.h"


template <class Compare = std::less<Segment>>
class RBTree
{
public:
    enum class Color { Red, Black };

    struct Node
    {
        Segment* key;
        Node* parent;
        Node* L = nullptr, * R = nullptr;
        Color color;
    };

    class ForwardIterator
    {
        friend class RBTree;

    public:
        bool operator==(const ForwardIterator& rhs) { return node_cur == rhs.node_cur; }

    private:
        Node* node_cur, *node_last;
    };

    void Insert(const Segment& _key);
    void DeleteNode(ForwardIterator _it);

    ForwardIterator Find(const Segment& key);

    ForwardIterator Get_end_it() const;

    ~RBTree();

    Node* root = nullptr;
    Compare compare_ = Compare{};

private:
    size_t size = 0;

    void Insert_case(Node* _node);

    Node* GetMin(Node* _node = nullptr);
    Node* GetMax(Node* _node = nullptr);

    Node* Get_next_node(Node* _node);
    Node* Get_prev_node(Node* _node);

    void Delete_node(Node* _node);
    void Delete_nodes_child(Node* _node);
    void Delete_next_node_for_child(Node* _node);

    Color GetÑolor(Node* _node)
    {
        if (_node)
            return _node->color;

        return Color::Black;
    }

    Node* Get_node_bro(Node* _node);

    Node* Get_grandparent(Node* _node);

    void Rotate_L(Node* _node);
    void Rotate_R(Node* node);
    void Destruct_nodes(Node* _node);
};

template <class Compare>
typename RBTree<Compare>::ForwardIterator
RBTree<Compare>::Find(const Segment& key)
{
    Node* node = root;

    while (node) 
    {
        if (compare_(key, *node->key))
            node = node->L;
        else 
        {
            if (compare_(*node->key, key))
                node = node->R;
            else
                break;
        }
    }

    if (!node)
        return Get_end_it();

    ForwardIterator it{};
    it.node_cur = node;
    it.node_last = it.node_cur->L;

    return it;
}

template <class Compare>
typename RBTree<Compare>::ForwardIterator
RBTree<Compare>::Get_end_it() const
{
    ForwardIterator it;
    it.node_cur = nullptr;
    it.node_last = nullptr;

    return it;
}

template<class Compare>
RBTree<Compare>::~RBTree()
{
    Destruct_nodes(root);
    root = nullptr;
}

template<class Compare>
void RBTree<Compare>::Insert_case(Node* _node)
{
    if (!_node->parent)
        _node->color = Color::Black;
    else
    {
        if (_node->parent->color == Color::Black)
            return;

        Node* grandparent = Get_grandparent(_node);
        Node* uncle;

        if (!grandparent)
            uncle = nullptr;
        else
        {
            if (_node->parent == grandparent->L)
                uncle = grandparent->R;
            else
                uncle = grandparent->L;
        }

        if (uncle && uncle->color == Color::Red)
        {
            _node->parent->color = Color::Black;
            uncle->color = Color::Black;
            grandparent = Get_grandparent(_node);
            grandparent->color = Color::Red;

            Insert_case(grandparent);
        }
        else
        {
            grandparent = Get_grandparent(_node);

            if ((_node == _node->parent->R) && (_node->parent == grandparent->L))
            {
                Rotate_L(_node->parent);
                _node = _node->L;
            }
            else
            {
                if ((_node == _node->parent->L) && (_node->parent == grandparent->R))
                {
                    Rotate_R(_node->parent);
                    _node = _node->R;
                }
            }

            grandparent = Get_grandparent(_node);

            _node->parent->color = Color::Black;
            grandparent->color = Color::Red;

            if ((_node == _node->parent->L) && (_node->parent == grandparent->L))
                Rotate_R(grandparent);
            else
                Rotate_L(grandparent);
        }
    }
}


template <class Compare>
typename RBTree<Compare>::Node*
RBTree<Compare>::GetMin(Node* _node)
{
    if (!_node)
        _node = root;

    while (_node->L)
        _node = _node->L;

    return _node;
}

template <class Compare>
typename RBTree<Compare>::Node*
RBTree<Compare>::GetMax(Node* _node)
{
    if (!_node)
        _node = root;

    while (_node->R)
        _node = _node->R;

    return _node;
}

template <class Compare>
typename RBTree<Compare>::Node*
RBTree<Compare>::Get_next_node(Node* _node)
{
    if (_node->R)
        return GetMin(_node->R);

    while (_node->parent && _node == _node->R)
        _node = _node->parent;

    return _node->parent;
}

template <class Compare>
typename RBTree<Compare>::Node*
RBTree<Compare>::Get_prev_node(Node* _node)
{
    if (_node->L)
        return GetMax(_node->L);

    while (_node->parent && _node == _node->L)
        _node = _node->parent;

    return _node->parent;
}

template<class Compare>
void RBTree<Compare>::Insert(const Segment& _key)
{
    Node* parent = root;
    bool is_parent_founded = false;

    while (parent && !is_parent_founded)
    {
        if (compare_(_key, *parent->key) && parent->L)
            parent = parent->L;
        else
        {
            if (!compare_(_key, *parent->key) && parent->R)
                parent = parent->R;
            else
                is_parent_founded = true;
        }
    }

    Node* _node = new Node{ new Segment{_key}, parent, nullptr, nullptr, Color::Red };

    if (parent)
    {
        if (compare_(_key, *parent->key) == true)
            parent->L = _node;
        else
            parent->R = _node;
    }
    else
        root = _node;

    Insert_case(_node);
    ++size;
}

template<class Compare>
void RBTree<Compare>::DeleteNode(ForwardIterator _it)
{
    Delete_node(_it.node_cur);
}

template<class Compare>
void RBTree<Compare>::Delete_node(Node* _node)
{
    if (!_node)
        return;

    if (size == 1)
    {
        if (root)
        {
            delete root->key;
            delete root;
        }

        root = nullptr;
    }
    else
    {
        if (_node->L || _node->R)
        {
            Node* new_node;
            if (_node->R)
                new_node = Get_next_node(_node);
            else
                new_node = Get_prev_node(_node);

            std::swap(_node->key, new_node->key);

            _node = new_node;
        }

        Delete_nodes_child(_node);
    }

    --size;
}

template<class Compare>
void RBTree<Compare>::Delete_nodes_child(Node* _node)
{
    Node* child;
    if (_node->L)
        child = _node->L;
    else
        child = _node->R;

    bool is_dummy_child_created = false;
    if (!child)
    {
        child = new Node{ nullptr, _node, nullptr, nullptr, Color::Black };
        is_dummy_child_created = true;
    }

    child->parent = _node->parent;

    if (_node == _node->parent->L)
        _node->parent->L = child;
    else
        _node->parent->R = child;

    if (_node->color == Color::Black)
    {
        if (child->color == Color::Red)
            child->color = Color::Black;
        else
        {
            if (child->parent)
                Delete_next_node_for_child(child);
        }
    }

    if (_node)
    {
        delete _node->key;
        delete _node;
    }

    if (is_dummy_child_created)
    {
        if (child == child->parent->L)
            child->parent->L = nullptr;
        else
            child->parent->R = nullptr;

        delete child;
    }
}

template<class Compare>
void RBTree<Compare>::Delete_next_node_for_child(Node* _node)
{
    Node* sibling = Get_node_bro(_node);

    if (sibling->color == Color::Red)
    {
        _node->parent->color = Color::Red;
        sibling->color = Color::Black;
        if (_node == _node->parent->L)
            Rotate_L(_node->parent);
        else
            Rotate_R(_node->parent);
    }

    sibling = Get_node_bro(_node);


    if (_node->parent->color == Color::Black && sibling->color == Color::Black && GetÑolor(sibling->L) == Color::Black && GetÑolor(sibling->R) == Color::Black)
    {
        sibling->color = Color::Red;

        if (_node->parent->parent)
            Delete_next_node_for_child(_node->parent);
    }
    else
    {
        sibling = Get_node_bro(_node);

        Color sibling_color_L = GetÑolor(sibling->L);
        Color sibling_color_R = GetÑolor(sibling->R);
        if (_node->parent->color == Color::Red && sibling->color == Color::Black && sibling_color_L == Color::Black && sibling_color_R == Color::Black)
        {
            sibling->color = Color::Red;
            _node->parent->color = Color::Black;
        }
        else
        {
            sibling = Get_node_bro(_node);

            if (sibling->color == Color::Black)
            {
                sibling_color_L = GetÑolor(sibling->L);
                sibling_color_R = GetÑolor(sibling->R);
                if (_node == _node->parent->L && sibling_color_R == Color::Black && sibling_color_L == Color::Red)
                {
                    sibling->color = Color::Red;

                    if (sibling->L)
                        sibling->L->color = Color::Black;

                    Rotate_R(sibling);
                }
                else
                {
                    sibling_color_L = GetÑolor(sibling->L);
                    sibling_color_R = GetÑolor(sibling->R);
                    if (_node == _node->parent->R && sibling_color_L == Color::Black && sibling_color_R == Color::Red)
                    {
                        sibling->color = Color::Red;

                        if (sibling->R)
                            sibling->R->color = Color::Black;

                        Rotate_L(sibling);
                    }
                }
            }

            sibling = Get_node_bro(_node);

            sibling->color = _node->parent->color;
            _node->parent->color = Color::Black;

            if (_node == _node->parent->L)
            {
                if (sibling->R)
                    sibling->R->color = Color::Black;

                Rotate_L(_node->parent);
            }
            else
            {
                if (sibling->L)
                    sibling->L->color = Color::Black;

                Rotate_R(_node->parent);
            }
        }
    }
}

template <class Compare>
typename RBTree<Compare>::Node*
RBTree<Compare>::Get_node_bro(Node* _node)
{
    if (_node == _node->parent->L)
        return _node->parent->R;

    return _node->parent->L;
}

template <class Compare>
typename RBTree<Compare>::Node*
RBTree<Compare>::Get_grandparent(Node* _node)
{
    if (_node && _node->parent)
        return _node->parent->parent;

    return nullptr;
}

template<class Compare>
void RBTree<Compare>::Rotate_L(Node* _node)
{
    auto pivot = _node->R;

    pivot->parent = _node->parent;
    if (_node->parent)
    {
        if (_node->parent->L == _node)
            _node->parent->L = pivot;
        else
            _node->parent->R = pivot;
    }

    _node->R = pivot->L;
    if (pivot->L)
        pivot->L->parent = _node;

    _node->parent = pivot;
    pivot->L = _node;

    if (_node == root)
        root = pivot;
}

template<class Compare>
void RBTree<Compare>::Rotate_R(Node* node)
{
    Node* pivot = node->L;

    pivot->parent = node->parent;
    if (node->parent)
    {
        if (node->parent->L == node)
            node->parent->L = pivot;
        else
            node->parent->R = pivot;
    }

    node->L = pivot->R;
    if (pivot->R)
        pivot->R->parent = node;

    node->parent = pivot;
    pivot->R = node;

    if (node == root)
        root = pivot;
}

template<class Compare>
void RBTree<Compare>::Destruct_nodes(Node* _node)
{
    if (_node)
    {
        Destruct_nodes(_node->L);
        Destruct_nodes(_node->R);

        if (_node)
        {
            delete _node->key;
            delete _node;
        }
    }
}
