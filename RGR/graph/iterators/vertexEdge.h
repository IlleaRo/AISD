#ifndef VERTEXEDGE_ITERATOR_H
#define VERTEXEDGE_ITERATOR_H

template <class VERTEX_T, class EDGE_T>
class graph;

template <class VERTEX_T, class EDGE_T>
class edge_iterator_for_v {
    VERTEX_T *vertex;
    graph<VERTEX_T, EDGE_T> *graph_ptr;
    EDGE_T *cur_edge;
    bool undefined;
    public:
    edge_iterator_for_v() : vertex(nullptr), graph_ptr(nullptr), cur_edge(nullptr), undefined(true) {}

    edge_iterator_for_v(graph<VERTEX_T, EDGE_T> *graph, VERTEX_T *vertex) {
        this->vertex = vertex;
        this->cur_edge = graph->get_first_edge(vertex);
        this->graph_ptr = graph;
        undefined = false;
    }

    edge_iterator_for_v(edge_iterator_for_v const &other) {
        vertex = other.vertex;
        graph_ptr = other.graph_ptr;
        cur_edge = other.cur_edge;
        undefined = false;
    }

    EDGE_T *operator*() {
        if (undefined || *this == graph_ptr->edge_v_end(vertex)) {
            throw std::out_of_range("Out of range");
        }

        return cur_edge;
    }

    edge_iterator_for_v &operator++() {
        if (undefined || *this == graph_ptr->edge_v_end(vertex)) {
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

    bool is_undefined() {
        return undefined;
    }
};

#endif //VERTEXEDGE_ITERATOR_H
