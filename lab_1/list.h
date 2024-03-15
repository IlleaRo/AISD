#ifndef LAB_1_LIST_H
#define LAB_1_LIST_H

#include <iostream>
#include <stdexcept>

template <class T>
class list { // Кольцевой двухсвязный список на базе адресных указателей

protected:
    class node { // Класс узла списка

    public:
        explicit node(T item) : item(item) {}
        T item;
        node *next;
        node *previous;
    };

    node *beg_node;
    unsigned int size;
    unsigned int traverse_counter;

    node *get_node_by_idx(unsigned int idx) {
        unsigned int counter = 0;
        node *cur_node;

        if (this->size == 0 || idx > this->size - 1)
        {
            throw std::runtime_error("out of list bounds");
        }

        if (idx > this->size / 2)
        {
            cur_node = this->beg_node->previous;

            counter = this->size - 1;
            while (counter != idx)
            {
                cur_node = cur_node->previous;
                counter--;
            }
        }
        else
        {
            cur_node = this->beg_node;
            while (counter != idx)
            {
                cur_node = cur_node->next;
                counter++;
            }
        }

        if (idx > this->size / 2)
        {
            counter = this->size - counter;
        }

        this->traverse_counter = counter;
        return cur_node;
    }

public:
    // Конструктор
    list() : traverse_counter(0), size(0), beg_node(nullptr){}

    // Конструктор копирования
    list(list<T> &old_list) : traverse_counter(0), size(0), beg_node(nullptr) {
        list<T>::iterator iter = list<T>::iterator(&old_list);

        for (unsigned int i = 0; i < old_list.size; i++)
        {
            this->push(*iter);
            iter++;
        }
    }

    // Деструктор
    ~list() {
        this->free();
    }

    // Опрос размера списка
    unsigned int get_size() { return size; }

    // Очистка списка
    void free() {
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

    // Проверка списка на пустоту
    bool is_empty() { return this->size == 0; };

    // Опрос наличия заданного значения
    bool contains(T item) {
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

    // Изменение значения с заданным номером в списке
    T set_element_by_idx(T item, unsigned int idx) {
        node *pnode = get_node_by_idx(idx);
        T ret = pnode->item;
        pnode->item = item;

        return ret;
    }

    // Чтение значения с заданным номером в списке
    T get_element_by_idx(unsigned int idx) {
        return get_node_by_idx(idx)->item;
    }

    // Вывод на экран последовательности значений данных из списка.
    template<class T1>
    friend std::ostream& operator<< (std::ostream &os, list<T1> &plist) {
        if (plist.is_empty()) {
            return os;
        }

        typename list<T>::iterator iter_beg = plist.begin();
        typename list<T>::iterator iter = plist.begin();

        do
        {
            os << *iter << " ";
            iter++;
        }
        while (iter != iter_beg);

        os<<"\n";
        return os;
    }

    // Получение позиции в списке для заданного значения
    unsigned int get_idx(T item) {
        unsigned int counter = 0;
        list::iterator iter_beg = this->begin();
        list::iterator iter = this->begin();

        do
        {
            if (*iter == item)
            {
                this->traverse_counter = counter;
                return counter;
            }
            iter++;
            counter++;
        }
        while (iter != iter_beg);

        this->traverse_counter = counter;

        throw std::runtime_error("item not found");
    }

    // Включение нового значения
    void push(T item) {
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

    // Включение нового значения в позицию с заданным номером
    void push(T item, unsigned int idx) {
        node *new_node;
        node *prev_node;
        node *next_node;

        if (idx > this->size)
        {
            throw std::runtime_error("out of list bounds");
        }

        if (idx == this->size)
        {
            this->traverse_counter = 0;
            this->push(item);
            return;
        }

        new_node = new node(item);
        prev_node = this->get_node_by_idx(idx)->previous;
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

    // Удаление заданного значения из списка
    bool remove_item(T item) {
        if (this->size == 0)
        {
            throw std::runtime_error("empty list");
        }

        list::node *tnode = this->beg_node;

        bool is_found = false;
        this->traverse_counter = 0;

        do {
            this->traverse_counter++;
            if (tnode->item == item) {
                is_found = true;
                break;
            }

            tnode = tnode->next;
        } while (tnode != this->beg_node);

        if (is_found) {
            switch (this->size)
            {
                case 1:
                {
                    delete this->beg_node;
                    this->beg_node = nullptr;
                    return true;
                }
                default:
                {
                    tnode->previous->next = tnode->next;
                    tnode->next->previous = tnode->previous;
                    delete tnode;
                    return true;
                }
            }
        }

        return false;
    }

    // Удаление значения из позиции с заданным номером
    T remove_idx(unsigned int idx) {
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
                this->traverse_counter = 0;
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

    // Удаление последнего значения списка
    T pop() {
        if (this->size == 0)
        {
            throw std::runtime_error("empty list");
        }

        return this->remove_idx(this->size-1);
    }

    class iterator { // Прямой итератор
    protected:
        list<T> *plist;
        node *cur_node;

    public:
        explicit iterator(list<T> *plist) : plist(plist), cur_node(plist->beg_node) {};
        iterator(list<T> *plist, node *pnode) : plist(plist), cur_node(pnode) {};

        // Операция доступа по чтению и записи к текущему значению
        T &operator*() {
            if (*this == this->plist->end()) {
               throw std::runtime_error("unspecified iterator");
            }

            return this->cur_node->item;
        }

        // Операция инкримента для перехода к следующему значению
        iterator operator++() {
            if (this == this->plist->end()) {
                throw std::runtime_error("unspecified iterator");
            }

            iterator temp = *this;

            cur_node = cur_node->next;

            return temp;
        }

        iterator operator++(int) {
            if (*this == this->plist->end()) {
                throw std::runtime_error("unspecified iterator");
            }
            cur_node = cur_node->next;

            return *this;
        }

        // Операция декремента для перехода к предыдущему значению в списке
        iterator operator--() {
            if (this == this->plist->end()) {
                throw std::runtime_error("unspecified iterator");
            }

            iterator temp = *this;

            cur_node = cur_node->previous;

            return temp;
        }

        iterator operator--(int) {
            if (*this == this->plist->end()) {
                throw std::runtime_error("unspecified iterator");
            }

            cur_node = cur_node->previous;

            return *this;
        }


        // Проверка равенства однотипных итераторов
        bool operator==(iterator iter) {
            if (this->plist == iter.plist)
            {
                return this->cur_node == iter.cur_node;
            }

            return false;
        }

        // Проверка неравенства однотипных итераторов
        bool operator!=(iterator iter) {

            if (this->plist == iter.plist)
            {
                return this->cur_node != iter.cur_node;
            }

            return false;
        }
    };


    class reverse_iterator { // Обратный итератор
    private:
        list<T> *plist;
        node *cur_node;

    public:
        explicit reverse_iterator(list<T> *plist) : plist(plist),
            cur_node(plist->beg_node ? plist->beg_node->previous : nullptr) {};
        reverse_iterator(list<T> *plist, node *pnode) : plist(plist), cur_node(pnode) {};

        // Операция доступа по чтению и записи к текущему значению
        T &operator*() {
            if (*this == this->plist->rend()) {
                throw std::runtime_error("unspecified iterator");
            }

            return this->cur_node->item;
        };

        // Операция инкримента для перехода к предыдущему значению
        reverse_iterator operator++() {
            if (this == this->plist->rend()) {
                throw std::runtime_error("unspecified iterator");
            }

            list<T>::reverse_iterator temp = *this;

            cur_node = cur_node->previous;

            return temp;
        }

        reverse_iterator operator++(int) {
            if (*this == this->plist->rend()) {
                throw std::runtime_error("unspecified iterator");
            }

            cur_node = cur_node->previous;

            return *this;
        }

        // Операция декремента для перехода к следующему значению в списке
        reverse_iterator operator--() {
            if (this == this->plist->rend()) {
                throw std::runtime_error("unspecified iterator");
            }

            list<T>::reverse_iterator temp = *this;

            cur_node = cur_node->next;

            return temp;
        }

        reverse_iterator operator--(int) {
            if (*this == this->plist->rend()) {
                throw std::runtime_error("unspecified iterator");
            }

            list<T>::reverse_iterator temp = *this;
            cur_node = cur_node->next;
            return temp;
        }

        // Проверка равенства однотипных итераторов
        bool operator==(reverse_iterator iter) {
            if (this->plist == iter.plist)
            {
                return this->cur_node == iter.cur_node;
            }

            return false;
        }

        // Проверка неравенства однотипных итераторов
        bool operator!=(reverse_iterator iter) {
            if (this->plist == iter.plist)
            {
                return this->cur_node != iter.cur_node;
            }

            return false;
        }
    };

    // Запрос прямого итератора
    iterator begin() {
        return list::iterator(this);
    }

    // Запрос обратного итератора
    reverse_iterator rbegin() {
        return list::reverse_iterator(this);
    }

    // Запрос неустановленного прямого итератора
    iterator end() {
        return list<T>::iterator(this, nullptr);
    }

    // Запрос неустановленного обратного итератора
    reverse_iterator rend() {
        return list<T>::reverse_iterator(this, nullptr);
    }

    // Запрос счетчика
    unsigned int get_traverse_count() {
        return this->traverse_counter;
    }
};

#endif //LAB_1_LIST_H
