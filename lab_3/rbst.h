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

      return (p->subtree_size = fix_size(p->left) + fix_size(p->right) + 1);
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

      return new_top;
  }

  node *rotate_left(node *ptr_node)
  {
      node *new_top = ptr_node->right;

      if (!new_top) return ptr_node;

      ptr_node->right = new_top->left;
      new_top->left = ptr_node;

      return new_top;
  }

  node *bst_root_insert(node *ptr_node, K key, T data, bool &is_inserted) override
  {
      node *new_node;
      node *cur_node;
      node *parent_node;
      bool went_right;

      if (!ptr_node) {
          is_inserted = true;
          return new node(key, data);
      }
      std::stack<node *> traversed_nodes;

      cur_node = ptr_node;
      parent_node = nullptr;

      while (cur_node) {
          if (cur_node->key == key) {
              is_inserted = false;
              return ptr_node;
          }
          traversed_nodes.push(cur_node);
          parent_node = cur_node;
          if (key < cur_node->key) {
              cur_node = cur_node->left;
          } else {
              cur_node = cur_node->right;
          }
      }

      new_node = new node(key, data);

      if (key < parent_node->key) {
          parent_node->left = new_node;
          went_right = false;
      } else {
          parent_node->right = new_node;
          went_right = true;
      }

      is_inserted = true;

      cur_node = new_node;


      while (!traversed_nodes.empty())
      {
          parent_node = traversed_nodes.top();
          traversed_nodes.pop();

          if(parent_node->key < cur_node->key) {
              parent_node->right = went_right ? rotate_left(cur_node) : cur_node;
              went_right = true;
          } else {
              parent_node->left = !went_right ? rotate_right(cur_node) : cur_node;
              went_right = false;
          }

          cur_node = parent_node;
      }
      if (went_right)
      {
          cur_node = rotate_left(cur_node);
      }
      else
      {
          cur_node = rotate_right(cur_node);
      }
      fix_size(cur_node);
      return cur_node;
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

  node* bst_join(node* a, node* b) {
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

      b->left = bst_join(a, b->left);
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
      super::traverse_counter = 0;
      if (!super::root)
      {
          super::root = new node(key, data);
          return true;
      }

      node *cur_node = super::root;
      bool traversed_right;
      bool is_inserted;
      std::stack<node *> traversed_nodes;

      while (cur_node)
      {
          super::traverse_counter++;
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

          traversed_nodes.push(cur_node);
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

      cur_node = new node(key, data);

_exit:
      if (traversed_right)
      {
          traversed_nodes.top()->right = cur_node;
      }
      else
      {
          traversed_nodes.top()->left = cur_node;
      }
      while (!traversed_nodes.empty())
      {
          traversed_nodes.top()->subtree_size++;
          traversed_nodes.pop();
      }

      return true;
  }

  bool remove(K key) override {
      super::traverse_counter = 0;
      if (!super::root) {
          return false;
      }

      node *ptr_node = super::root;
      std::stack<node*> traversed_nodes;
      bool traversed_right;

      while (ptr_node) {
          super::traverse_counter++;
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
