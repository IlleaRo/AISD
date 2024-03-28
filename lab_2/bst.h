#ifndef BST
#define H_HEADER

#include <iostream>
#include <functional>


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

    void bst_show(node *ptr_node, const unsigned int level) {
        if (!ptr_node) {
            return;
        }
        
        bst_show(ptr_node->right, level + 1);

        for (int i = 0; i < level * 3; i++) {
            std::cout<<" ";
        }
        std::cout<<ptr_node->key<<std::endl;

        bst_show(ptr_node->left, level + 1);
    }

    void bst_clear(node *ptr_node) {
        if (!ptr_node) {
            return;
        }

        bst_clear(ptr_node->left);
        bst_clear(ptr_node->right);

        delete ptr_node;
    }

    node *bst_remove(node *ptr_node, K key, bool &is_deleted) {
        std::function<node *(node *, node *)> bst_use_replacement_node =
            [&] (node *ptr_replacement_node, node *_ptr_node) {
            if (ptr_replacement_node->left) {
                ptr_replacement_node->left = bst_use_replacement_node(ptr_replacement_node->left, ptr_node);
                return ptr_replacement_node;
            }

            _ptr_node->key = ptr_replacement_node->key;
            _ptr_node->data = ptr_replacement_node->data;

            node *tmp = ptr_replacement_node->right;
            delete ptr_replacement_node;

            return tmp;
        };

        if (!ptr_node) {
            return ptr_node;
        }

        if (key < ptr_node->key) {
            ptr_node->left = bst_remove(ptr_node->left, key, is_deleted);
            return ptr_node;
        }

        if (key > ptr_node->key) {
            ptr_node->right = bst_remove(ptr_node->right, key, is_deleted);
            return ptr_node;
        }

        is_deleted = true;

        // У удаляемого узла нет сыновей
        if (!ptr_node->left && !ptr_node->right) {
            delete ptr_node;
            return nullptr;
        }

        // У удаляемого узла один сын левый или правый
        if (!ptr_node->left) {
            node *tmp = ptr_node->right;
            delete ptr_node;
            return tmp;
        }

        if (!ptr_node->right) {
            node *tmp = ptr_node->left;
            delete ptr_node;
            return tmp;
        }

        // У удаляемого узла два потомка
        ptr_node->right = bst_use_replacement_node(ptr_node->right, ptr_node);
        return ptr_node;
    }

    node *bst_root_insert(node *ptr_node, K key, T data, bool &is_inserted) {

        auto left_rotate = [](node *_ptr_node) {
            node * tmp = _ptr_node->right;
            _ptr_node->right = tmp->left;
            tmp->left = _ptr_node;

            return tmp;
        };

        auto right_rotate = [](node *_ptr_node) {
            node * tmp = _ptr_node->left;
            _ptr_node->left = tmp->right;
            tmp->right = _ptr_node;

            return tmp;
        };


        if (!ptr_node) {
            is_inserted = true;
            return new node(key, data);
        }

        if (ptr_node->key == key) {
            is_inserted = false;
            return ptr_node;
        }

        if (key < ptr_node->key) {
            ptr_node->left = bst_root_insert(ptr_node->left, key, data, is_inserted);
            if (is_inserted) {
                return right_rotate(ptr_node);
            }

            return ptr_node;
        }

        ptr_node->right = bst_root_insert(ptr_node->right, key, data, is_inserted);

        if (is_inserted) {
            return left_rotate(ptr_node);
        }

        return ptr_node;
    }

public:

    /// Конструктор
    bst(void) : traverse_counter(0), root(nullptr), size(0) {};

    /// Конструктор копирования
    bst(const bst<T,K> &old_tree) : traverse_counter(0), size(old_tree.size) {
        std::function<node *(node *)> bst_copy = [&] (node *ptr_node){
            if (!ptr_node) {
                return nullptr;
            }

            return new node(ptr_node->key, ptr_node->data, bst_copy(ptr_node->left), bst_copy(ptr_node->right));
        };

        root = bst_copy(old_tree.root);
    };

    /// Деструктор
    ~bst(void) {
        bst_clear(root);
    }

    /// Опрос размера дерева
    [[nodiscard]] unsigned int get_size(void) const {
        return size;
    }

    /// Очистка дерева
    void clear(void) {
        bst_clear(root);
        size = 0;
        root = nullptr;
    }

    /// Проверка дерева на пустоту
    [[nodiscard]] bool is_empty(void) const {
        return size == 0;
    }

    /// Доступ по чтению/записи к данным по ключу
    T &get_by_key(const K key) {
        std::function<T &(node *)> bst_search = [&] (node *ptr_node) {
            if (!ptr_node) {
                throw std::runtime_error("unknown key");
            }

            if (ptr_node->key == key) {
                return ptr_node->data;
            }

            if (ptr_node->key < key) {
                return bst_search(ptr_node->left, key);
            }

            return bst_search(ptr_node->right, key);
        };

        return bst_search(root);
    }

    /// Включение данных с заданным ключом
    bool insert(const K key, const T data) {
        bool is_inserted = false;

        std::function<node *(node *)> bst_insert =
            [&](node *ptr_node) {
                if (!ptr_node) {
                    size++;
                    is_inserted = true;

                    return new node(key, data);
                }

                if (ptr_node->key == key) {
                    return ptr_node;
                }

                if (ptr_node->key > key) {
                    ptr_node->left = bst_insert(ptr_node->left);
                } else {
                    ptr_node->right = bst_insert(ptr_node->right);
                }

                return ptr_node;
            };

        if (!root) {
            root = new node(key, data);
            size++;
            return true;
        }

        bst_insert(root);

        return is_inserted;
    }

    /// Удаление данных с заданным ключом
    bool remove(K key) {
        bool is_deleted;

        root = bst_remove(root, key, is_deleted);

        return is_deleted;
    }

    /// Формирование списка ключей в дереве в порядке обхода узлов по схеме L->t->R
    void print_traversal(void) {
        std::function<void (const node *)> bst_ltr_traversal = [&](const node *ptr_node) {
            if (!ptr_node) {
                return;
            }

            bst_ltr_traversal(ptr_node->left);
            std::cout<<ptr_node->key<<" ";
            bst_ltr_traversal(ptr_node->right);
        };

        bst_ltr_traversal(root);
    }

    /** Поиск и подъем в корень дерева узла с ближайшим ключом, большим заданного значения.
    Трудоёмкость операции – O(log n). */
    bool climbing_greater_node(const K key) {
        std::function<node *(node *, node **, K, bool &)> bst_find_greater_node =
            [&](node *ptr_node, node **ptr_parrent, K key_link, bool &is_find) {
            if (!ptr_node) {
                return ptr_node;
            }

            if (ptr_node->key > key_link) {
                is_find = true;
                return ptr_node;
            }

            *ptr_parrent = ptr_node;
            return bst_find_greater_node(ptr_node->right, ptr_parrent, key_link, is_find);
        };

        bool is_find = false;

        node *parrent = root;
        node *tmp = bst_find_greater_node(root, &parrent, key, is_find);

        if (!is_find) {
            return false;
        }

        if (tmp == root) {
            return true;
        }

        T _data = tmp->data;
        K _key = tmp->key;

        if (parrent->left == tmp) {
            parrent->left = bst_remove(tmp, tmp->key, is_find);
        } else {
            parrent->right = bst_remove(tmp, tmp->key, is_find);
        }

        root = bst_root_insert(root, _key, _data, is_find);
        return true;
    }
    

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

#endif // BST