#include <iostream>

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
        

        node(K key, T data) : key(key), data(data), left(nullptr), right(nullptr) {};
        node(K key, T data, node *left, node *right) : key(key), data(data), left(left), right(right) {};
    };

    node *root; // Корень дерева
    unsigned int size; // Количество элементов

    node *bst_insert(node *ptr_node, const K key, const T data, bool &is_inserted) {
        if (!ptr_node) {
            size++;
            is_inserted = true;

            return new node(key, data);
        }

        if (ptr_node->key == key) {
            return ptr_node;
        }

        if (ptr_node->key < key) {
            ptr_node->left = bst_insert(ptr_node->left, key, data, is_inserted);
        } else {
            ptr_node->right = bst_insert(ptr_node->right, key, data, is_inserted);
        }

        return ptr_node;
    }

    void bst_show(node *ptr_node, unsigned int level) {
        if (!ptr_node) {
            return;
        }
        
        bst_show(ptr_node->left, level + 1);

        for (int i = 0; i < level * 3; i++) {
            std::cout<<" ";
        }
        std::cout<<ptr_node->key<<std::endl;

        bst_show(ptr_node->right, level + 1);
    }

    void bst_clear(node *ptr_node) {
        if (!ptr_node) {
            return;
        }

        bst_clear(ptr_node->left);
        bst_clear(ptr_node->right);

        delete ptr_node;
    }

    node *bst_copy(node *ptr_node) {
        if (!ptr_node) {
            return nullptr;
        }

        return new node(ptr_node->key, ptr_node->data, bst_copy(ptr_node->left), bst_copy(ptr_node->right));
    }

public:

    /// Конструктор
    bst(void) : traverse_counter(0), size(0), root(nullptr) {};

    /// Конструктор копирования
    bst(bst<T,K> &old_tree) : size(old_tree.size), traverse_counter(0) {
        root = bst_copy(old_tree.root);
    };

    /// Деструктор
    ~bst(void) {
        clear();
    }

    /// Опрос размера дерева
    unsigned int get_size(void) {
        return size;
    }

    /// Очистка дерева
    void clear(void) {
       bst_clear(root);
       root = nullptr;
    }

    /// Проверка дерева на пустоту
    bool is_empty(void) {
        return size == 0;
    }

    /// Доступ по чтению/записи к данным по ключу
    T &get_by_key(const K);
    T &bst_search(node *, const K);

    /// Включение данных с заданным ключом
    bool insert(const K key, const T data) {
        if (!root) {
            size++;
            return (root = new node(key, data));
        }
        
        bool is_inserted = false;

        bst_insert(root, key, data, is_inserted);

        return is_inserted;
    }

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
    
    /// Вывод структуры дерева на экран (так не стоит)
    template<class T1, class K1>
    friend std::ostream &operator<< (std::ostream &os, bst<T1,K1> &tree);

    /// Опрос числа узлов дерева, просмотренных предыдущей операцией
    unsigned long get_traverse_counter(void) {
        return traverse_counter;
    }
};


    /// Вывод структуры дерева на экран (так не стоит)
template<class T, class K>
std::ostream &operator<< (std::ostream &os, bst<T,K> &tree) {
    tree.bst_show(tree.root, 0);
    
    return os;
}


