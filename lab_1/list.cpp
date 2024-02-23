#include "list.h"
#include <stdexcept>

template<class T>
list<T>::node::node(T item)
{
    this->item = item;
}

template<class T>
T list<T>::iterator::operator*()
{
    return this->cur_node->item;
}

template<class T>
list<T>::iterator::iterator(const list<T> *plist)
{
    this->plist = plist;
    cur_node = plist->beg_node;
}

template<class T>
typename list<T>::iterator list<T>::iterator::operator++()
{
    iterator temp = *this;
    cur_node = cur_node->next;
    return temp;
}

template<class T>
typename list<T>::iterator list<T>::iterator::operator++(int)
{
    cur_node = cur_node->next;
    return *this;
}

template<class T>
typename list<T>::iterator list<T>::iterator::operator--()
{
    iterator temp = *this;
    cur_node = cur_node->previous;
    return temp;
}

template<class T>
typename list<T>::iterator list<T>::iterator::operator--(int)
{
    cur_node = cur_node->previous;
    return *this;
}

template<class T>
bool list<T>::iterator::operator==(list<T>::iterator iter)
{
    return this->cur_node == iter.cur_node;
}

template<class T>
bool list<T>::iterator::operator!=(list<T>::iterator iter)
{
    return this->cur_node != iter.cur_node;
}

template<class T>
list<T>::reverse_iterator::reverse_iterator(const list<T> *plist)
{
    this->plist = plist;
    cur_node = plist->beg_node->previous;
}

template<class T>
T list<T>::reverse_iterator::operator*()
{
    return this->cur_node->item;
}

template<class T>
typename list<T>::reverse_iterator list<T>::reverse_iterator::operator++()
{
    list<T>::reverse_iterator temp = *this;
    cur_node = cur_node->previous;
    return temp;
}

template<class T>
typename list<T>::reverse_iterator list<T>::reverse_iterator::operator++(int)
{
    cur_node = cur_node->previous;
    return *this;
}

template<class T>
typename list<T>::reverse_iterator list<T>::reverse_iterator::operator--()
{
    list<T>::reverse_iterator temp = *this;
    cur_node = cur_node->next;
    return temp;
}

template<class T>
typename list<T>::reverse_iterator list<T>::reverse_iterator::operator--(int)
{
    cur_node = cur_node->next;
    return *this;
}

template<class T>
bool list<T>::reverse_iterator::operator==(list<T>::reverse_iterator iter)
{
    return this->cur_node == iter.cur_node;
}

template<class T>
bool list<T>::reverse_iterator::operator!=(list<T>::reverse_iterator iter)
{
    return this->cur_node != iter.cur_node;
}

template<class T>
list<T>::list()
{
    this->size = 0;
    this->beg_node = nullptr;
}

template<class T>
list<T>::list(const list<T> &old_list)
{
    const list<T> *test = &old_list;
    list<T>::iterator iter = list<T>::iterator(&old_list);

    this->size = 0;
    this->beg_node = nullptr;

    for (unsigned int i = 0; i < old_list.size; i++)
    {
        this->push(*iter);
        iter++;
    }
}

template<class T>
list<T>::~list()
{
    this->free();
}

template<class T>
unsigned int list<T>::get_size()
{
    return this->size;
}

template<class T>
void list<T>::free()
{
    node *cur_node;
    node *next_node;

    if (this->beg_node == nullptr)
    {
        return;
    }

    cur_node = this->beg_node;
    next_node = this->beg_node->next;

    while (this->size > 0)
    {
        delete cur_node;
        cur_node = next_node;
        next_node = next_node->next;
        this->size--;
    }

    this->beg_node = nullptr;
}

template<class T>
bool list<T>::is_empty()
{
    return this->size == 0;
}

template<class T>
bool list<T>::contains(T item)
{
    try
    {
        this->get_idx(item);
    }
    catch (...)
    {
        return false;
    }
    return true;
}

template<class T>
typename list<T>::node *list<T>::get_node_by_idx(unsigned int idx) {
    unsigned int counter = 0;
    node *cur_node = this->beg_node;

    if (idx > this->size)
    {
        throw std::runtime_error("out of list bounds");
    }

    while (counter != idx)
    {
        cur_node = cur_node->next;
        counter++;
    }

    return cur_node;
}

template<class T>
T list<T>::get_element_by_idx(unsigned int idx)
{
    return get_node_by_idx(idx)->item;
}

template<class T>
unsigned int list<T>::get_idx(T item)
{
    unsigned int counter = 0;
    list::iterator iter_beg = this->begin();
    list::iterator iter = this->begin();

    do
    {
        if (*iter == item)
        {
            return counter;
        }
        iter++;
        counter++;
    }
    while (iter != iter_beg);

    throw std::runtime_error("item not found");
}

template<class T>
void list<T>::push(T item)
{
    node *new_node = new node(item);

    switch (this->size)
    {
        case 0:
        {
            this->beg_node = new_node;
            this->beg_node->next = new_node;
            this->beg_node->previous = new_node;
            break;
        }
        default:
        {
            new_node->next = this->beg_node;
            new_node->previous = this->beg_node->previous;
            this->beg_node->previous->next = new_node;
            this->beg_node->previous = new_node;
            break;
        }
    }

    this->size++;
}

template<class T>
void list<T>::push(T item, unsigned int idx)
{
    node *new_node;
    node *prev_node;
    node *next_node;

    if (idx > this->size)
    {
        throw std::runtime_error("out of list bounds");
    }

    if (idx == this->size)
    {
        this->push(item);
        return;
    }

    new_node = new node(item);
    prev_node = this->get_node_by_idx(idx);
    next_node = prev_node->next;

    new_node->previous = prev_node;
    new_node->next = next_node;

    prev_node->next = new_node;
    next_node->previous = new_node;

    if (idx == 0)
    {
        this->beg_node = prev_node->next;
    }

    this->size++;
}

template<class T>
T list<T>::remove(T item)
{
    if (this->size == 0)
    {
        throw std::runtime_error("empty list");
    }

    return this->remove(this->size-1);
}

template<class T>
T list<T>::remove(unsigned int idx)
{
    T removed_item;
    node *removed_node;
    if (idx >= this->size)
    {
        throw std::runtime_error("out of list bounds");
    }

    switch (this->size)
    {
        case 1:
        {
            removed_item = this->beg_node->item;
            delete this->beg_node;
            this->beg_node = nullptr;
            break;
        }
        default:
        {
            removed_node = get_node_by_idx(idx);
            removed_item = removed_node->item;
            removed_node->next->previous = removed_node->previous;
            removed_node->previous->next = removed_node->next;
            delete removed_node;
            break;
        }
    }

    this->size--;
    return removed_item;
}

template<class T>
typename list<T>::iterator list<T>::begin()
{
    return list::iterator(this);
}

template<class T>
typename list<T>::reverse_iterator list<T>::rbegin()
{
    return list::reverse_iterator(this);
}

template<class T>
typename list<T>::iterator list<T>::end()
{
    // TODO: "proper" end iterator
    return list<T>::iterator(this)--;
}

template<class T>
typename list<T>::reverse_iterator list<T>::rend()
{
    // TODO: "proper" end iterator
    return list<T>::reverse_iterator(this)++;
}


template class list<int>;
