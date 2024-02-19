#include "list.h"

template<class T>
list<T>::node::node(T item)
{
    // TODO: IMPLEMENT ME
}

template<class T>
T list<T>::iterator::operator*()
{
    // TODO: IMPLEMENT ME
    return nullptr;
}

template<class T>
list<T>::iterator::iterator(list *plist)
{
    this->plist = plist;
    cur_node = plist->head;
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
bool list<T>::iterator::operator==(list::iterator iter)
{
    // TODO: IMPLEMENT ME
    return false;
}

template<class T>
bool list<T>::iterator::operator!=(list::iterator iter)
{
    // TODO: IMPLEMENT ME
    return false;
}

template<class T>
list<T>::reverse_iterator::reverse_iterator(list *plist)
{
    this->plist = plist;
    cur_node = plist->tail;
}

template<class T>
T list<T>::reverse_iterator::operator*()
{
    // TODO: IMPLEMENT ME
    return nullptr;
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
bool list<T>::reverse_iterator::operator==(list::reverse_iterator iter)
{
    // TODO: IMPLEMENT ME
    return false;
}

template<class T>
bool list<T>::reverse_iterator::operator!=(list::reverse_iterator iter)
{
    // TODO: IMPLEMENT ME
    return false;
}

template<class T>
list<T>::list()
{
    // TODO: IMPLEMENT ME
}

template<class T>
list<T>::list(const list &)
{
    // TODO: IMPLEMENT ME
}

template<class T>
list<T>::~list()
{
    // TODO: IMPLEMENT ME
}

template<class T>
unsigned int list<T>::get_size()
{
    // TODO: IMPLEMENT ME
    return 0;
}

template<class T>
void list<T>::free()
{
    // TODO: IMPLEMENT ME
}

template<class T>
bool list<T>::is_empty()
{
    // TODO: IMPLEMENT ME
    return false;
}

template<class T>
bool list<T>::is_contain(T item)
{
    // TODO: IMPLEMENT ME
    return false;
}

template<class T>
T list<T>::get_element_by_id(unsigned int idx)
{
    // TODO: IMPLEMENT ME
    return nullptr;
}

template<class T>
unsigned int list<T>::get_id(T item)
{
    // TODO: IMPLEMENT ME
    return 0;
}

template<class T>
void list<T>::push(T item)
{
    // TODO: IMPLEMENT ME
}

template<class T>
bool list<T>::push(T item, unsigned int idx)
{
    // TODO: IMPLEMENT ME
    return false;
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
    // TODO: IMPLEMENT ME
    return list::iterator(nullptr);
}

template<class T>
typename list<T>::reverse_iterator list<T>::rbegin()
{
    // TODO: IMPLEMENT ME
    return list::reverse_iterator(nullptr);
}

template<class T>
typename list<T>::iterator list<T>::end()
{
    // TODO: IMPLEMENT ME
    return list::iterator(nullptr);
}

template<class T>
typename list<T>::reverse_iterator list<T>::rend()
{
    // TODO: IMPLEMENT ME
    return list::reverse_iterator(nullptr);
}

template<class T>
std::ostream &operator<<(std::ostream &os, const list<T> &list)
{
    // TODO: IMPLEMENT ME
    return os;
}