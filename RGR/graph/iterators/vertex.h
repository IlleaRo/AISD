#ifndef VERTEX_ITERATOR_H
#define VERTEX_ITERATOR_H

#include <vector>

template <class VERTEX_T>
class vertex_iterator {
    typename std::vector<VERTEX_T *>::iterator it;
    bool undefined;

    public:
    explicit vertex_iterator() : it(), undefined(true) {}
    explicit vertex_iterator(typename std::vector<VERTEX_T *>::iterator it) : it(it), undefined(false) {}

    VERTEX_T *operator*() {
        if (undefined || *it == nullptr) {
            throw std::out_of_range("Out of range");
        }
        return *it;
    }

    vertex_iterator &operator++() {
        if (undefined || *it == nullptr) return *this;
        ++it;
        return *this;
    }

    bool operator!=(const vertex_iterator& other) const {
        if (undefined || *it == nullptr) return false;
        return it != other.it;
    }

    bool operator==(const vertex_iterator& other) const {
        if (undefined || *it == nullptr) return false;
        return it == other.it;
    }

    bool is_undefined() {
        return undefined;
    }
};

#endif //VERTEX_ITERATOR_H
