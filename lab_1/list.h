#ifndef LAB_1_LIST_H
#define LAB_1_LIST_H

template <class T>
class list { // Кольцевой двухсвязный список на базе адресных указателей

protected:
    class node { // Класс узла списка
        node(T item);

    private:
        T item;
        node *next;
        node *preview;
    };

    class iterator { // Прямой итератор
    private:
        list* plist;
        node *cur_node;

    public:
        iterator(list* plist) {
            this->plist = plist;
            cur_node = plist->head;
        }

        T operator*(); // Операция доступа по чтению и записи к текущему значению

        void operator++() { // Операция инкримента для перехода к следующему значению
            cur_node = cur_node->next;
        }

        void operator--() { // Операция декремента для перехода к предыдущему значению в списке
            cur_node = cur_node->preview;
        }

        /**
         * НЕПРОСМОТРЕННО: операторы равенства и неравенства
         */

        bool operator==(); // Проверка равенства однотипных итераторов
        bool operator!=(); // Проверка неравенства однотипных итераторов
    };

    /**
    * НЕПРОСМОТРЕННО: обратный итератор
    */

    class reverse_iterator { // Обратный итератор
    private:
        list* plist;
        node *cur_node;

    public:
        reverse_iterator(list* plist) {
            this->plist = plist;
            cur_node = plist->tail;
        }

        T operator*(); // Операция доступа по чтению и записи к текущему значению

        void operator++() { // Операция инкримента для перехода к предыдущему значению
            cur_node = cur_node->preview;
        }

        void operator--() { // Операция декремента для перехода к следующему значению в списке
            cur_node = cur_node->next;
        }

        bool operator==(); // Проверка равенства однотипных итераторов
        bool operator!=(); // Проверка неравенства однотипных итераторов
    };

public:
    list(); // Конструктор

    list(const list &); // Конструктор копирования

    ~list(); // Деструктор

    unsigned int get_size(); // Опрос размера списка

    void free(); // Очистка списка

    bool is_empty(); // Проверка списка на пустоту

    bool is_contain(T item); // Опрос наличия заданного значения

    T get_element_by_id(unsigned int id); // Чтение значения с заданным номером в списке

    unsigned int get_id(T item); // Получение позиции в списке для заданного значения

    void push(T item); // Включение нового значения
    bool push(T item, unsigned int id); // Включение нового значения в позицию с заданным номером

    bool remove(T item); // Удаление заданного значения из списка
    bool remove(unsigned int); // Удаление значения из позиции с заданным номером

    iterator begin(); // Запрос прямого итератора
    reverse_iterator rbegin(); // Запрос обратного итератора

    iterator end(); // Запрос прямого итератора
    reverse_iterator rend(); // Запрос обратного итератора
};

#endif //LAB_1_LIST_H
