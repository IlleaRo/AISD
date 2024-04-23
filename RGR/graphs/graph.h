#ifndef RGR_GRAPH_H
#define RGR_GRAPH_H

#include "vertex.h"
#include "edge.h"
#include "forms.h"

#include <ostream>
#include <vector>

template <class VERTEX_T, class EDGE_T>
class graph;

template <class VERTEX_T, class EDGE_T>
std::ostream& operator<< (std::ostream &os, graph<VERTEX_T, EDGE_T> &graph_ptr) {
    os<<*graph_ptr.form;
    return os;
}

template <class VERTEX_T, class EDGE_T>
class graph {
protected:
    form_of_graphs <EDGE_T> *form;
    std::vector<VERTEX_T> vertexes;
public:
    // Создает пустой L - граф с нулевым числом вершин и ребер
    graph() {
        form = new L_graph<EDGE_T>;
    };

    //graph(unsigned long num_of_vertex, graph_type_e type, graph_form_e form);

    //graph(unsigned long num_of_vertex, unsigned long num_of_edges, graph_type_e type, graph_form_e form);

    // Возвращает тип графа (ориентированный / неориентированный)
    graph_type_e get_type() {
        return form->get_type();
    }

    // Возвращает форму представления графа (L - матрица смежности / M - матрица инцидентности)
    graph_form_e get_form() {
        return form->get_form();
    }

    // Возвращает число вершин в графе
    unsigned long get_num_of_vertex() {
        return vertexes.size();
    }

    // Возвращает число ребер в графе
    unsigned long get_num_of_edges() {
        return form->get_num_of_edges();
    }

    // Добавляет вершину к графу и возвращает адрес дескриптора вновь созданной вершины
    VERTEX_T *insert_vertex() {
        unsigned long index;
        if ((index = form->insert_vertex())== -1) {
            return nullptr;
        }

        VERTEX_T *vertex = new VERTEX_T(index);
        vertexes.push_back(*vertex);

        return vertex;
    }

    // Добавляет вершину c именем name к графу и возвращает адрес дескриптора вновь созданной вершины
    VERTEX_T *insert_vertex(std::string name) {
        VERTEX_T *vertex = insert_vertex();
        vertex->set_name(name);
        return vertex;
    }

    //fixme: что делать, если ребро уже существует?
    // Добавляет ребро между вершинами графа, заданными адресами дескрипторов v1 и v2 и возвращает
    // адрес дескриптора вновь созданного ребра.
    EDGE_T *insert_edge(VERTEX_T *v1, VERTEX_T *v2) {
        if (v1 == nullptr || v2 == nullptr) {
            return nullptr;
        }

        EDGE_T *edge = new EDGE_T(v1, v2);

        form->insert_edge(v1->get_index(), v2->get_index(), edge);

        return edge;
    }

    //fixme: что делать, если ребро уже существует?
    // Добавляет ребро между вершинами графа, заданными адресами
    // дескрипторов v1 и v2, с весом w и возвращает адрес дескриптора вновь созданного ребра.
    EDGE_T *insert_edge(VERTEX_T *v1, VERTEX_T *v2, double weight) {
        if (v1 == nullptr || v2 == nullptr) {
            return nullptr;
        }

        EDGE_T *edge = new EDGE_T(v1, v2, weight);
        edge->v1 = v1;
        edge->v2 = v2;

        form->insert_edge(v1->get_index(), v2->get_index(), edge);

        return edge;
    }

    EDGE_T *get_edge(VERTEX_T *v1, VERTEX_T *v2) {
        if (v1 == nullptr || v2 == nullptr) {
            return nullptr;
        }

        return form->get_edge(v1->get_index(), v2->get_index());
    }

    // Удаляет ребро, соединяющее вершины, заданные адресами дескрипторов v1 и v2
    bool remove_edge(VERTEX_T *v1, VERTEX_T *v2) {
        if (v1 == nullptr || v2 == nullptr) {
            return false;
        }

        return form->remove_edge(v1->get_index(), v2->get_index());
    }


    // Удаляет вершину из графа, заданную адресом дескриптора
    bool remove_vertex(VERTEX_T *vertex_ptr) {
        if (vertex_ptr == nullptr) {
            return false;
        }

        if (form->remove_vertex(vertex_ptr->get_index())) {
            delete vertex_ptr;
            return true;
        }

        return false;
    }

    friend std::ostream& operator<< <>(std::ostream &os, graph<VERTEX_T, EDGE_T> &graph_ptr);
};

#endif //RGR_GRAPH_H

