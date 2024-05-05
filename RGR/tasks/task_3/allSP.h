#ifndef ALLSP_H
#define ALLSP_H

#include "SPT.h"
template <class VERTEX_T, class EDGE_T> class allSP {
    graph<VERTEX_T, EDGE_T> *G;
    vector<SPT<VERTEX_T, EDGE_T>*> A;
public:
    explicit allSP(graph<VERTEX_T, EDGE_T> *G) : G(G), A(G->get_num_of_vertex()) {
        for (int s = 0; s < G->get_num_of_vertex(); s++) {
            A[s] = new SPT<VERTEX_T, EDGE_T>(G, s);
        }
    }

    EDGE_T *pathR(int s, int t) const {
        return A[s]->pathR(t);
    }

    [[nodiscard]] double dist(int s, int t) const {
        return A[s]->dist(t);
    }

    [[nodiscard]] double radius() const {
        int vmax = 0, wmax = 0;
        double max_dist = -1;

        for (int v = 0; v < G->get_num_of_vertex(); v++) {
            for (int w = 0; w < G->get_num_of_vertex(); w++) {
                if (v != w) {
                    double dist = A[v]->dist(w);
                    if (dist != INT_MAX && dist > max_dist) {
                        vmax = v;
                        wmax = w;
                        max_dist = dist;
                    }
                }
            }
        }

        cout << "Longest path: " << vmax << " -> " << wmax << " : " << max_dist / 2 << endl;
        /*
        EDGE_T* edge = A[vmax]->pathR(wmax);
        while (edge != nullptr) {
            cout << edge->get_v2()->get_index() << " -> ";
            edge = A[edge->get_v2()->get_index()]->pathR(vmax);
        }
        cout << wmax << endl; */

        return max_dist / 2;
    }

    void restart() {
        for (int s = 0; s < G->get_num_of_vertex(); s++) {
            A[s] = new SPT<VERTEX_T, EDGE_T>(G, s);
        }

        result();
    }

    void result() {
        radius();
    }

    void set_graph(graph<VERTEX_T, EDGE_T> *new_graph) {
        if (!new_graph) {
            throw std::runtime_error("Uninitialized graph_ptr!");
        }

        G = new_graph;
    }
};

#endif //ALLSP_H
