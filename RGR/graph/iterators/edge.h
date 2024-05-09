#ifndef EDGE_ITERATOR_H
#define EDGE_ITERATOR_H

#include "../graph.h"

template <class VERTEX_T, class EDGE_T>
class graph;

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

        next:
        do {
            if ((cur_edge = graph_ptr->get_next_edge(cur_vertex, cur_edge))) {
                if (graph_ptr->get_type() == NON_DIRECTED &&
                    cur_vertex == cur_edge->get_v2()) {
                    continue;
                }

                return *this;
            }
        } while (cur_edge);

        for (unsigned long i = cur_vertex->get_index() + 1; i < graph_ptr->get_num_of_vertex(); ++i) {
            cur_vertex = graph_ptr->vertexes[i];
            if ((cur_edge = graph_ptr->get_first_edge(cur_vertex))) {
                // Пропускаем повторные рёбра
                if (graph_ptr->get_type() == NON_DIRECTED && cur_vertex == cur_edge->get_v2()) {
                    goto next;
                }

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

#endif //EDGE_ITERATOR_H
