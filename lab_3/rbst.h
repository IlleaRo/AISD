#include "bst.h"

template <class T, class K>
class rbst : public bst<T, K> {
  typedef typename bst<T, K>::node node;
 private:
  int rand_bool() {
      return rand() % 2;
  }
 protected:

  virtual void bst_show(node *ptr_node, const unsigned int level) {

  }

  node *bst_insert(node* ptr_node, const K &key, const T &data, bool &is_inserted) {

  }

  node *bst_remove(node *ptr_node, K key, bool &is_deleted) {

  }
};