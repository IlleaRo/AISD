#include "bst.h"
#include <stack>

template<class K, class T>
class rbst : public bst<K, T>
{
  typedef class bst<K, T> super;
  typedef typename super::node node;
 protected:


  int get_subtree_size(node *ptr_node)
  {
      return ptr_node ? ptr_node->subtree_size : 0;
  }

    void fix_size(node* p) {
        p->subtree_size = get_subtree_size(p->left)+get_subtree_size(p->right)+1;
    }

  node *rotate_right(node *ptr_node)
  {
      node *new_top = ptr_node->left;

      if (!new_top) return ptr_node;

      ptr_node->left = new_top->right;
      new_top->right = ptr_node;

      if (new_top->left) fix_size(new_top->left);
      if (new_top->right) fix_size(new_top->right);
      fix_size(new_top);

      return new_top;
  }

  node *rotate_left(node *ptr_node)
  {
      node *new_top = ptr_node->right;

      if (!new_top) return ptr_node;

      ptr_node->right = new_top->left;
      new_top->left = ptr_node;

      if (new_top->left) fix_size(new_top->left);
      if (new_top->right) fix_size(new_top->right);
      fix_size(new_top);

      return new_top;
  }

    node *bst_root_insert(node *ptr_node, K key, T data, bool &is_inserted)
    {
        if (!ptr_node)
            return new node(key, data, 1);
        if (key < ptr_node->key)
        {
            ptr_node->left = bst_root_insert(ptr_node->left, key, data, is_inserted);
            ptr_node = rotate_right(ptr_node);
        }
        else
        {
            ptr_node->right = bst_root_insert(ptr_node->right, key, data, is_inserted);
            ptr_node = rotate_left(ptr_node);
        }
        return ptr_node;
    }

  bool check_subtree_sizes_node(node *ptr_node)
  {
      if (!ptr_node)
          return true;

      bool left_correct = check_subtree_sizes_node(ptr_node->left);
      bool right_correct = check_subtree_sizes_node(ptr_node->right);

      int expected_size = get_subtree_size(ptr_node->left) + get_subtree_size(ptr_node->right) + 1;
      if (ptr_node->subtree_size != expected_size) {
          return false;
      }

      return left_correct && right_correct;
  }

node *bst_join(node *a, node *b) {
      if (!a) {
          return b;
      }

      if (!b) {
          return a;
      }

      if (rand() / (RAND_MAX / (a->subtree_size + b->subtree_size + 1)) < a->subtree_size) {
          a->right = bst_join(a->right, b);
          fix_size(a);
          return a;
      }

      b->left = bst_join(b->left, b);
      fix_size(b);
      return b;
  }

public:
  [[nodiscard]] unsigned int get_size() override {
      return get_subtree_size(super::root);
  }

  bool check_subtree_sizes() {
      return check_subtree_sizes_node(super::root);
  }

  bool insert(const K key, const T data) override
  {
      if (!super::root)
      {
          super::root = new node(key, data, 1);
          return true;
      }

      node *cur_node = super::root;
      bool traversed_right;
      bool is_inserted;
      std::vector<node *> traversed_nodes;

      while (cur_node)
      {
          if (rand() < RAND_MAX / (cur_node->subtree_size + 1))
          {
              if (cur_node == super::root)
              {
                  super::root = bst_root_insert(cur_node, key, data, is_inserted);

                  if (is_inserted)
                  {
                      return true;
                  }

                  return false;
              }

              cur_node = bst_root_insert(cur_node, key, data, is_inserted);

              if (!is_inserted)
              {
                  return false;
              }

              goto _exit;
          }

          if (key == cur_node->key)
          {
              return false;
          }

          traversed_nodes.push_back(cur_node);
          if (key < cur_node->key)
          {
              cur_node = cur_node->left;
              traversed_right = false;
          }
          else
          {
              cur_node = cur_node->right;
              traversed_right = true;
          }
      }

      if (!cur_node)
      {
          cur_node = new node(key, data, 1);
          if (traversed_right) {
              (*traversed_nodes.rbegin())->right = cur_node;
          } else {
              (*traversed_nodes.rbegin())->left = cur_node;
          }
      }

_exit:
      for (typename std::vector<node *>::const_reverse_iterator r_iter = traversed_nodes.rbegin();
           r_iter != traversed_nodes.rend();
           ++r_iter)
      {
          (*r_iter)->subtree_size++;
      }

      return true;
  }

  bool remove(K key) override {
      if (!super::root) {
          return false;
      }

      node *ptr_node = super::root;
      std::stack<node*> traversed_nodes;
      bool traversed_right;

      while (ptr_node) {
          if (key < ptr_node->key) {
              traversed_nodes.push(ptr_node);

              ptr_node = ptr_node->left;
              traversed_right = false;

              continue;
          }

          if (key > ptr_node->key) {
              traversed_nodes.push(ptr_node);

              ptr_node = ptr_node->right;
              traversed_right = true;

              continue;
          }

          node* tmp = bst_join(ptr_node->left, ptr_node->right);

          if (ptr_node == super::root) {
              delete ptr_node;
              super::root = tmp;

              return true;
          }

          delete ptr_node;


          if (traversed_right) {
              traversed_nodes.top()->right = tmp;
          }
          else {
              traversed_nodes.top()->left = tmp;
          }

          while (!traversed_nodes.empty()) {
              node* top_node = traversed_nodes.top();
              top_node->subtree_size--;
              traversed_nodes.pop();
          }

          return true;
      }

      return false;
  }
};
