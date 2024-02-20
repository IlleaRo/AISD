#ifndef LAB_1_LIST_H
#define LAB_1_LIST_H

#include <iostream>

template <class T>
class list { // Кольцевой двухсвязный список на базе адресных указателей

protected:
    class node { // Класс узла списка
        explicit node(T item);

    private:
        T item;
        node *next;
        node *preview;
    };

    class iterator { // Прямой итератор
    private:
        list<T> *plist;
        node *cur_node;

    public:
        explicit iterator(list* plist);

        T operator*(); // Операция доступа по чтению и записи к текущему значению

        void operator++(); // Операция инкримента для перехода к следующему значению

        void operator--(); // Операция декремента для перехода к предыдущему значению в списке

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
        list<T>* plist;
        node *cur_node;

    public:
        explicit reverse_iterator(list* plist);

        T operator*(); // Операция доступа по чтению и записи к текущему значению

        void operator++(); // Операция инкримента для перехода к предыдущему значению

        void operator--(); // Операция декремента для перехода к следующему значению в списке

        bool operator==(reverse_iterator iter); // Проверка равенства однотипных итераторов
        bool operator!=(reverse_iterator iter); // Проверка неравенства однотипных итераторов
    };

public:
    list(); // Конструктор

    list(const list &); // Конструктор копирования

    ~list(); // Деструктор

    unsigned int get_size(); // Опрос размера списка

    void free(); // Очистка списка

    bool is_empty(); // Проверка списка на пустоту

    bool is_contain(T item); // Опрос наличия заданного значения

    T get_element_by_id(unsigned int idx); // Чтение значения с заданным номером в списке

    template<class T1>
    friend std::ostream& operator<< (std::ostream &os, const list<T1> &list); // Вывод на экран последовательности значений данных из списка.

    unsigned int get_id(T item); // Получение позиции в списке для заданного значения

    void push(T item); // Включение нового значения
    bool push(T item, unsigned int idx); // Включение нового значения в позицию с заданным номером

    bool remove(T item); // Удаление заданного значения из списка
    bool remove(unsigned int idx); // Удаление значения из позиции с заданным номером

    iterator begin(); // Запрос прямого итератора
    reverse_iterator rbegin(); // Запрос обратного итератора

    iterator end(); // Запрос прямого итератора
    reverse_iterator rend(); // Запрос обратного итератора
};

#endif //LAB_1_LIST_H
