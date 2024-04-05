#include "bst.h"

template<class K, class T>
class rbst : public bst<K, T>
{
  typedef class bst<K, T> super;
  typedef typename super::node node;
 protected:

  node *bst_insert(node *ptr_node, const K &key, const T &data, bool &is_inserted)
  {
      node *cur_node = ptr_node;
      bool traversed_right;
      std::vector<node *> traversed_nodes = {};

      while (cur_node)
      {
          if (rand() < RAND_MAX / (cur_node->subtree_size + 1))
          {
              ptr_node = super::bst_root_insert(cur_node, key, data, is_inserted); //NOTE: эта функция уже у нас есть
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
      if (traversed_nodes.size() > 0) {
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
