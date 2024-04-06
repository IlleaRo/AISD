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

  node* root_insert(node* ptr_node, const K &key, const T &data)
  {
      if(!ptr_node)
      {
          node *root = new node(key, data);
          return root;
      }
      if(key < ptr_node->key)
      {
          ptr_node->left = root_insert(ptr_node->left, key, data);
          return rotate_right(ptr_node);
      }
      else
      {
          ptr_node->right = root_insert(ptr_node->right, key, data);
          return rotate_left(ptr_node);
      }
  }

  node *bst_insert(node *ptr_node, const K &key, const T &data, bool &is_inserted)
  {
      node *cur_node = ptr_node;
      bool traversed_right;
      std::vector<node *> traversed_nodes = {};

      while (cur_node)
      {
          if (rand() < RAND_MAX / (cur_node->subtree_size + 1))
          {
              ptr_node = root_insert(cur_node, key, data);
              is_inserted = true;
              return ptr_node;
          }

          if (key == cur_node->key)
          {
              is_inserted = false;
              return ptr_node;
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

      cur_node = new node(key, data);
      cur_node->subtree_size = 1;
      if (!traversed_nodes.empty()) {
          if (traversed_right)
          {
              traversed_nodes[traversed_nodes.size() - 1]->right = cur_node;
          }
          else
          {
              traversed_nodes[traversed_nodes.size() - 1]->left = cur_node;
          }
          for (int i = 0; i < traversed_nodes.size(); i++)
          {
              traversed_nodes[i]->subtree_size++;
          }
      }
      else {
          ptr_node = cur_node;
      }
      is_inserted = true;
      return ptr_node;
  }
};
