template <class T>
class list {
protected:
    class node;

    node *beg_node;
    unsigned int size;
    unsigned int traverse_counter;

    node *get_node_by_idx(unsigned int idx);

public:
    list(); // Конструктор
    list(list<T> &old_list); // Конструктор копирования
    ~list(); // Деструктор
    unsigned int get_size(); // Опрос размера списка
    void free(); // Очистка списка
    bool is_empty(); // Проверка на пустоту
    bool contains(T item); // опрос наличия заданного значения
    T get_element_by_idx(unsigned int idx); // чтение значения с заданным номером в списке
    T set_element_by_idx(T item, unsigned int idx); // изменение значения с заданным номером в списке
    unsigned int get_idx(T item); // получение позиции в списке для заданного значения
    void push(T item); // включение нового значения
    void push(T item, unsigned int idx); //включение нового значения в позицию с заданным номером
    bool remove_item(T item); // удаление заданного значения из списка
    T remove_idx(unsigned int idx); //удаление значения из позиции с заданным номером
    T pop();

    class iterator;
    class reverse_iterator;

    iterator begin(); // запрос прямого итератора
    reverse_iterator rbegin(); // запрос обратного итератора
    iterator end(); // запрос неустановленного итератора
    reverse_iterator rend(); // запрос обратного неустановленного
    unsigned int get_traverse_count(); // Счетчик просмотров

public:
    class iterator {
    protected:
        list<T> *plist;
        typename list<T>::node *cur_node;

    public:
        explicit iterator(list<T> *plist);
        iterator(list<T> *plist, typename list<T>::node *pnode);

        T &operator*(); // операция доступа по чтению и записи к текущему значению
        iterator operator++(); // операция инкремента для перехода к следующему
        iterator operator++(int); // операция инкремента для перехода к следующему
        iterator operator--(); // операция декремента для перехода к следующему
        iterator operator--(int); // операция декремента для перехода к следующему
        bool operator==(iterator iter); // проверка равенства однотипных итераторов
        bool operator!=(iterator iter); // проверка неравенства однотипных итераторов
    };

    class reverse_iterator {
    private:
        list<T> *plist;
        typename list<T>::node *cur_node;

    public:
        explicit reverse_iterator(list<T> *plist);
        reverse_iterator(list<T> *plist, typename list<T>::node *pnode);

        T &operator*(); // операция доступа по чтению и записи к текущему значению
        reverse_iterator operator++(); // операция инкремента для перехода к следующему
        reverse_iterator operator++(int); // операция инкремента для перехода к следующему
        reverse_iterator operator--(); // операция декремента для перехода к следующему
        reverse_iterator operator--(int); // операция декремента для перехода к следующему
        bool operator==(reverse_iterator iter); // проверка равенства однотипных итераторов
        bool operator!=(reverse_iterator iter); // проверка неравенства однотипных итераторов
    };


public:
    template<class T1>
    friend std::ostream& operator<< (std::ostream &os, list<T1> &plist); // Вывод на экран последовательности значений данных из списка
};