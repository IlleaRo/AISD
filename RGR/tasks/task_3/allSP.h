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
};

#endif //ALLSP_H
