#ifndef SPT_H
#define SPT_H

#include "../../graphs/graph.h"
#include <vector>

#include "PQi.h"


template <class VERTEX_T, class EDGE_T> class SPT {
    const graph<VERTEX_T, EDGE_T> *G;

    std::vector<EDGE_T *> spt;
    std::vector<double> wt;

public:
    SPT(graph<VERTEX_T, EDGE_T> *graph, int s /*что это?*/) :
        G(graph), spt(graph->get_num_of_vertex()), wt(graph->get_num_of_vertex(), graph->get_num_of_vertex()) {
        PQi<double> pQ(graph->get_num_of_vertex(), wt);

        for (int v = 0; v < graph->get_num_of_vertex(); ++v) {
            pQ.insert(v);
        }

        wt[s] = 0.0;
        pQ.lower(s);

        while (!pQ.empty()) {
            int v = pQ.getmin(); // wt[v] = 0.0; Don't use for Dijkstra's algorithm

            if (v != s && spt[v] == nullptr) {
                return;
            }

            for (edge_iterator_for_v<VERTEX_T, EDGE_T> iter = graph->edge_v_begin(graph->get_vertex(v));
                iter != graph->edge_v_end(graph->get_vertex(v)); ++iter) {
                int w = (*iter)->get_v2()->get_index();


                if ((*iter)->get_weight() < 0) {
                    throw runtime_error("Incorrect weight");
                }

                double P = wt[v] + (*iter)->get_weight();

                if (P < wt[w]) {
                    wt[w] = P;

                    pQ.lower(w);
                    spt[w] = *iter;
                }
            }
        }
    }

    EDGE_T *pathR(int v) const {
        return spt[v];
    }

    [[nodiscard]] double dist(int v) const {
        return wt[v];
    }
};

#endif //SPT_H
