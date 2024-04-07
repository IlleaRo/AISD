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

  node* rotate_right(node* ptr_node)
  {
      node* new_top = ptr_node->left;

      if( !new_top ) return ptr_node;

      ptr_node->left = new_top->right;
      new_top->right = ptr_node;
      new_top->subtree_size = ptr_node->subtree_size;

      ptr_node->subtree_size = get_subtree_size(ptr_node->left) + get_subtree_size(ptr_node->right) + 1;

      return new_top;
  }

  node* rotate_left(node* ptr_node)
  {
      node* new_top = ptr_node->right;

      if( !new_top ) return ptr_node;

      ptr_node->right = new_top->left;
      new_top->left = ptr_node;
      new_top->subtree_size = ptr_node->subtree_size;

      ptr_node->subtree_size = get_subtree_size(ptr_node->left) + get_subtree_size(ptr_node->right) + 1;

      return new_top;
  }

  node* bst_root_insert(node* ptr_node, K key, T data, bool& is_inserted) {
      super::traverse_counter++;

      if (!ptr_node) {
          is_inserted = true;
          return new node(key, data, 1);
      }

      if (ptr_node->key == key) {
          is_inserted = false;
          return ptr_node;
      }

      if (key < ptr_node->key) {
          ptr_node->left = bst_root_insert(ptr_node->left, key, data, is_inserted);
          if (is_inserted) {
              return rotate_right(ptr_node);
          }

          return ptr_node;
      }

      ptr_node->right = bst_root_insert(ptr_node->right, key, data, is_inserted);

      if (is_inserted) {
          return rotate_left(ptr_node);
      }

      return ptr_node;
  }

  node* bst_join(node* a, node* b) {
      if (!a) {
          return b;
      }

      if (!b) {
          return a;
      }

      node* ret = nullptr;
      node* parent = nullptr;
      node* cur_a = a;
      node* cur_b = b;

      while (cur_a && cur_b) {
          if (rand() / (RAND_MAX / (cur_a->subtree_size + cur_b->subtree_size + 1)) < cur_b->subtree_size) {
              if (parent) {
                  parent->right = cur_a;
              }
              else {
                  ret = cur_a;
              }

              parent = cur_a;
              cur_a = cur_a->right;
          }
          else {
              if (parent) {
                  parent->left = cur_b;
              }
              else {
                  ret = cur_b;
              }

              parent = cur_b;
              cur_b = cur_b->left;
          }
      }

      if (cur_a) {
          parent->right = cur_a;
      }
      else {
          parent->left = cur_b;
      }

      ret->subtree_size = a->subtree_size + b->subtree_size + 1;

      return ret;
  }

public:

  bool insert(const K key, const T data) override
  {
      if (!super::root) {
          super::root = new node(key, data, 1);
          return true;
      }


      node *cur_node = super::root;
      bool traversed_right;
      bool is_inserted = false;
      std::vector<node *> traversed_nodes;

      while (cur_node)
      {
          if (rand() < RAND_MAX / (cur_node->subtree_size + 1))
          {
              if (cur_node == super::root) {
                  super::root = bst_root_insert(cur_node, key, data, is_inserted);
                  if (is_inserted) {
                      return true;
                  }

                  return false;
              }


              cur_node = bst_root_insert(cur_node, key, data, is_inserted);

              
              if (!is_inserted) {
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

      if (!cur_node) {
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

  virtual bool remove(K key) override {
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

              super::size--;
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

          super::size--;
          return true;
      }

      return false;
  }
};
