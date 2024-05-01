#ifndef SHORTEST_WAY_H
#define SHORTEST_WAY_H

#include "SEARCH.h"
#include "GQ.h"

#include <vector>


template <class VERTEX_T, class EDGE_T>
class shortest_way : public SEARCH<VERTEX_T, EDGE_T>{
    using SEARCH<VERTEX_T, EDGE_T>::ord;
    using SEARCH<VERTEX_T, EDGE_T>::graph_ptr;
    using SEARCH<VERTEX_T, EDGE_T>::cnt;
    using SEARCH<VERTEX_T, EDGE_T>::search;

    std::vector<unsigned long> st;

    void searchC(EDGE_T edge) override {
        GQ<EDGE_T> queue(graph_ptr->get_num_of_vertex());

        queue.put(edge);
        ord[edge.get_v2()->get_index()] = cnt++;

        while (!queue.is_empty()) {
            edge = queue.get();
            st[edge.get_v2()->get_index()] = edge.get_v1()->get_index();

            for (edge_iterator_for_v<VERTEX_T, EDGE_T> iter = graph_ptr->edge_v_begin(edge.get_v2());
                iter != graph_ptr->edge_v_end(edge.get_v2()); ++iter) {

                if (ord[(*iter)->get_v2()->get_index()] == -1) {
                    queue.put(EDGE_T(edge.get_v2(), (*iter)->get_v2()));
                    ord[(*iter)->get_v2()->get_index()] = cnt++;
                } else {
                    if (st[(*iter)->get_v2()->get_index()] == -1) {
                        queue.update(EDGE_T(edge.get_v2(), (*iter)->get_v2()));
                    }
                }
            }
        }
    }
public:
    explicit shortest_way(graph<VERTEX_T, EDGE_T> *graph) :
        SEARCH<VERTEX_T, EDGE_T>(graph), st(graph->get_num_of_vertex(), -1) {
        if (!graph) {
            throw std::runtime_error("Uninitialized graph_ptr!");
        }

        if (graph->get_type() == NON_DIRECTED) {
            throw std::runtime_error("Yor are using non directed graph!");
        }

        search();
    }

    [[nodiscard]] int ST(const int v) const {
        return st[v];
    }
};



#endif //SHORTEST_WAY_H
