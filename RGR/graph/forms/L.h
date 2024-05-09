#ifndef L_H
#define L_H

#include <vector>

#include "common.h"

template <class EDGE_T>
class L_graph_non_directed : public form_of_graphs<EDGE_T> {
protected:
    using form_of_graphs<EDGE_T>::num_of_edges;

    class node {
    public:
        EDGE_T *edge;
        unsigned long v2;
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

    ~L_graph_non_directed() {
        for (int i = 0; i < vertex_vector.size(); ++i) {
            node *current = vertex_vector[i];
            while (current != nullptr) {
                node *temp = current;
                current = current->next;

                if (temp->v2 < i) { // Очищаем память каждого ребра только единожды
                    delete temp->edge;
                }
                delete temp;
            }
        }

        vertex_vector.clear();
    }

    unsigned long insert_vertex() override {
        vertex_vector.push_back(nullptr);
        return vertex_vector.size() - 1;
    }

    bool insert_edge(unsigned long v_index_1, unsigned long v_index_2, EDGE_T *edge) override {
        if (v_index_1 >= vertex_vector.size() || v_index_2 >= vertex_vector.size()) {
            throw std::runtime_error("Vertex index out of range");
        }

        node *tmp = vertex_vector[v_index_1];

        while (tmp) {
            if (tmp->v2 == v_index_2) {
                return false;
            }
            tmp = tmp->next;
        }

        node *new_node = new node;
        new_node->edge = edge;
        new_node->v2 = v_index_2;
        new_node->next = vertex_vector[v_index_1];
        vertex_vector[v_index_1] = new_node;

        new_node = new node;
        new_node->edge = edge;
        new_node->v2 = v_index_1;
        new_node->next = vertex_vector[v_index_2];
        vertex_vector[v_index_2] = new_node;

        num_of_edges++;

        return true;
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
                    delete temp; // Удаляем ребро один раз (при втором проходе по графу)
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
                            if (form_of_graphs<EDGE_T>::type == DIRECTED) {
                                delete current->edge;
                                num_of_edges--;
                            }
                            delete current;
                            current = vertex_vector[i];
                            continue;
                        }

                        node *temp = current;
                        prev->next = current->next;
                        current = current->next;

                        delete temp->edge;
                        num_of_edges--;

                        delete temp;
                        continue;
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

                    delete current; // We will delete the edge at the node of the second vertex

                    v1_v2_removed = true;
                    break;
                }

                node *temp = current;
                prev->next = current->next;

                delete temp; // We will delete the edge at the node of the second vertex

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

                    delete current->edge; // We use same pointer for both vertices
                    delete current;

                    num_of_edges--;
                    return true;
                }

                node *temp = current;
                prev->next = current->next;

                delete temp->edge; // We use same pointer for both vertices
                delete temp;

                num_of_edges--;
                return true;
            }

            prev = current;
            current = current->next;
        }

        throw std::runtime_error("Edge not found for second vertex!");
    }

    EDGE_T *get_first_edge(unsigned long vertex_index) override {
        if (vertex_index >= vertex_vector.size()) {
            throw std::runtime_error("Vertex index out of range");
        }

        return vertex_vector[vertex_index] ? vertex_vector[vertex_index]->edge : nullptr;
    }

    EDGE_T *get_next_edge(unsigned long vertex_index, EDGE_T *edge) override {
        if (vertex_index >= vertex_vector.size()) {
            throw std::runtime_error("Vertex index out of range");
        }

        node *current = vertex_vector[vertex_index];
        while (current != nullptr) {
            if (current->edge == edge) {
                return current->next ? current->next->edge : nullptr;
            }
            current = current->next;
        }

        return nullptr;
    }
};

template <class EDGE_T>
class L_graph_directed : public L_graph_non_directed<EDGE_T> {
    using typename L_graph_non_directed<EDGE_T>::node;
    using L_graph_non_directed<EDGE_T>::vertex_vector;
    using form_of_graphs<EDGE_T>::type;
    using form_of_graphs<EDGE_T>::num_of_edges;

public:
    L_graph_directed() : L_graph_non_directed<EDGE_T>() {
        type = DIRECTED;
    }

    ~L_graph_directed() { // Деструктор неориентированного графа не удаляет петли
        for (typename std::vector<node *>::iterator it = vertex_vector.begin(); it != vertex_vector.end(); ++it) {
            node *current = *it;
            while (current != nullptr) {
                node *temp = current;
                current = current->next;
                delete temp->edge;
                delete temp;
            }
        }

        vertex_vector.clear();
    }

    bool insert_edge(unsigned long v_index_1, unsigned long v_index_2, EDGE_T *edge) override {
        node *tmp = vertex_vector[v_index_1];
        if (tmp == nullptr) {
            node *new_node = new node;
            new_node->edge = edge;
            new_node->v2 = v_index_2;
            new_node->next = nullptr;
            vertex_vector[v_index_1] = new_node;

            num_of_edges++;

            return true;
        }

        while (tmp->next) {
            if (tmp->v2 == v_index_2) {
                return false;
            }
            tmp = tmp->next;
        }

        node *new_node = new node;
        new_node->edge = edge;
        new_node->v2 = v_index_2;
        new_node->next = nullptr;
        tmp->next = new_node;

        num_of_edges++;

        return true;
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

                    delete current->edge;
                    delete current;

                    num_of_edges--;
                    return true;
                }

                node *temp = current;
                prev->next = current->next;

                delete current->edge;
                delete temp;

                num_of_edges--;
                return true;
            }

            prev = current;
            current = current->next;
        }

        return false;
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
                            delete current->edge;
                            num_of_edges--;

                            delete current;
                            current = vertex_vector[i];
                            continue;
                        }

                        node *temp = current;
                        prev->next = current->next;
                        current = current->next;

                        delete temp->edge;
                        num_of_edges--;

                        delete temp;
                        continue;
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
};

#endif //L_H
