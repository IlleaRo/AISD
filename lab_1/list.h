#ifndef LAB_1_LIST_H
#define LAB_1_LIST_H

#include <iostream>

template <class T>
class list { // Кольцевой двухсвязный список на базе адресных указателей

protected:
    class node { // Класс узла списка

    public:
        explicit node(T item);
        T item;
        node *next;
        node *previous;
    };

    node *beg_node;
    unsigned int size;
    unsigned int traverse_counter;

    node *get_node_by_idx(unsigned int idx);

public:
    list(); // Конструктор

    list(const list<T> &old_list); // Конструктор копирования

    ~list(); // Деструктор

    unsigned int get_size(); // Опрос размера списка

    void free(); // Очистка списка

    bool is_empty(); // Проверка списка на пустоту

    bool contains(T item); // Опрос наличия заданного значения

    T set_element_by_idx(T item, unsigned int idx); // Изменение значения с заданным номером в списке

    T get_element_by_idx(unsigned int idx); // Чтение значения с заданным номером в списке

    template<class T1>
    friend std::ostream& operator<< (std::ostream &os, list<T1> &plist); // Вывод на экран последовательности
    // значений данных из списка.

    unsigned int get_idx(T item); // Получение позиции в списке для заданного значения

    void push(T item); // Включение нового значения
    void push(T item, unsigned int idx); // Включение нового значения в позицию с заданным номером

    bool remove_item(T item); // Удаление заданного значения из списка
    T remove_idx(unsigned int idx); // Удаление значения из позиции с заданным номером

    T pop(); // Удаление последнего значения списка

    class iterator { // Прямой итератор
    protected:
        const list<T> *plist;
        node *cur_node;

    public:
        explicit iterator(const list<T> *plist);
        iterator(const list<T> *plist, node *pnode);

        T operator*(); // Операция доступа по чтению и записи к текущему значению

        iterator operator++(); // Операция инкримента для перехода к следующему значению
        iterator operator++(int);

        iterator operator--(); // Операция декремента для перехода к предыдущему значению в списке
        iterator operator--(int);

        /**
         * НЕПРОСМОТРЕННО: операторы равенства и неравенства
         */

        bool operator==(iterator iter); // Проверка равенства однотипных итераторов
        bool operator!=(iterator iter); // Проверка неравенства однотипных итераторов
    };

    /**
    * НЕПРОСМОТРЕННО: обратный итератор
    */

    class reverse_iterator { // Обратный итератор
    private:
        const list<T> *plist;
        node *cur_node;

    public:
        explicit reverse_iterator(const list<T> *plist);
        reverse_iterator(const list<T> *plist, node *pnode);

        T operator*(); // Операция доступа по чтению и записи к текущему значению

        reverse_iterator operator++(); // Операция инкримента для перехода к предыдущему значению
        reverse_iterator operator++(int);

        reverse_iterator operator--(); // Операция декремента для перехода к следующему значению в списке
        reverse_iterator operator--(int);

        bool operator==(reverse_iterator iter); // Проверка равенства однотипных итераторов
        bool operator!=(reverse_iterator iter); // Проверка неравенства однотипных итераторов
    };

    iterator begin(); // Запрос прямого итератора
    reverse_iterator rbegin(); // Запрос обратного итератора

    iterator end(); // Запрос прямого итератора
    reverse_iterator rend(); // Запрос обратного итератора

    unsigned int get_traverse_count(); // Запрос последнего количества пройденных элементов
};

template<class T>
std::ostream &operator<<(std::ostream &os, list<T> &plist)
{
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

#endif //LAB_1_LIST_H
