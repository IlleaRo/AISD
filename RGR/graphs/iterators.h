#ifndef RGR_ITERATORS_H
#define RGR_ITERATORS_H

#include <vector>
#include "graph.h"

template <class VERTEX_T>
class vertex_iterator {
    typename std::vector<VERTEX_T *>::iterator it;
    bool undefined;

public:
    explicit vertex_iterator() : it(), undefined(true) {}
    explicit vertex_iterator(typename std::vector<VERTEX_T *>::iterator it) : it(it), undefined(false) {}

    VERTEX_T *operator*() {
        if (undefined) return nullptr;
        return *it;
    }

    vertex_iterator &operator++() {
        if (undefined) return *this;
        ++it;
        return *this;
    }

    bool operator!=(const vertex_iterator& other) const {
        if (undefined) return false;
        return it != other.it;
    }

    bool operator==(const vertex_iterator& other) const {
        if (undefined) return false;
        return it == other.it;
    }

    bool is_undefined() {
        return undefined;
    }
};

template <class VERTEX_T, class EDGE_T>
class graph;

template <class VERTEX_T, class EDGE_T>
class edge_iterator_for_v {
    VERTEX_T *vertex;
    graph<VERTEX_T, EDGE_T> *graph_ptr;
    EDGE_T *cur_edge;
public:
    edge_iterator_for_v(graph<VERTEX_T, EDGE_T> *graph, VERTEX_T *vertex)
    : vertex(vertex), graph_ptr(graph) {}

    edge_iterator_for_v(edge_iterator_for_v const &other) {
        vertex = other.vertex;
        graph_ptr = other.graph_ptr;
        cur_edge = other.cur_edge;
    }

    EDGE_T *operator*() {
        if (*this == graph_ptr->edge_v_end(vertex)) {
            throw std::out_of_range("Out of range");
        }

        return cur_edge;
    }

    edge_iterator_for_v &operator++() {
        if (*this == graph_ptr->edge_v_end(vertex)) {
            throw std::out_of_range("Out of range");
        }

        cur_edge = graph_ptr->get_next_edge(vertex, cur_edge);
        return *this;
    }

    bool operator!=(const edge_iterator_for_v& other) const {
        if (vertex != other.vertex) {
            return true;
        }

        if (cur_edge != other.cur_edge) {
            return true;
        }

        return false;
    }

    bool operator==(const edge_iterator_for_v& other) const {
        if (vertex != other.vertex) {
            return false;
        }

        if (cur_edge != other.cur_edge) {
            return false;
        }

        return true;
    }

    void set_cur_edge(EDGE_T *new_cur_edge) {
        cur_edge = new_cur_edge;
    }
};

template <class VERTEX_T, class EDGE_T>
class edge_iterator {
    VERTEX_T *cur_vertex;
    graph<VERTEX_T, EDGE_T> *graph_ptr;
    EDGE_T *cur_edge;
    bool undefined;

public:
    explicit edge_iterator() : graph_ptr(0), undefined(true) {}
    explicit edge_iterator(graph<VERTEX_T, EDGE_T> *graph) : graph_ptr(graph), undefined(false) {}

    EDGE_T *operator*() {
        if (undefined || *this == graph_ptr->edge_end()) {
            throw std::out_of_range("Out of range");
        }

        return cur_edge;
    }

    edge_iterator &operator++() {
        if (undefined) return *this;
        if (*this == graph_ptr->edge_end()) {
            throw std::out_of_range("Out of range");
        }

        if ((cur_edge = graph_ptr->get_next_edge(cur_vertex, cur_edge))) {
            return *this;
        }

        for (unsigned long i = cur_vertex->get_index() + 1; i < graph_ptr->get_num_of_vertex(); ++i) {
            cur_vertex = graph_ptr->vertexes[i];
            if ((cur_edge = graph_ptr->get_first_edge(cur_vertex))) {
                return *this;
            }
        }

        *this = graph_ptr->edge_end();

        return *this;
    }

    bool operator!=(const edge_iterator& other) const {
        if (undefined) return false;
        if (cur_vertex != other.cur_vertex) {
            return true;
        }

        if (cur_edge != other.cur_edge) {
            return true;
        }

        return false;
    }

    bool operator==(const edge_iterator& other) const {
        if (undefined) return false;
        if (cur_vertex != other.cur_vertex) {
            return false;
        }

        if (cur_edge != other.cur_edge) {
            return false;
        }

        return true;
    }

    void set_cur_edge(EDGE_T *new_cur_edge) {
        if (undefined) return;
        cur_edge = new_cur_edge;
    }

    void set_cur_vertex(VERTEX_T *new_cur_vertex) {
        if (undefined) return;
        cur_vertex = new_cur_vertex;
    }

    bool is_undefined() {
        return undefined;
    }
};

#endif //RGR_ITERATORS_H
