#include "bst.h"

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
      traverse_counter++;

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

public:

  bool insert(const K key, const T data) override
  {
      if (!root) {
          root = new node(key, data, 1);
          return true;
      }


      node *cur_node = root;
      bool traversed_right;
      bool is_inserted = false;
      std::vector<node *> traversed_nodes;

      while (cur_node)
      {
          if (rand() < RAND_MAX / (cur_node->subtree_size + 1))
          {
              if (cur_node == root) {
                  root = bst_root_insert(cur_node, key, data, is_inserted);
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

      for (std::vector<node *>::const_reverse_iterator r_iter = traversed_nodes.rbegin(); r_iter != traversed_nodes.rend(); ++r_iter)
      {
          (*r_iter)->subtree_size++;
      }

      return true;
  }
};
