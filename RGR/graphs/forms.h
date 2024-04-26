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
class form_of_graphs;

template <class EDGE_T>
std::ostream& operator<< (std::ostream &os, form_of_graphs<EDGE_T> &plist) {
    plist.print_graph(os);
    return os;
}

template <class EDGE_T>
class form_of_graphs{
protected:
    graph_type_e type;
    graph_form_e form;

    unsigned long num_of_edges; // Число ребер

    virtual void print_graph(std::ostream &os) = 0;

    form_of_graphs(graph_type_e type, graph_form_e form, unsigned long num_of_edges) :
        type(type), form(form), num_of_edges(num_of_edges) {};
public:
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

    virtual EDGE_T *get_edge(unsigned long v1_index, unsigned long v2_index) = 0;

    virtual bool remove_edge(unsigned long v1_index, unsigned long v2_index) = 0;

    virtual unsigned long insert_vertex() = 0;

    virtual bool remove_vertex(unsigned long vertex_index) = 0;

    virtual EDGE_T *insert_edge(unsigned long v_index_1, unsigned long v_index_2, EDGE_T *edge) = 0;

    friend std::ostream& operator<< <>(std::ostream &os, form_of_graphs<EDGE_T> &plist);
};

template <class EDGE_T>
class L_graph_non_directed : public form_of_graphs<EDGE_T> {
protected:
    class node {
    public:
        EDGE_T *edge;
        unsigned int v2;
        node *next;
    };

    std::vector<node *> vertex_vector;

    void print_graph(std::ostream &os) override {
        for (int i = 0; i < vertex_vector.size(); ++i) {
            os << i << " : ";
            node *current = vertex_vector[i];
            while (current != nullptr) {
                os << current->v2 << " ";
                current = current->next;
            }
            os << std::endl;
        }
    }

public:
    L_graph_non_directed() : form_of_graphs<EDGE_T>(NON_DIRECTED, L, 0) {};

    unsigned long insert_vertex() override {
        vertex_vector.push_back(nullptr);
        return vertex_vector.size() - 1;
    }

    EDGE_T *insert_edge(unsigned long v_index_1, unsigned long v_index_2, EDGE_T *edge) override {
        if (v_index_1 >= vertex_vector.size() || v_index_2 >= vertex_vector.size()) {
            throw std::runtime_error("Vertex index out of range");
        }

        node *tmp = vertex_vector[v_index_1];
        if (tmp == nullptr) {
            node *new_node = new node;
            new_node->edge = edge;
            new_node->v2 = v_index_2;
            new_node->next = nullptr;
            vertex_vector[v_index_1] = new_node;

            new_node = new node;
            new_node->edge = edge;
            new_node->v2 = v_index_1;
            new_node->next = nullptr;
            vertex_vector[v_index_2] = new_node;

            form_of_graphs<EDGE_T>::num_of_edges++;

            return edge;
        }

        while (tmp->next) {
            if (tmp->v2 == v_index_2) {
                return tmp->edge;
            }
            tmp = tmp->next;
        }

        node *new_node = new node;
        new_node->edge = edge;
        new_node->v2 = v_index_2;
        new_node->next = nullptr;

        tmp->next = new_node;

        new_node = new node;
        new_node->edge = edge;
        new_node->v2 = v_index_1;
        new_node->next = vertex_vector[v_index_2];
        vertex_vector[v_index_2] = new_node;

        form_of_graphs<EDGE_T>::num_of_edges++;

        return edge;
    }

    bool remove_vertex(unsigned long vertex_index) override {
        if (vertex_index >= vertex_vector.size()) {
            return false;
        }

        for (unsigned int i = 0; i < vertex_vector.size(); ++i) {
            if (i == vertex_index) {
                node *current = vertex_vector[i];
                while (current != nullptr) {
                    node *temp = current;
                    current = current->next;
                    delete temp;
                }
                continue;
            }

            if (vertex_vector[i] != nullptr) {

                node *current = vertex_vector[i];
                node *prev = nullptr;

                while (current != nullptr) {
                    if (current->v2 == vertex_index) {
                        if (current == vertex_vector[i]) {
                            vertex_vector[i] = current->next;
                            delete current;
                            current = vertex_vector[i];
                            continue;
                        }

                        node *temp = current;
                        prev->next = current->next;
                        delete temp;
                    } else if (current->v2 > vertex_index) {
                        current->v2--;
                    }

                    prev = current;
                    current = current->next;
                }
            }
        }

        vertex_vector.erase(vertex_vector.begin() + vertex_index);

        return true;
    }

    //TODO: перепиши меня под использование итератора
    EDGE_T *get_edge(unsigned long v1_index, unsigned long v2_index) override {
        if (v1_index >= vertex_vector.size() || v2_index >= vertex_vector.size()) {
            return nullptr;
        }

        node *current = vertex_vector[v1_index];
        while (current != nullptr) {
            if (current->v2 == v2_index) {
                return current->edge;
            }
            current = current->next;
        }

        return nullptr;
    }

    bool remove_edge(unsigned long v1_index, unsigned long v2_index) override {
        if (v1_index >= vertex_vector.size() || v2_index >= vertex_vector.size()) {
            return false;
        }

        node *current = vertex_vector[v1_index];
        node *prev = nullptr;
        bool v1_v2_removed = false;

        while (current != nullptr) {
            if (current->v2 == v2_index) {
                if (current == vertex_vector[v1_index]) {
                    vertex_vector[v1_index] = current->next;
                    delete current;
                    //form_of_graphs<EDGE_T>::num_of_edges--;
                    v1_v2_removed = true;
                    break;
                }

                node *temp = current;
                prev->next = current->next;
                delete temp;
                //form_of_graphs<EDGE_T>::num_of_edges--;
                v1_v2_removed = true;
                break;
            }

            prev = current;
            current = current->next;
        }

        if (!v1_v2_removed) {
            return false;
        }

        current = vertex_vector[v2_index];
        prev = nullptr;

        while (current != nullptr) {
            if (current->v2 == v1_index) {
                if (current == vertex_vector[v2_index]) {
                    vertex_vector[v2_index] = current->next;
                    delete current;
                    form_of_graphs<EDGE_T>::num_of_edges--;
                    return true;
                }

                node *temp = current;
                prev->next = current->next;
                delete temp;
                form_of_graphs<EDGE_T>::num_of_edges--;
                return true;
            }

            prev = current;
            current = current->next;
        }

        throw std::runtime_error("Edge not found for second vertex!");
    }
};

template <class EDGE_T>
class L_graph_directed : public L_graph_non_directed<EDGE_T> {
    using typename L_graph_non_directed<EDGE_T>::node;
    using L_graph_non_directed<EDGE_T>::vertex_vector;

public:
    L_graph_directed() : L_graph_non_directed<EDGE_T>() {
        form_of_graphs<EDGE_T>::type = DIRECTED;
    }

    EDGE_T *insert_edge(unsigned long v_index_1, unsigned long v_index_2, EDGE_T *edge) override {
        node *tmp = vertex_vector[v_index_1];
        if (tmp == nullptr) {
            node *new_node = new node;
            new_node->edge = edge;
            new_node->v2 = v_index_2;
            new_node->next = nullptr;
            vertex_vector[v_index_1] = new_node;

            form_of_graphs<EDGE_T>::num_of_edges++;

            return edge;
        }

        while (tmp->next) {
            if (tmp->v2 == v_index_2) {
                return tmp->edge;
            }
            tmp = tmp->next;
        }

        node *new_node = new node;
        new_node->edge = edge;
        new_node->v2 = v_index_2;
        new_node->next = nullptr;
        tmp->next = new_node;

        return edge;
    }

    bool remove_edge(unsigned long v1_index, unsigned long v2_index) override {
        if (v1_index >= vertex_vector.size() || v2_index >= vertex_vector.size()) {
            return false;
        }

        node *current = vertex_vector[v1_index];
        node *prev = nullptr;

        while (current != nullptr) {
            if (current->v2 == v2_index) {
                if (current == vertex_vector[v1_index]) {
                    vertex_vector[v1_index] = current->next;
                    delete current;
                    form_of_graphs<EDGE_T>::num_of_edges--;
                    return true;
                }

                node *temp = current;
                prev->next = current->next;
                delete temp;
                form_of_graphs<EDGE_T>::num_of_edges--;
                return true;
            }

            prev = current;
            current = current->next;
        }

        return false;
    }
};

#endif //RGR_FORMS_H
