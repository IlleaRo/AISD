#ifndef M_H
#define M_H

#include <vector>

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
        for (unsigned long i = 0; i < vertex_vector.size(); ++i) {
            for (unsigned long j = 0; j < vertex_vector[i].size(); ++j) {
                if (vertex_vector[i][j] != nullptr && vertex_vector[i][j]->get_v2()->get_index() < i) {
                    delete vertex_vector[i][j];
                }
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

    bool insert_edge(unsigned long v_index_1, unsigned long v_index_2, EDGE_T *edge) override {
        if (v_index_1 >= vertex_vector.size() || v_index_2 >= vertex_vector.size()) {
            throw std::runtime_error("Vertex index out of range");
        }

        if (vertex_vector[v_index_1][v_index_2] != nullptr) {
            return false;
        }

        vertex_vector[v_index_1][v_index_2] = edge;
        vertex_vector[v_index_2][v_index_1] = edge;

        num_of_edges++;

        return true;
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

    EDGE_T *get_first_edge(unsigned long vertex_index) override {
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

    EDGE_T *get_next_edge(unsigned long vertex_index, EDGE_T *edge) override {
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

    ~M_graph_directed() {
        for (std::vector<EDGE_T *> &edge : vertex_vector) {
            for (EDGE_T *e: edge) {
                delete e;
            }
        }
        vertex_vector.clear();
    }

    bool insert_edge(unsigned long v_index_1, unsigned long v_index_2, EDGE_T *edge) override {
        if (v_index_1 >= vertex_vector.size() || v_index_2 >= vertex_vector.size()) {
            throw std::runtime_error("Vertex index out of range");
        }

        if (vertex_vector[v_index_1][v_index_2] != nullptr) {
            return false;
        }

        vertex_vector[v_index_1][v_index_2] = edge;

        num_of_edges++;

        return true;
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

#endif //M_H
