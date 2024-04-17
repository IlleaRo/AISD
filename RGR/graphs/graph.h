#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>

typedef enum {
    directed,
    non_directed
} graph_type_e;

typedef enum {
    L,
    M
} graph_form_e;

template <typename T>
class graph {
protected:
    unsigned long num_of_vertex; // Число вершин
    unsigned long num_of_edges; // Число ребер

    class edge {
        vertex v1; // Дескриптор вершины, из которой исходит ребро.
        vertex v2; // Дескриптор вершины, в которую входит ребро.

        unsigned long weight; // Вес ребра
        T data; // Данные, связанные с ребром
    };

public:
    class vertex {
    protected:
        unsigned long index; // Индекс вершины в структуре графа или -1 (скрытое поле)
    public:
        std::string name; // Имя вершины?
        T data; // Хранимые данные
    };

    // Cоздает пустой L - граф с нулевым числом вершин и ребер
    graph();

    //graph(unsigned long num_of_vertex, graph_type_e type, graph_form_e form);

    //graph(unsigned long num_of_vertex, unsigned long num_of_edges, graph_type_e type, graph_form_e form);

    // Число вершин в графе
    [[nodiscard]] unsigned long get_num_of_vertex() const;

    // Число ребер в графе
    [[nodiscard]] unsigned long get_num_of_edges() const;

    // Возвращает тип графа (ориентированный / неориентированный)
    graph_type_e get_type();

    // Добавляет вершину к графу и возвращает адрес дескриптора вновь созданной вершины
    vertex *insert_vertex();

    // Удаляет вершину из графа, заданную адресом дескриптора v,
    bool remove_vertex(vertex *);

};

#endif //GRAPH_H
