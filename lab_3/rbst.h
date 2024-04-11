#include "bst.h"
#include <stack>

template<class K, class T>
class rbst : public bst<K, T>
{
  typedef class bst<K, T> super;
  typedef typename super::node node;
 protected:
  unsigned int fix_size(node* p) {
      if (!p) {
          return 0;
      }

      return (p->subtree_size = fixsize(p->left) + fixsize(p->right) + 1);
  }

  int get_subtree_size(node *ptr_node)
  {
      return ptr_node ? ptr_node->subtree_size : 0;
  }

  node *rotate_right(node *ptr_node)
  {
      node *new_top = ptr_node->left;

      if (!new_top) return ptr_node;

      ptr_node->left = new_top->right;
      new_top->right = ptr_node;
      new_top->subtree_size = ptr_node->subtree_size;

      ptr_node->subtree_size = get_subtree_size(ptr_node->left) + get_subtree_size(ptr_node->right) + 1;

      return new_top;
  }

  node *rotate_left(node *ptr_node)
  {
      node *new_top = ptr_node->right;

      if (!new_top) return ptr_node;

      ptr_node->right = new_top->left;
      new_top->left = ptr_node;
      new_top->subtree_size = ptr_node->subtree_size;

      ptr_node->subtree_size = get_subtree_size(ptr_node->left) + get_subtree_size(ptr_node->right) + 1;

      return new_top;
  }

  node *bst_root_insert(node *ptr_node, K key, T data, bool &is_inserted)
  {
      node *new_node;
      node *cur_node;
      node *parent_node;
      if (!ptr_node) {
          is_inserted = true;
          return new node(key, data, 1);
      }

      cur_node = ptr_node;
      parent_node = nullptr;

      while (cur_node) {
          if (cur_node->key == key) {
              is_inserted = false;
              return ptr_node;
          }
          parent_node = cur_node;
          if (key < cur_node->key) {
              cur_node = cur_node->left;
          } else {
              cur_node = cur_node->right;
          }
      }

      new_node = new node(key, data, 1);

      if (key < parent_node->key) {
          parent_node->left = new_node;
      } else {
          parent_node->right = new_node;
      }

      is_inserted = true;

      if (is_inserted && parent_node->left == new_node) {
          return rotate_right(ptr_node);
      } else if (is_inserted && parent_node->right == new_node) {
          return rotate_left(ptr_node);
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

  node* bst_join(node* a, node* b) { //fixme: скорее всего, я источник проблем при удалении.
      if (!a) {
          return b;
      }

      if (!b) {
          return a;
      }

      node* ret = a;
      bool is_first = true;
      node *parent = nullptr;
      bool is_right = false;
      node* cur_a = a;
      node* cur_b = b;

      while (true) {
          if (rand() / (RAND_MAX / (cur_a->subtree_size + cur_b->subtree_size + 1)) < cur_a->subtree_size) {
              if (!cur_a->right) {
                  cur_a->right = cur_b;

                  if (is_first) {
                      return a;
                  }

                  return ret;
              }
              if (is_first) {
                  ret = a;
                  parent = a;

                  is_first = false;
                  continue;
              }

              if (is_right) {
                  parent->right = cur_a;
              } else {
                  parent->left = cur_a;
              }

              parent = cur_a;
              is_right = true;
              cur_a = cur_a->right;
          } else {
              if (!cur_b->left) {
                  cur_b->left = cur_a;

                  if (is_first) {
                      return b;
                  }

                  return ret;
              }

              if (is_first) {
                  ret = b;
                  parent = b;

                  is_first = false;
                  continue;
              }
              if (is_right) {
                  parent->right = cur_b;
              } else {
                  parent->left = cur_b;
              }

              parent = cur_b;
              is_right = false;

              cur_b = cur_b->left;
          }
      }
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

              break;
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
      }

      if (traversed_right)
      {
          (*traversed_nodes.rbegin())->right = cur_node;
      }
      else
      {
          (*traversed_nodes.rbegin())->left = cur_node;
      }

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

          fix_size(tmp);

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
