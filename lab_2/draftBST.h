#include <iostream>
#include <list>

template <class T>
class bst {
private:
    unsigned long traverse_counter;
protected:
    /// Класс узла
    class node {
    private:
        unsigned long key; // Ключ
        T data; // Данные
        node &left; // Левый потомок
        node &right; // Правый потомок
    };

    node &head; // Корень дерева
    unsigned int size; // Вершина дерева

public:

    /// Конструктор
    bst(void);

    /// Конструктор копирования
    bst(const bst<T> &);

    /// Деструктор
    ~bst(void);

    /// Опрос размера дерева
    unsigned int get_size(void);

    /// Очистка дерева
    void free(void);

    /// Проверка дерева на пустоту
    bool is_empty(void);

    /// Доступ по чтению/записи к данным по ключу
    T &get_by_key(const T &);
    T &bst_search(node *, const T &);

    /// Включение данных с заданным ключом
    bool insert(const unsigned long key, const T data);
    bool bst_insert(node *, const unsigned long key, const T data);

    /// Удаление данных с заданным ключом
    bool remove(const unsigned long key);
    bool bst_remove(node *, const unsigned long key);

    /// Формирование списка ключей в дереве в порядке обхода узлов по схеме L->t->R
    std::list<T> traversal(node *);

    /** Поиск и подъем в корень дерева узла с ближайшим ключом, большим заданного значения.
    Трудоёмкость операции – O(log n). */
    void climbing_greater_node(void);

    class iterator;
    class reverse_iterator;

    /// Запрос прямого итератора, установленного на узел дерева с минимальным ключом begin().
    iterator begin(void);

    /// Запрос обратного итератора, установленного на узел дерева с максимальным ключом rbegin().
    reverse_iterator rbegin(void);

    /// запрос «неустановленного» прямого итератора end().
    iterator end(void);

    /// запрос «неустановленного» обратного итератора rend().
    reverse_iterator rend(void);


    class iterator {
    private:
        bst *root; // Корень
        node *cur; // Текущий узел

    public:
        /// операция доступа по чтению и записи к данным текущего узла *.
        T &operator*(void);

        /// операция перехода к следующему (для обратного – к предыдущему) по ключу узлу в дереве ++.
        iterator operator++(void);

        /// операция перехода к предыдущему (для обратного – к следующему) по ключу узлу в дереве --.
        iterator operator--(void);

        /// проверка равенства однотипных итераторов ==.
        bool operator==(const iterator &iter);

        /// проверка неравенства однотипных итераторов !=.
        bool operator!=(const iterator &iter);
    };

    class reverse_iterator {
    private:
        bst *root; // Корень
        node *cur; // Текущий узел

    public:
        /// операция доступа по чтению и записи к данным текущего узла *.
        T &operator*(void);

        /// операция перехода к следующему (для обратного – к предыдущему) по ключу узлу в дереве ++.
        reverse_iterator operator++(void);

        /// операция перехода к предыдущему (для обратного – к следующему) по ключу узлу в дереве --.
        reverse_iterator operator--(void);

        /// проверка равенства однотипных итераторов ==.
        bool operator==(const iterator &reverse_iterator);

        /// проверка неравенства однотипных итераторов !=.
        bool operator!=(const iterator &reverse_iterator);
    };

    /// Вывод структуры дерева на экран
    template<class T1>
    friend std::ostream& operator<< (std::ostream &os, const bst<T1> &root);

    /// Опрос числа узлов дерева, просмотренных предыдущей операцией
    unsigned long get_traverse_counter(void);
};