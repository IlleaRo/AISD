#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>

enum graph_types {
    oriented,
    non_oriented
} typedef graph_type_e;

enum graph_forms {
    L,
    M
} typedef graph_form_e;

template <typename T>
class graph {
protected:
    unsigned long num_of_vertex; // Число вершин
    unsigned long num_of_edges; // Число ребер

    class vertex {
    protected:
        unsigned long index; // Индекс вершины в структуре графа или -1 (скрытое поле)
    public:
        std::string name; // Имя вершины?
        T data; // Хранимые данные
    };
public:

    // Cоздает пустой L - граф с нулевым числом вершин и ребер
    graph();

    //graph(unsigned long num_of_vertex, graph_type_e type, graph_form_e form);

    //graph(unsigned long num_of_vertex, unsigned long num_of_edges, graph_type_e type, graph_form_e form);

    // Число вершин в графе
    [[nodiscard]] unsigned long get_num_of_vertex() const;

    // Число ребер в графе
    [[nodiscard]] unsigned long get_num_of_edges() const;


};

#endif //GRAPH_H
