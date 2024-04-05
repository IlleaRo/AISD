#include "bst.h"

template <class K, class T>
class rbst : public bst<K, T> {
  typedef class bst<K, T> super;
  typedef typename super::node node;
  typedef typename super::bst_root_insert bst_root_insert;
 protected:

	 virtual void bst_show(node *ptr_node, const unsigned int level) {
	 
	 }

  node *bst_insert(node* ptr_node, const K &key, const T &data, bool &is_inserted) {
	  if (!ptr_node) {
		  ptr_node = new node(key, data);
		  ptr_node->subtree_size = 1; //TODO: Конструктор для узла с размером поддерева?
		  is_inserted = true;

		  return ptr_node;
	  }

	  if (rand() < RAND_MAX / (ptr_node->subtree_size + 1)) {
		  ptr_node = bst_root_insert(ptr_node, key, data, is_inserted); //NOTE: эта функция уже у нас есть
		  
		  return ptr_node;
	  }

	  if (key == ptr_node->key) {
		  is_inserted = false;

		  return ptr_node;
	  }

	  if (key < ptr_node->key) {
		  ptr_node->left = bst_insert(ptr_node->left, key, data, is_inserted);
	  }
	  else {
		  ptr_node->right = bst_insert(ptr_node->right, key, data, is_inserted);
	  }

	  if (is_inserted) {
		  ptr_node->subtree_size++;
	  }

	  return ptr_node;
  }

};