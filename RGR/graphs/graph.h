#ifndef RGR_GRAPH_H
#define RGR_GRAPH_H

#include "vertex.h"
#include "edge.h"
#include "forms.h"
#include "iterators.h"

#include <ostream>
#include <vector>
#include <random>

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
    std::vector<VERTEX_T *> vertexes;

    friend class edge_iterator_for_v<VERTEX_T, EDGE_T>;
    friend class edge_iterator<VERTEX_T, EDGE_T>;

    EDGE_T *get_first_edge(VERTEX_T *vertex) {
        return form->get_first_edge(vertex->get_index());
    }

    EDGE_T *get_next_edge(VERTEX_T *vertex, EDGE_T *cur_edge) {
        return form->get_next_edge(vertex->get_index(), cur_edge);
    }

public:
    // Создает пустой L - граф с нулевым числом вершин и ребер
    graph() {
        form = new L_graph_non_directed<EDGE_T>;
    };

    graph(unsigned long num_of_vertex, graph_type_e type, graph_form_e form) {
        if (form == L) {
            if (type == DIRECTED) {
                this->form = new L_graph_directed<EDGE_T>;
            } else {
                this->form = new L_graph_non_directed<EDGE_T>;
            }
        } else {
            if (type == DIRECTED) {
                this->form = new M_graph_directed<EDGE_T>;
            } else {
                this->form = new M_graph_non_directed<EDGE_T>;
            }
        }

        for (int i = 0; i < num_of_vertex; ++i) {
            insert_vertex();
        }
    }

    graph(unsigned long num_of_vertex, unsigned long num_of_edges, graph_type_e type, graph_form_e form) {
        if (form == L) {
            if (type == DIRECTED) {
                this->form = new L_graph_directed<EDGE_T>;
            } else {
                this->form = new L_graph_non_directed<EDGE_T>;
            }
        } else {
            if (type == DIRECTED) {
                this->form = new M_graph_directed<EDGE_T>;
            } else {
                this->form = new M_graph_non_directed<EDGE_T>;
            }
        }

        for (int i = 0; i < num_of_vertex; ++i) {
            insert_vertex();
        }

        if (type == DIRECTED) {
            if (num_of_edges > num_of_vertex * (num_of_vertex - 1)) {
                num_of_edges = num_of_vertex * (num_of_vertex - 1);
            }
        } else {
            if (num_of_edges > num_of_vertex * (num_of_vertex - 1) / 2) {
                num_of_edges = num_of_vertex * (num_of_vertex - 1) / 2;
            }
        }

        // Seed with a real random value, if available
        std::random_device r;

        std::default_random_engine e(r());
        std::uniform_int_distribution<int> uniform_dist(0, (int)num_of_vertex - 1); // Равномерное распределение

        unsigned long i = 0;

        while (i < num_of_edges) {
            unsigned long v1 = uniform_dist(e);
            unsigned long v2 = uniform_dist(e);

            if (v1 == v2) {
                continue;
            }

            if (get_edge(vertexes[v1], vertexes[v2]) == nullptr) {
                insert_edge(vertexes[v1], vertexes[v2]);

                if (type == NON_DIRECTED) {
                    i+=2;
                } else {
                    ++i;
                }
            }
        }
    }

    ~graph() {

        delete form;

        for (VERTEX_T *vertex : vertexes) {
            delete vertex;
        }

        vertexes.clear();
    }

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
        vertexes.push_back(vertex);

        return vertex;
    }

    // Добавляет вершину c именем name к графу и возвращает адрес дескриптора вновь созданной вершины
    VERTEX_T *insert_vertex(std::string name) {
        VERTEX_T *vertex = insert_vertex();
        vertex->set_name(name);
        return vertex;
    }

    // Добавляет ребро между вершинами графа, заданными адресами дескрипторов v1 и v2 и возвращает
    // адрес дескриптора вновь созданного ребра (или уже существующего).
    EDGE_T *insert_edge(VERTEX_T *v1, VERTEX_T *v2) {
        if (v1 == nullptr || v2 == nullptr) {
            return nullptr;
        }

        EDGE_T *edge = new EDGE_T(v1, v2);

        EDGE_T *inserted_edge = form->insert_edge(v1->get_index(), v2->get_index(), edge);

        if (edge != inserted_edge) {
            delete edge;
        }

        return inserted_edge;
    }

    // Добавляет ребро между вершинами графа, заданными адресами
    // дескрипторов v1 и v2, с весом w и возвращает адрес дескриптора вновь созданного ребра (или уже существующего).
    EDGE_T *insert_edge(VERTEX_T *v1, VERTEX_T *v2, double weight) {
        if (v1 == nullptr || v2 == nullptr) {
            return nullptr;
        }

        EDGE_T *edge = new EDGE_T(v1, v2, weight);

        form->insert_edge(v1->get_index(), v2->get_index(), edge);

        return edge;
    }

    EDGE_T *get_edge(VERTEX_T *v1, VERTEX_T *v2) {
        if (v1 == nullptr || v2 == nullptr) {
            return nullptr;
        }

        return form->get_edge(v1->get_index(), v2->get_index());
    }

    VERTEX_T *get_vertex(size_t idx) {
        if (idx > this->vertexes.size()) {
            return nullptr;
        }

        return this->vertexes[idx];
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

        unsigned long index = vertex_ptr->get_index();

        bool is_removed;

        if ((is_removed = form->remove_vertex(index))) {
            vertexes.erase(vertexes.begin() + index);
            delete vertex_ptr;
        }

        if (is_removed) {
            for (unsigned long i = index; i < vertexes.size(); ++i) {
                vertexes[i]->set_index(i);
            }
        }

        return is_removed;
    }

    vertex_iterator<VERTEX_T> vertex_begin() {
        return vertex_iterator<VERTEX_T>(vertexes.begin());
    }

    vertex_iterator<VERTEX_T> vertex_end() {
        return vertex_iterator<VERTEX_T>(vertexes.end());
    }

    edge_iterator_for_v<VERTEX_T, EDGE_T> edge_v_begin(VERTEX_T *vertex) {
        edge_iterator_for_v<VERTEX_T, EDGE_T> iter(this, vertex);
        iter.set_cur_edge(get_first_edge(vertex));
        return iter;
    }

    edge_iterator_for_v<VERTEX_T, EDGE_T> edge_v_end(VERTEX_T *vertex) {
        edge_iterator_for_v<VERTEX_T, EDGE_T> iter(this, vertex);
        iter.set_cur_edge(nullptr);

        return iter;
    }

    edge_iterator<VERTEX_T, EDGE_T> edge_begin() {
        edge_iterator<VERTEX_T, EDGE_T> iter(this);

        EDGE_T *tmp;

        for (VERTEX_T *vertex : vertexes) {
            if ((tmp = get_first_edge(vertex)) != nullptr) {
                if (get_type() == NON_DIRECTED) {
                    do {
                        if (vertex == tmp->get_v2()) {
                            continue;
                        }

                        break;
                    } while ((tmp = get_next_edge(vertex, tmp)));

                    if (tmp == nullptr) {
                        continue;
                    }
                }

                iter.set_cur_vertex(vertex);
                iter.set_cur_edge(tmp);

                return iter;
            }
        }

        iter = edge_end();
        return iter;
    }

    edge_iterator<VERTEX_T, EDGE_T> edge_end() {
        edge_iterator<VERTEX_T, EDGE_T> iter(this);
        iter.set_cur_edge(nullptr);
        iter.set_cur_vertex(*vertexes.rbegin());

        return iter;
    }

    [[nodiscard]] float get_koeff() const {
        if (get_type() == DIRECTED) {
            return (float) get_num_of_edges() / (get_num_of_vertex() * (get_num_of_vertex() - 1));
        } else {
            return (float) get_num_of_edges() / (get_num_of_vertex() * (get_num_of_vertex() - 1) / 2);
        }
    }

    void to_list_graph() {
        if (get_form() == L) {
            return;
        }

        form_of_graphs<EDGE_T> *new_form;

        if (get_type() == DIRECTED) {
            new_form = new L_graph_directed<EDGE_T>;
        } else {
            new_form = new L_graph_non_directed<EDGE_T>;
        }

        for (VERTEX_T *vertex : vertexes) {
            new_form->insert_vertex();
        }

        edge_iterator<VERTEX_T, EDGE_T> iter(this);

        for (iter = edge_begin(); iter != edge_end(); ++iter) {
            new_form->insert_edge((*iter)->get_v1()->get_index(),
                                  (*iter)->get_v2()->get_index(), new EDGE_T(**iter));
        }

        delete form;
        form = new_form;
    }

    void to_matrix_graph() {
        if (get_form() == M) {
            return;
        }

        form_of_graphs<EDGE_T> *new_form;

        if (get_type() == DIRECTED) {
            new_form = new M_graph_directed<EDGE_T>;
        } else {
            new_form = new M_graph_non_directed<EDGE_T>;
        }

        for (VERTEX_T *vertex : vertexes) {
            new_form->insert_vertex();
        }

        edge_iterator<VERTEX_T, EDGE_T> iter(this);

        for (iter = edge_begin(); iter != edge_end(); ++iter) {
            new_form->insert_edge((*iter)->get_v1()->get_index(),
                                  (*iter)->get_v2()->get_index(), new EDGE_T(**iter));
        }

        delete form;
        form = new_form;
    }

    friend std::ostream& operator<< <>(std::ostream &os, graph<VERTEX_T, EDGE_T> &graph_ptr);
};

#endif //RGR_GRAPH_H

