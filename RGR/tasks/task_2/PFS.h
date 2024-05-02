#ifndef SHORTEST_WAY_H
#define SHORTEST_WAY_H

#include "SEARCH.h"
#include "randomized_queue.h"

#include <vector>
#include <algorithm>


template <class VERTEX_T, class EDGE_T>
class PFS : public SEARCH<VERTEX_T, EDGE_T>{
    using SEARCH<VERTEX_T, EDGE_T>::ord;
    using SEARCH<VERTEX_T, EDGE_T>::graph_ptr;
    using SEARCH<VERTEX_T, EDGE_T>::cnt;
    using SEARCH<VERTEX_T, EDGE_T>::search;

    std::vector<std::vector<unsigned long>> previous_vertexes;

    void searchC(EDGE_T edge) override {
        randomized_queue<EDGE_T> queue(graph_ptr->get_num_of_vertex());
        const unsigned long from = edge.get_v2()->get_index();

        queue.put(edge);
        ord[edge.get_v2()->get_index()] = cnt++;

        while (!queue.is_empty()) {
            edge = queue.get();
            previous_vertexes[from][edge.get_v2()->get_index()] = edge.get_v1()->get_index();

            for (edge_iterator_for_v<VERTEX_T, EDGE_T> iter = graph_ptr->edge_v_begin(edge.get_v2());
                iter != graph_ptr->edge_v_end(edge.get_v2()); ++iter) {

                if (ord[(*iter)->get_v2()->get_index()] == -1) {
                    queue.put(EDGE_T(edge.get_v2(), (*iter)->get_v2()));
                    ord[(*iter)->get_v2()->get_index()] = cnt++;
                }
            }
        }
    }

    void shortest(unsigned long from, unsigned long to) {
        std::vector<unsigned long> path;

        unsigned long cur = to;         //текущая вершина пути
        path.push_back(cur);

        while (previous_vertexes[from][cur] != cur) {   //пока существует предыдущая вершина
            cur = previous_vertexes[from][cur];        //переходим в неё
            path.push_back(cur);    //и дописываем к пути
        }

        if (previous_vertexes[from][cur] != from) {
            return;
        }

        std::reverse(path.begin(), path.end());

        std::cout<<to<<" : ";

        for (unsigned long v: path) {
            std::cout << v << " ";
        }

        std::cout<<std::endl;
    }

    void get_all_shortest_paths() {
        for (vertex_iterator<VERTEX_T> iter = graph_ptr->vertex_begin(); iter != graph_ptr->vertex_end(); ++iter) {
            ord = std::vector<unsigned long>(graph_ptr->get_num_of_vertex(), -1);
            //cnt = 0;

            search(*iter);
        }
    }
public:
    explicit PFS(graph<VERTEX_T, EDGE_T> *graph) :
            SEARCH<VERTEX_T, EDGE_T>(graph) {
        previous_vertexes = std::vector<std::vector<unsigned long>>(graph->get_num_of_vertex(), std::vector<unsigned long>(graph->get_num_of_vertex()));

        for (unsigned long i = 0; i < graph->get_num_of_vertex(); ++i) {
            for (unsigned long j = 0; j < graph->get_num_of_vertex(); ++j) {
                previous_vertexes[i][j] = j;
            }
        }

        if (!graph) {
            throw std::runtime_error("Uninitialized graph_ptr!");
        }

        if (graph->get_type() == NON_DIRECTED) {
            throw std::runtime_error("Yor are using non directed graph!");
        }

        get_all_shortest_paths();
    }
    PFS(const PFS<VERTEX_T, EDGE_T> &old_pfs) :
            SEARCH<VERTEX_T, EDGE_T>(old_pfs.graph_ptr), previous_vertexes(old_pfs.previous_vertexes) {}

    void result() {
        for (vertex_iterator<VERTEX_T> iter = graph_ptr->vertex_begin(); iter != graph_ptr->vertex_end(); ++iter) {
            std::cout<<"Shortest ways from "<<(*iter)->get_index()<<std::endl;
            for (unsigned long i = 0; i < graph_ptr->get_num_of_vertex(); i++) {
                if (i == (*iter)->get_index()) {
                    continue;
                }

                shortest((*iter)->get_index(), i);
            }
        }
    }

    void set_graph(graph<VERTEX_T, EDGE_T> *new_graph) {
        if (!new_graph) {
            throw std::runtime_error("Uninitialized graph_ptr!");
        }

        if (new_graph->get_type() != DIRECTED) {
            throw std::runtime_error("Yor are using non directed graph!");
        }

        if (graph_ptr != new_graph) {
            graph_ptr = new_graph;
        }
    }

    void restart() {
        for (unsigned long i = 0; i < graph_ptr->get_num_of_vertex(); ++i) {
            for (unsigned long j = 0; j < graph_ptr->get_num_of_vertex(); ++j) {
                previous_vertexes[i][j] = j;
            }
        }

        get_all_shortest_paths();
    }
};



#endif //SHORTEST_WAY_H
