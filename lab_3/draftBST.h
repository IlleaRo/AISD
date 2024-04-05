#include <iostream>
#include <list>

template <class T, class K>
class bst {
private:
    unsigned long traverse_counter;
protected:
    /// Класс узла
    class node {
    public:
        K key; // Ключ
        T data; // Данные
        node *left; // Левый потомок
        node *right; // Правый потомок
        unsigned int subtree_size; // Количество потомков узла
    };

    node *root; // Корень дерева
    unsigned int size; // Количество элементов

public:

    /// Конструктор
    bst(void);

    /// Конструктор копирования
    bst(const bst<T,K> &);

    /// Деструктор
    ~bst(void);

    /// Опрос размера дерева
    unsigned int get_size(void);

    /// Очистка дерева
    void clear(void);

    /// Проверка дерева на пустоту
    bool is_empty(void);

    /// Доступ по чтению/записи к данным по ключу
    T &get_by_key(const K);
    T &bst_search(node *, const K);

    /// Включение данных с заданным ключом
    bool insert(const K key, const T data);
    bool bst_insert(node *, const K key, const T data);

    /// Удаление данных с заданным ключом
    bool remove(const K key);
    bool bst_remove(node *, const K key);

    /// Формирование списка ключей в дереве в порядке обхода узлов по схеме L->t->R
    void print_traversal(void);

    /** Поиск и подъем в корень дерева узла с ближайшим ключом, большим заданного значения.
    Трудоёмкость операции – O(log n). */
    void climbing_greater_node(const K key);
    

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
        bst *tree; // Корень
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
        bst *tree; // Корень
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
    void show(void); // вывод структуры на экран (лучше так)
    /// Вывод структуры дерева на экран (так не стоит)
    template<class T1, class K1>
    friend std::ostream& operator<< (std::ostream &os, const bst<T1,K1> &root);

    /// Опрос числа узлов дерева, просмотренных предыдущей операцией
    unsigned long get_traverse_counter(void);
};
