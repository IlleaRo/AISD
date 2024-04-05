#include "bst.h"

template <class K, class T>
class rbst : public bst<K, T> {
  typedef class bst<K, T> super;
  typedef typename super::node node;
 protected:

  virtual void bst_show(node *ptr_node, const unsigned int level) {

  }

  node *bst_insert(node* ptr_node, const K &key, const T &data, bool &is_inserted) {

  }

  node *bst_remove(node *ptr_node, K key, bool &is_deleted) {

  }

};