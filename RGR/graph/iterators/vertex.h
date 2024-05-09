#ifndef VERTEX_ITERATOR_H
#define VERTEX_ITERATOR_H

#include <vector>

template <class VERTEX_T>
class vertexIterator {
    typename std::vector<VERTEX_T *>::iterator vectorIterator;
    bool graphUndefined;

    public:
    explicit vertexIterator() : vectorIterator(), graphUndefined(true) {}
    explicit vertexIterator(typename std::vector<VERTEX_T *>::iterator vectorIterator) : vectorIterator(vectorIterator), graphUndefined(false) {}

    VERTEX_T *operator*() {
        if (graphUndefined || *vectorIterator == nullptr) {
            throw std::out_of_range("out of range exception");
        }
        return *vectorIterator;
    }

    vertexIterator &operator++() {
        if (graphUndefined || *vectorIterator == nullptr) return *this;
        ++vectorIterator;
        return *this;
    }

    bool operator!=(const vertexIterator& other) const {
        if (graphUndefined || *vectorIterator == nullptr) return false;
        return vectorIterator != other.vectorIterator;
    }

    bool operator==(const vertexIterator& other) const {
        if (graphUndefined || *vectorIterator == nullptr) return false;
        return vectorIterator == other.vectorIterator;
    }

    bool isUndefined() {
        return graphUndefined;
    }
};

#endif //VERTEX_ITERATOR_H
