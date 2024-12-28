#ifndef ALLSP_H
#define ALLSP_H

#include "SPT.h"

template <class VERTEX_T, class EDGE_T> class allSP {
    graph<VERTEX_T, EDGE_T> *G;
    vector<SPT<VERTEX_T, EDGE_T>*> A;

    vector<int> radius_path;
    double radius;

    vector<int> get_path(int from, int to) {
        EDGE_T* edge = A[from]->pathR(to);

        vector<int> path;

        while (edge != nullptr) {
            path.push_back(edge->get_v2()->get_index());
            if (edge->get_v2()->get_index() == from) {
                break;
            }

            edge = A[from]->pathR(edge->get_v1()->get_index());
        }
        path.push_back(from);

        reverse(path.begin(), path.end());

        return path;
    }

    EDGE_T *pathR(int s, int t) const {
        return A[s]->pathR(t);
    }

    [[nodiscard]] double dist(int s, int t) const {
        return A[s]->dist(t);
    }

    void set_radius() {
        double max_dist;

        radius_path.clear(); // Очищаем текущий радиус-путь
        vector<int> longest_path(G->get_num_of_vertex()); // Текущий эксцентриситет

        for (int v = 0; v < G->get_num_of_vertex(); v++) {
            max_dist = -1;
            longest_path.clear();
            for (int w = 0; w < G->get_num_of_vertex(); w++) {
                /*Здесь каждая получаем путь из v->w*/

                if (v != w) {
                    if (const double dist = A[v]->dist(w); dist != INT_MAX && dist > max_dist) {
                        longest_path = get_path(v, w);
                        max_dist = dist;
                    }
                }
            }
            if (max_dist != -1 && (radius_path.empty() || radius > max_dist)) {
                radius_path = longest_path;
                radius = max_dist;
            }
        }
    }

public:
    explicit allSP(graph<VERTEX_T, EDGE_T> *G) : G(G), A(G->get_num_of_vertex()) {
            restart();
    }

    allSP(const allSP<VERTEX_T, EDGE_T> &old_allSP) : G(old_allSP.G), radius(old_allSP.radius),
        radius_path(old_allSP.radius_path) {};

    void restart() {
        for (int s = 0; s < G->get_num_of_vertex(); s++) {
            A[s] = new SPT<VERTEX_T, EDGE_T>(G, s);
        }

        set_radius();
    }

    [[nodiscard]] double get_radius() const {
        return radius;
    }

    [[nodiscard]] vector<int> get_radius_path() const {
        return radius_path;
    }

    void set_graph(graph<VERTEX_T, EDGE_T> *new_graph) {
        if (!new_graph) {
            throw std::runtime_error("Uninitialized graph_ptr!");
        }

        G = new_graph;
    }

    void print_path() {
        for (const int vertex : radius_path) {
            cout<<vertex<<(vertex != radius_path.back()? " -> " : "");
        }
    }
};

#endif //ALLSP_H
