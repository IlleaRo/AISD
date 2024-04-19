//
// Created by Illea on 19.04.2024.
//

#ifndef RGR_FORMS_H
#define RGR_FORMS_H

#include <iostream>
#include <vector>

typedef enum {
    DIRECTED,
    NON_DIRECTED
} graph_type_e;

typedef enum {
    L,
    M
} graph_form_e;

template <class EDGE_T>
class form_of_graphs{
protected:
    graph_type_e type;
    graph_form_e form;

    unsigned long num_of_vertex; // Число вершин
    unsigned long num_of_edges; // Число ребер

    virtual void print_graph(std::ostream &os);

    form_of_graphs(graph_type_e type, graph_form_e form, unsigned long num_of_vertex, unsigned long num_of_edges) :
        type(type), form(form), num_of_vertex(0), num_of_edges(0) {};
public:

    // Число вершин в графе
    [[nodiscard]] unsigned long get_num_of_vertex() const {
        return num_of_vertex;
    }

    // Число ребер в графе
    [[nodiscard]] unsigned long get_num_of_edges() const {
        return num_of_edges;
    }

    [[nodiscard]] graph_type_e get_type() const {
        return type;
    }

    [[nodiscard]] graph_form_e get_form() const {
        return form;
    }

    virtual unsigned long insert_vertex();

    friend std::ostream& operator<< (std::ostream &os, form_of_graphs<EDGE_T> &plist);
};

template <class EDGE_T>
std::ostream& operator<< (std::ostream &os, form_of_graphs<EDGE_T> &graph_ptr) {
    graph_ptr.print_graph();
}

template <class EDGE_T>
class L_graph : form_of_graphs<EDGE_T> {
protected:
    class node {
        EDGE_T *edge;
        node *next;

        unsigned int v2;
    };

    std::vector<node *> vertex_vector;

    void print_graph(std::ostream &os) override {
        for (int i = 0; i < vertex_vector.size(); ++i) {
            os << i << "\t:\t";
            node *current = vertex_vector[i];
            while (current != nullptr) {
                os << current->v2 << " ";
                current = current->next;
            }
        }
    }

public:
    L_graph() : form_of_graphs<EDGE_T>(NON_DIRECTED, L, 0, 0) {};

    unsigned long insert_vertex() override {
        vertex_vector.push_back(nullptr);
        return vertex_vector.size() - 1;
    }
};

#endif //RGR_FORMS_H
