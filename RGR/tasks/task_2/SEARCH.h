#ifndef SEARCH_H
#define SEARCH_H

#include "../../graphs/graph.h"

#include <vector>

template <class VERTEX_T, class EDGE_T>
class SEARCH {
protected:
    graph<VERTEX_T, EDGE_T> *graph_ptr;
    unsigned long cnt;

    std::vector<unsigned long> ord;
    virtual void searchC(EDGE_T edge) = 0;

    void search(VERTEX_T *v) {
        searchC(EDGE_T(v, v));

        for (vertex_iterator iter = graph_ptr->vertex_begin(); iter != graph_ptr->vertex_end(); ++iter) {
            if ((*iter) != v && ord[(*iter)->get_index()] == -1) {
                searchC(EDGE_T(*iter, *iter));
            }
        }
    }
public:
    explicit SEARCH (graph<VERTEX_T, EDGE_T> *graph) :
        graph_ptr(graph), cnt(0), ord(graph->get_num_of_vertex(), -1) {}

    unsigned long operator[] (const unsigned long v) const {
        return ord[v];
    }
};



#endif //SEARCH_H
