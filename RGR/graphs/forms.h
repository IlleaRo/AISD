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

    virtual EDGE_T *get_first_edge(unsigned long vertex_index) = 0;

    virtual EDGE_T *get_next_edge(unsigned long vertex_index, EDGE_T *edge) = 0;

    friend std::ostream& operator<< <>(std::ostream &os, form_of_graphs<EDGE_T> &plist);
};

template <class EDGE_T>
class L_graph_non_directed : public form_of_graphs<EDGE_T> {
protected:
    using form_of_graphs<EDGE_T>::num_of_edges;

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

    ~L_graph_non_directed() {
        for (typename std::vector<node *>::iterator it = vertex_vector.begin(); it != vertex_vector.end(); ++it) {
            node *current = *it;
            while (current != nullptr) {
                node *temp = current;
                current = current->next;
                delete temp;
            }
        }

        vertex_vector.clear();
    }

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

            num_of_edges++;

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

        num_of_edges++;

        return edge;
    }

    bool remove_vertex(unsigned long vertex_index) override {
        if (vertex_index >= vertex_vector.size()) {
            return false;
        }

        EDGE_T *to_remove_edge = nullptr;

        for (unsigned int i = 0; i < vertex_vector.size(); ++i) {
            if (i == vertex_index) {
                node *current = vertex_vector[i];
                while (current != nullptr) {
                    node *temp = current;
                    current = current->next;
                    to_remove_edge = temp->edge;
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
        delete to_remove_edge;

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
                    //num_of_edges--;
                    v1_v2_removed = true;
                    break;
                }

                node *temp = current;
                prev->next = current->next;
                delete temp;
                //num_of_edges--;
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
                    num_of_edges--;
                    return true;
                }

                node *temp = current;
                prev->next = current->next;
                delete temp;
                num_of_edges--;
                return true;
            }

            prev = current;
            current = current->next;
        }

        throw std::runtime_error("Edge not found for second vertex!");
    }

    EDGE_T *get_first_edge(unsigned long vertex_index) {
        if (vertex_index >= vertex_vector.size()) {
            throw std::runtime_error("Vertex index out of range");
        }

        return vertex_vector[vertex_index] ? vertex_vector[vertex_index]->edge : nullptr;
    }

    EDGE_T *get_next_edge(unsigned long vertex_index, EDGE_T *edge) {
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

    EDGE_T *insert_edge(unsigned long v_index_1, unsigned long v_index_2, EDGE_T *edge) override {
        node *tmp = vertex_vector[v_index_1];
        if (tmp == nullptr) {
            node *new_node = new node;
            new_node->edge = edge;
            new_node->v2 = v_index_2;
            new_node->next = nullptr;
            vertex_vector[v_index_1] = new_node;

            num_of_edges++;

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
                    num_of_edges--;
                    return true;
                }

                node *temp = current;
                prev->next = current->next;
                delete temp;
                num_of_edges--;
                return true;
            }

            prev = current;
            current = current->next;
        }

        return false;
    }
};


template <class EDGE_T>
class M_graph_non_directed : public form_of_graphs<EDGE_T> {
protected:
    using form_of_graphs<EDGE_T>::num_of_edges;
protected:
    std::vector<std::vector<EDGE_T *>> vertex_vector;

    void print_graph(std::ostream &os) override {

        os << "   ";

        for (int i = 0; i < vertex_vector.size(); ++i) {
            os << i << " ";
        }

        for (unsigned long i = 0; i < vertex_vector.size(); ++i) {
            os << '\n' << i << "  ";
            for (unsigned long j = 0; j < vertex_vector[i].size(); ++j) {
                os << (vertex_vector[i][j] ? "1" : " ") << " ";
            }
        }
    }
public:
    M_graph_non_directed() : form_of_graphs<EDGE_T>(NON_DIRECTED, M, 0) {};

    ~M_graph_non_directed() {
        for (std::vector<EDGE_T *> &edge : vertex_vector) {
            for (EDGE_T *e: edge) {
                delete e;
            }
        }
    }

    unsigned long insert_vertex() override {
        vertex_vector.push_back(std::vector<EDGE_T *>(vertex_vector.size(), nullptr));
        for (std::vector<EDGE_T *> &edge : vertex_vector) {
            edge.push_back(nullptr);
        }
        return vertex_vector.size() - 1;
    }

    EDGE_T *insert_edge(unsigned long v_index_1, unsigned long v_index_2, EDGE_T *edge) override {
        if (v_index_1 >= vertex_vector.size() || v_index_2 >= vertex_vector.size()) {
            throw std::runtime_error("Vertex index out of range");
        }

        if (vertex_vector[v_index_1][v_index_2] != nullptr) {
            return vertex_vector[v_index_1][v_index_2];
        }

        vertex_vector[v_index_1][v_index_2] = edge;
        vertex_vector[v_index_2][v_index_1] = edge;

        num_of_edges++;

        return edge;
    }

    bool remove_vertex(unsigned long vertex_index) override {
        if (vertex_index >= vertex_vector.size()) {
            return false;
        }

        std::vector<EDGE_T *> to_remove_edges = vertex_vector[vertex_index];

        // Сдвигаем ребра влево
        for (std::vector<EDGE_T *> &edges : vertex_vector) {
            if (edges == to_remove_edges) {
                continue;
            }

            for (unsigned long i = vertex_index; i < edges.size() - 1; ++i) {
                edges[i] = edges[i + 1];
            }

            edges.pop_back();
        }

        // Удаляем значения в строке
        for (EDGE_T *edge : to_remove_edges) {
            delete edge;
        }

        // Сдвигаем ребра вверх
        for (unsigned int i = vertex_index; i < vertex_vector.size() - 1; ++i) {
            vertex_vector[i] = vertex_vector[i + 1];
        }

        // Чистим последнюю строчку
        for (EDGE_T *edge : vertex_vector.back()) {
            delete edge;
        }
        vertex_vector.pop_back();

        return true;
    }

    EDGE_T *get_edge(unsigned long v1_index, unsigned long v2_index) override {
        if (v1_index >= vertex_vector.size() || v2_index >= vertex_vector.size()) {
            return nullptr;
        }

        return vertex_vector[v1_index][v2_index];
    }

    bool remove_edge(unsigned long v1_index, unsigned long v2_index) override {
        if (v1_index >= vertex_vector.size() || v2_index >= vertex_vector.size()) {
            return false;
        }

        if (vertex_vector[v1_index][v2_index] == nullptr) {
            return false;
        }

        delete vertex_vector[v1_index][v2_index];
        vertex_vector[v1_index][v2_index] = nullptr;

        // We use the same pointer for both vertices
        //delete vertex_vector[v2_index][v1_index];
        vertex_vector[v2_index][v1_index] = nullptr;

        num_of_edges--;

        return true;
    }

    EDGE_T *get_first_edge(unsigned long vertex_index) {
        if (vertex_index >= vertex_vector.size()) {
            throw std::runtime_error("Vertex index out of range");
        }

        for (unsigned long i = 0; i < vertex_vector.size(); ++i) {
            if (vertex_vector[vertex_index][i] != nullptr) {
                return vertex_vector[vertex_index][i];
            }
        }

        return nullptr;
    }

    EDGE_T *get_next_edge(unsigned long vertex_index, EDGE_T *edge) {
        if (vertex_index >= vertex_vector.size()) {
            throw std::runtime_error("Vertex index out of range");
        }

        for (unsigned long i = 0; i < vertex_vector.size(); ++i) {
            if (vertex_vector[vertex_index][i] == edge) {
                for (unsigned long j = i + 1; j < vertex_vector.size(); ++j) {
                    if (vertex_vector[vertex_index][j] != nullptr) {
                        return vertex_vector[vertex_index][j];
                    }
                }
                return nullptr;
            }
        }

        return nullptr;
    }
};

template <class EDGE_T>
class M_graph_directed : public M_graph_non_directed<EDGE_T> {
    using M_graph_non_directed<EDGE_T>::vertex_vector;
    using form_of_graphs<EDGE_T>::num_of_edges;
    using form_of_graphs<EDGE_T>::type;
public:
    M_graph_directed() : M_graph_non_directed<EDGE_T>() {
        type = DIRECTED;
    }

    EDGE_T *insert_edge(unsigned long v_index_1, unsigned long v_index_2, EDGE_T *edge) override {
        if (v_index_1 >= vertex_vector.size() || v_index_2 >= vertex_vector.size()) {
            throw std::runtime_error("Vertex index out of range");
        }

        if (vertex_vector[v_index_1][v_index_2] != nullptr) {
            return vertex_vector[v_index_1][v_index_2];
        }

        vertex_vector[v_index_1][v_index_2] = edge;

        num_of_edges++;

        return edge;
    }

    bool remove_edge(unsigned long v1_index, unsigned long v2_index) override {
        if (v1_index >= vertex_vector.size() || v2_index >= vertex_vector.size()) {
            return false;
        }

        if (vertex_vector[v1_index][v2_index] == nullptr) {
            return false;
        }

        delete vertex_vector[v1_index][v2_index];
        vertex_vector[v1_index][v2_index] = nullptr;

        num_of_edges--;

        return true;
    }
};

#endif //RGR_FORMS_H
