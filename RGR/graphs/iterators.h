#ifndef RGR_ITERATORS_H
#define RGR_ITERATORS_H

#include <vector>

template <class VERTEX_T>
class vertex_iterator {
    typename std::vector<VERTEX_T *>::iterator it;

public:
    explicit vertex_iterator(typename std::vector<VERTEX_T *>::iterator it) : it(it) {}

    VERTEX_T *operator*() {
        return *it;
    }

    vertex_iterator &operator++() {
        ++it;
        return *this;
    }

    vertex_iterator &operator--() {
        --it;
        return *this;
    }

    bool operator!=(const vertex_iterator& other) const {
        return it != other.it;
    }

    bool operator==(const vertex_iterator& other) const {
        return it == other.it;
    }
};
#endif //RGR_ITERATORS_H
