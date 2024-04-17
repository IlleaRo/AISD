#ifndef RGR_GRAPH_H
#define RGR_GRAPH_H

#include <iostream>

#include "vertex.h"
#include "edge.h"

typedef enum {
    directed,
    non_directed
} graph_type_e;

typedef enum {
    L,
    M
} graph_form_e;

template <class V_NAME_T, class V_DATA_T, class E_WEIGHT_T, class E_DATA_T>
class graph {
protected:
    unsigned long num_of_vertex; // Число вершин
    unsigned long num_of_edges; // Число ребер

public:
    // Cоздает пустой L - граф с нулевым числом вершин и ребер
    graph();

    graph(unsigned long num_of_vertex, graph_type_e type, graph_form_e form);

    graph(unsigned long num_of_vertex, unsigned long num_of_edges, graph_type_e type, graph_form_e form);

    // Число вершин в графе
    [[nodiscard]] unsigned long get_num_of_vertex() const;

    // Число ребер в графе
    [[nodiscard]] unsigned long get_num_of_edges() const;

    // Возвращает тип графа (ориентированный / неориентированный)
    graph_type_e get_type();

    // Добавляет вершину к графу и возвращает адрес дескриптора вновь созданной вершины
    vertex<V_NAME_T, V_DATA_T> *insert_vertex();

    // Удаляет вершину из графа, заданную адресом дескриптора,
    bool remove_vertex(vertex<V_NAME_T, V_DATA_T> * vertex_ptr);

};

#endif //RGR_GRAPH_H
