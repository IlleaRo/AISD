#ifndef SHORTEST_WAY_H
#define SHORTEST_WAY_H

#include "SEARCH.h"
#include "randomized_queue.h"

#include <vector> // Основа многомерных массивов
#include <algorithm> // Используется для reverse

using namespace std;

template <class VERTEX_T, class EDGE_T>
class PFS final : public SEARCH<VERTEX_T, EDGE_T>{
    using SEARCH<VERTEX_T, EDGE_T>::ord;
    using SEARCH<VERTEX_T, EDGE_T>::graph_ptr;
    using SEARCH<VERTEX_T, EDGE_T>::cnt;
    using SEARCH<VERTEX_T, EDGE_T>::search;

    vector<vector<unsigned long>> previous_vertexes; // Двумерный массив предшественников
    vector<vector<vector<unsigned long>>> shortests; // Трехмерный массив путей

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

    [[nodiscard]] vector<unsigned long> shortest(const unsigned long from, const unsigned long to) const {
        vector<unsigned long> path;

        unsigned long cur = to;         //текущая вершина пути
        path.push_back(cur);

        while (previous_vertexes[from][cur] != cur) {   //пока существует предыдущая вершина
            cur = previous_vertexes[from][cur];        //переходим в неё
            path.push_back(cur);    //и дописываем к пути
        }

        if (previous_vertexes[from][cur] != from) {
            return vector<unsigned long>(1, -1);
        }

        reverse(path.begin(), path.end());

        return path;
    }

    void get_all_shortest_paths() {
        for (unsigned long i = 0; i < graph_ptr->get_num_of_vertex(); ++i) {
            for (unsigned long j = 0; j < graph_ptr->get_num_of_vertex(); ++j) {
                previous_vertexes[i][j] = j;
            }
        }

        // Получение предшественников
        for (vertex_iterator<VERTEX_T> iter = graph_ptr->vertex_begin(); iter != graph_ptr->vertex_end(); ++iter) {
            ord = vector<unsigned long>(graph_ptr->get_num_of_vertex(), -1);
            //cnt = 0;

            search(*iter);
        }

        for (unsigned long start_vertex = 0; start_vertex < shortests.size(); ++start_vertex) {
            for (unsigned long finish_vertex = 0; finish_vertex < shortests.size(); ++finish_vertex) {
                if (vector<unsigned long> path = shortest(start_vertex, finish_vertex); path[0] != -1) {
                    shortests[start_vertex].push_back(path);
                }
            }
        }
    }

    void reinizilize() {
        previous_vertexes =
                vector<vector<unsigned long>>
                    (graph_ptr->get_num_of_vertex(), vector<unsigned long>(graph_ptr->get_num_of_vertex()));
        shortests = vector<vector<vector<unsigned long>>>(graph_ptr->get_num_of_vertex());
    }
public:
    explicit PFS(graph<VERTEX_T, EDGE_T> *graph) :
            SEARCH<VERTEX_T, EDGE_T>(graph){
        if (!graph) {
            throw runtime_error("Uninitialized graph_ptr!");
        }

        if (graph->get_type() == NON_DIRECTED) {
            throw runtime_error("Yor are using non directed graph!");
        }

        reinizilize();

        get_all_shortest_paths();
    }

    PFS(const PFS<VERTEX_T, EDGE_T> &old_pfs) :
            SEARCH<VERTEX_T, EDGE_T>(old_pfs.graph_ptr), previous_vertexes(old_pfs.previous_vertexes),
            shortests(old_pfs.shortests){}

    ~PFS() override = default;

    [[nodiscard]] vector<vector<vector<unsigned long>>> result() const {
        return shortests;
    }


    void print_result() {
        for (const vector<vector<unsigned long>> &start_vertex : shortests) {
            if (!start_vertex.empty()) {
                cout<<"From "<<start_vertex[0][0]<<'\n';
                for (const vector<unsigned long> &finish_vertex : start_vertex) {
                    cout<<finish_vertex.back()<<" : ";
                    for (const unsigned long &id : finish_vertex) {
                        cout<<id<<" ";
                    }
                    cout<<'\n';
                }
            }
        }
    }

    bool set_graph(graph<VERTEX_T, EDGE_T> *new_graph) {
        if (!new_graph) {
            return false;
        }

        if (new_graph->get_type() != DIRECTED) {
            return false;
        }

        if (graph_ptr != new_graph) {
            graph_ptr = new_graph;

            reinizilize();
        }

        get_all_shortest_paths();

        return true;
    }

    void restart() {
        reinizilize();

        get_all_shortest_paths();
    }
};



#endif //SHORTEST_WAY_H
