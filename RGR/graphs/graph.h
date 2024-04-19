#ifndef RGR_GRAPH_H
#define RGR_GRAPH_H

#include "vertex.h"
#include "edge.h"
#include "forms.h"

#include <iostream>
#include <vector>

template <class VERTEX_T, class EDGE_T>
class graph {
protected:
    form_of_graphs <EDGE_T> form;
    std::vector<VERTEX_T> vertexes;
public:
    // Создает пустой L - граф с нулевым числом вершин и ребер
    graph() {
        L_graph<EDGE_T> graph;
        form = graph;
    }

    //graph(unsigned long num_of_vertex, graph_type_e type, graph_form_e form);

    //graph(unsigned long num_of_vertex, unsigned long num_of_edges, graph_type_e type, graph_form_e form);

    // Возвращает тип графа (ориентированный / неориентированный)
    graph_type_e get_type() {
        form.get_type();
    }

    // Возвращает форму представления графа (L - матрица смежности / M - матрица инцидентности)
    graph_form_e get_form() {
        form.get_form();
    }

    // Возвращает число вершин в графе
    unsigned long get_num_of_vertex() {
        return vertexes.size();
    }

    // Возвращает число ребер в графе
    unsigned long get_num_of_edges() {
        return form.get_num_of_edges();
    }

    // Добавляет вершину к графу и возвращает адрес дескриптора вновь созданной вершины
    VERTEX_T *insert_vertex() {
        unsigned long index;
        if ((index = form->insert_vertex())== -1) {
            return nullptr;
        }

        VERTEX_T *vertex = new VERTEX_T;
        vertex->index = index;
        vertexes.push_back(*vertex);

        return vertex;
    }

    // Удаляет вершину из графа, заданную адресом дескриптора,
    //bool remove_vertex(vertex<V_NAME_T, V_DATA_T> * vertex_ptr);


    friend std::ostream& operator<<(std::ostream &os, graph<VERTEX_T, EDGE_T> &graph_ptr);
};

template <class VERTEX_T, class EDGE_T>
std::ostream& operator<< (std::ostream &os, graph<VERTEX_T, EDGE_T> &graph_ptr) {
    os<<graph_ptr.form;
    return os;
}

#endif //RGR_GRAPH_H

