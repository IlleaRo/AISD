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
    cur_node = plist->beg_node;
}

template<class T>
void list<T>::iterator::operator++()
{
    cur_node = cur_node->next;
}

template<class T>
void list<T>::iterator::operator--()
{
    cur_node = cur_node->preview;
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
    cur_node = plist->beg_node->next;
}

template<class T>
T list<T>::reverse_iterator::operator*()
{
    return this->cur_node->item;
}

template<class T>
void list<T>::reverse_iterator::operator++()
{
    cur_node = cur_node->preview;
}

template<class T>
void list<T>::reverse_iterator::operator--()
{
    cur_node = cur_node->next;
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
        ++iter;
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
    node *cur_node = this->beg_node;
    node *next_node = this->beg_node->next;

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
    catch (...) // TODO: make exceptions static
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
        throw std::runtime_error("out of list bounds"); // TODO: make exceptions static
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
        ++iter;
        ++counter;
    }
    while (iter != iter_beg);

    throw std::runtime_error("item not found"); // TODO: make exceptions static
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
        case 1:
        {
            new_node->next = this->beg_node;
            new_node->previous = this->beg_node;
            this->beg_node->previous = new_node;
            this->beg_node->next = new_node;
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
        throw std::runtime_error("out of list bounds"); // TODO: make exceptions static
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
bool list<T>::remove(T item)
{
    // TODO: IMPLEMENT ME
    return false;
}

template<class T>
bool list<T>::remove(unsigned int idx)
{
    // TODO: IMPLEMENT ME
    return false;
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
    // TODO: postfix decrement
    list<T>::iterator iter = list<T>::iterator(this);
    --iter;
    return iter;
}

template<class T>
typename list<T>::reverse_iterator list<T>::rend()
{
    // TODO: postfix increment
    list<T>::reverse_iterator iter = list<T>::reverse_iterator(this);
    ++iter;
    return iter;
}

template<class T>
std::ostream &operator<<(std::ostream &os, const list<T> &list)
{
    // TODO: IMPLEMENT ME
    return os;
}
