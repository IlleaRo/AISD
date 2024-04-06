#ifndef BST
#define BST

#include <iostream>
#include <functional>

#define USE_INSERT_IN_ROOT 0

template <class K, class T>
class bst {
 protected:
  unsigned long traverse_counter;
  /// Класс узла
  class node {
   public:
    K key; // Ключ
    T data; // Данные
    node *left; // Левый потомок
    node *right; // Правый потомок
    unsigned int subtree_size; // Количество потомков узла


    node(K key, T data) : key(key), data(data), left(nullptr), right(nullptr), subtree_size(0) {};
    node(K key, T data, node *left, node *right) : key(key), data(data), left(left), right(right), subtree_size(0) {};
  };

  node *root; // Корень дерева
  unsigned int size; // Количество элементов

  virtual void bst_show(node *ptr_node, const unsigned int level) {
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

  node *bst_use_replacement_node(node* ptr_replacement_node, node* ptr_node) {
      traverse_counter++;

      if (ptr_replacement_node->left) {
          ptr_replacement_node->left = bst_use_replacement_node(ptr_replacement_node->left, ptr_node);
          return ptr_replacement_node;
      }

      ptr_node->key = ptr_replacement_node->key;
      ptr_node->data = ptr_replacement_node->data;

      node* tmp = ptr_replacement_node->right;
      delete ptr_replacement_node;

      return tmp;
  }

  virtual node *bst_remove(node *ptr_node, K key, bool &is_deleted) {
      traverse_counter++;

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

  // Поиск максимального по ключу узла в левом поддереве
  node *bst_max(node* ptr_node) {
      if (!ptr_node) {
          return nullptr;
      }

      while (ptr_node->right) {
          ptr_node = ptr_node->right;
      }

      return ptr_node;
  }

  // Поиск минимального по ключу узла в правом поддереве
  node *bst_min(node* ptr_node) {
      if (!ptr_node) {
          return nullptr;
      }

      while (ptr_node->left) {
          ptr_node = ptr_node->left;
      }

      return ptr_node;
  }

  // Поиск ближайшего правого родителя для заданного узла дерева
  node *bst_r_parent(node *tmp, const node *ptr_node){
      if (ptr_node == tmp) {
          return nullptr;
      }

      if (ptr_node->key > tmp->key) {
          if (node* r_parrent = bst_r_parent(tmp->right, ptr_node)) {
              return r_parrent;
          }

          return tmp;
      }

      return bst_r_parent(tmp->left, ptr_node);
  }

  // Поиск ближайшего левого родителя для заданного узла дерева
  node *bst_l_parent(node* tmp, const node *ptr_node){
      if (ptr_node == tmp) {
          return nullptr;
      }

      if (ptr_node->key < tmp->key) {
          if (node* l_parrent = bst_l_parent(tmp->left, ptr_node)) {
              return l_parrent;
          }

          return tmp;
      }

      return bst_l_parent(tmp->right, ptr_node);
  }


  // Поиск предыдущего по ключу узла
  node *bst_predecessor(node *ptr_root, node *ptr_node) {
      if (ptr_node->left) {
          return bst_max(ptr_node->left);
      }

      return bst_r_parent(ptr_root, ptr_node);
  };

  // Поиск следующего по ключу узла
  node *bst_successor(node *ptr_root, node *ptr_node) {
      if (ptr_node->right) {
          return bst_min(ptr_node->right);
      }

      return bst_l_parent(ptr_root, ptr_node);
  };

  // Рекурсивное копирование узлов дерева
  node *bst_copy(node* ptr_node) {
      if (!ptr_node) {
          return nullptr;
      }

      return new node(ptr_node->key, ptr_node->data, bst_copy(ptr_node->left), bst_copy(ptr_node->right));
  }

  // Рекурсивный поиск элементов в дереве
  T &bst_search(node* ptr_node, const K &key){
      traverse_counter++;

      if (!ptr_node) {
          throw std::runtime_error("unknown key");
      }

      if (ptr_node->key == key) {
          return ptr_node->data;
      }

      if (ptr_node->key < key) {
          return bst_search(ptr_node->right, key);
      }

      return bst_search(ptr_node->left, key);
  }

  // Рекурсивный поиск элементов в дереве
  virtual node *bst_insert(node* ptr_node, const K &key, const T &data, bool &is_inserted) {
      traverse_counter++;

      if (!ptr_node) {
          is_inserted = true;

          return new node(key, data);
      }

      if (ptr_node->key == key) {
          return ptr_node;
      }

      if (ptr_node->key > key) {
          ptr_node->left = bst_insert(ptr_node->left, key, data, is_inserted);
      }
      else {
          ptr_node->right = bst_insert(ptr_node->right, key, data, is_inserted);
      }

      return ptr_node;
  }

  // Рекурсивное формирование списка ключей в дереве в порядке обхода узлов по схеме L->t->R
  void bst_ltr_traversal(const node* ptr_node) {
      if (!ptr_node) {
          return;
      }

      bst_ltr_traversal(ptr_node->left);
      std::cout << ptr_node->key << " ";
      bst_ltr_traversal(ptr_node->right);
  }

  // Рекурсивный поиск узла с большим заданного ключом
  node *bst_find_greater_node(node* ptr_node, node** ptr_parrent, const K &key, bool &is_find) {
      traverse_counter++;

      if (!ptr_node) {
          return ptr_node;
      }

      if (ptr_node->key > key) {
          is_find = true;
          return ptr_node;
      }

      *ptr_parrent = ptr_node;
      return bst_find_greater_node(ptr_node->right, ptr_parrent, key, is_find);
  }

 public:

  /// Конструктор
  bst() : traverse_counter(0), root(nullptr), size(0) {};

  /// Конструктор копирования
  explicit bst(const bst<T,K> &old_tree) : traverse_counter(0), size(old_tree.size) {
      root = bst_copy(old_tree.root);
  };

  /// Деструктор
  ~bst() {
      bst_clear(root);
  }

  /// Опрос размера дерева
  [[nodiscard]] unsigned int get_size() const {
      return size;
  }

  /// Очистка дерева
  void clear() {
      bst_clear(root);
      size = 0;
      root = nullptr;
  }

  /// Проверка дерева на пустоту
  [[nodiscard]] bool is_empty() const {
      return size == 0;
  }

  /// Доступ по чтению/записи к данным по ключу
  T &get_by_key(const K key) {
      traverse_counter = 0;

      return bst_search(root, key);
  }

  /// Включение данных с заданным ключом
  bool insert(const K key, const T data) {
      traverse_counter = 0;

      bool is_inserted = false;

      root = bst_insert(root, key, data, is_inserted);

      if (is_inserted) {
          size++;
      }

      return is_inserted;
  }

  /// Удаление данных с заданным ключом
  bool remove(K key) {
      traverse_counter = 0;
      bool is_deleted;

      root = bst_remove(root, key, is_deleted);

      if (is_deleted) {
          size--;
      }

      return is_deleted;
  }

  /// Формирование списка ключей в дереве в порядке обхода узлов по схеме L->t->R
  void print_traversal() {
      bst_ltr_traversal(root);
  }

  /** Поиск и подъем в корень дерева узла с ближайшим ключом, большим заданного значения.
  Трудоёмкость операции – O(log n). */
  bool climbing_greater_node(const K key) {
      traverse_counter = 0;
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

#if !(USE_INSERT_IN_ROOT)
      node * new_root = new node(_key, _data);
#endif // !(USE_INSERT_IN_ROOT)

      if (parrent->left == tmp) {
          parrent->left = bst_remove(tmp, tmp->key, is_find);
      } else {
          parrent->right = bst_remove(tmp, tmp->key, is_find);
      }

#if USE_INSERT_IN_ROOT
      root = bst_root_insert(root, _key, _data, is_find);
#else //USE_INSERT_IN_ROOT
      new_root->left = root;
      new_root->right = parrent->right;
      parrent->right = nullptr;
      root = new_root;
#endif //USE_INSERT_IN_ROOT
      return true;
  }


  class iterator;
  class reverse_iterator;

  /// Запрос прямого итератора, установленного на узел дерева с минимальным ключом begin().
  iterator begin() {
      node *tmp = root;

      if (tmp) {
          while (tmp->left) {
              tmp = tmp->left;
          }
      }

      return bst::iterator(this, tmp);
  }

  /// Запрос обратного итератора, установленного на узел дерева с максимальным ключом rbegin().
  reverse_iterator rbegin() {
      node *tmp = root;

      if (tmp) {
          while (tmp->right) {
              tmp = tmp->right;
          }
      }

      return bst::reverse_iterator(this, tmp);
  }

  /// запрос «неустановленного» прямого итератора end().
  iterator end() {
      return bst::iterator(this, nullptr);
  }

  /// запрос «неустановленного» обратного итератора rend().
  reverse_iterator rend() {
      return bst::reverse_iterator(this, nullptr);
  }


  class iterator {
   private:
    bst *tree; // Корень
    node *cur; // Текущий узел
   public:
    explicit iterator(bst *ptr_tree, node *ptr_node) : tree(ptr_tree), cur(ptr_node) {}

    /// операция доступа по чтению и записи к данным текущего узла *.
    T &operator*() {
        if (*this == this->tree->end()) {
            throw std::runtime_error("unspecified iterator");
        }

        return cur->data;
    }

    /// операция перехода к следующему по ключу узлу в дереве ++.
    iterator &operator++() {
        if (*this == tree->end()) {
            throw std::runtime_error("unspecified iterator");
        }

        cur = tree->bst_successor(tree->root, cur);
        return *this;
    }

    /// операция перехода к предыдущему по ключу узлу в дереве --.
    iterator &operator--() {
        if (*this == tree->end()) {
            throw std::runtime_error("unspecified iterator");
        }

        this->cur = tree->bst_predecessor(tree->root, cur);
        return *this;
    }

    /// проверка равенства однотипных итераторов ==.
    bool operator==(const iterator &iter) {
        return tree == iter.tree && cur == iter.cur;
    }

    /// проверка неравенства однотипных итераторов !=.
    bool operator!=(const iterator &iter) {
        return tree != iter.tree || cur != iter.cur;
    }
  };

  class reverse_iterator {
   private:
    bst *tree; // Корень
    node *cur; // Текущий узел

   public:
    explicit reverse_iterator(bst *ptr_tree, node *ptr_node) : tree(ptr_tree), cur(ptr_node) {}

    /// операция доступа по чтению и записи к данным текущего узла *.
    T &operator*() {
        if (*this == this->tree->rend()) {
            throw std::runtime_error("unspecified iterator");
        }

        return cur->data;
    }

    /// операция перехода к предыдущему по ключу узлу в дереве ++.
    reverse_iterator &operator++() {
        if (*this == tree->rend()) {
            throw std::runtime_error("unspecified iterator");
        }

        cur = tree->bst_predecessor(tree->root, cur);
        return *this;
    }

    /// операция перехода к следующему по ключу узлу в дереве --.
    reverse_iterator &operator--() {
        if (*this == tree->rend()) {
            throw std::runtime_error("unspecified iterator");
        }

        this->cur = tree->bst_successor(tree->root, cur);
        return *this;
    }

    /// проверка равенства однотипных итераторов ==.
    bool operator==(const reverse_iterator &rev_iter) {
        return tree == rev_iter.tree && cur == rev_iter.cur;
    }

    /// проверка неравенства однотипных итераторов !=.
    bool operator!=(const reverse_iterator &rev_iter) {
        return tree != rev_iter.tree || cur != rev_iter.cur;
    }
  };

  /// Вывод структуры дерева на экран (так не стоит)
  template<class T1, class K1>
  friend std::ostream &operator<< (std::ostream &os, bst<T1,K1> &tree);

  /// Опрос числа узлов дерева, просмотренных предыдущей операцией
  [[nodiscard]] unsigned long get_traverse_counter() const {
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