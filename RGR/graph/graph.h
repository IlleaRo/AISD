#ifndef GRAPH_H
#define GRAPH_H

#include "forms/forms.h"
#include "iterators/iterators.h"
#include "parts/edge.h"
#include "parts/vertex.h"

#include <vector>
#include <random>

template <class VERTEX_T, class EDGE_T>
class graph;

template <class VERTEX_T, class EDGE_T>
std::ostream& operator<< (std::ostream &os, graph<VERTEX_T, EDGE_T> &graph_ptr) {
    os<<*graph_ptr.curForm;
    return os;
}

template <class VERTEX_T, class EDGE_T>
class graph {
protected:
    form <EDGE_T> *curForm;
    std::vector<VERTEX_T *> vertices;

    friend class vertexEdgeIter<VERTEX_T, EDGE_T>;
    friend class edgeIterator<VERTEX_T, EDGE_T>;

    EDGE_T *firstEdge(VERTEX_T *vertex) {
        return curForm->firstEdge(vertex->getIndex());
    }

    EDGE_T *nextEdge(VERTEX_T *vertex, EDGE_T *cur_edge) {
        return curForm->nextEdge(vertex->getIndex(), cur_edge);
    }

public:
    graph() {
        curForm = new nonDirectedL<EDGE_T>;
    };

    graph(unsigned long num_of_vertex, graphTypeE type, graphFormE form) {
        if (form == L) {
            if (type == DIRECTED) {
                this->curForm = new directedL<EDGE_T>;
            } else {
                this->curForm = new nonDirectedL<EDGE_T>;
            }
        } else {
            if (type == DIRECTED) {
                this->curForm = new directedM<EDGE_T>;
            } else {
                this->curForm = new nonDirectedM<EDGE_T>;
            }
        }

        for (int i = 0; i < num_of_vertex; ++i) {
            pushVertex();
        }
    }

    graph(graph<VERTEX_T, EDGE_T> &old_graph) {
        if (old_graph.get_form() == L) {
            if (old_graph.getType() == DIRECTED) {
                this->curForm = new directedL<EDGE_T>;
            } else {
                this->curForm = new nonDirectedL<EDGE_T>;
            }
        } else {
            if (old_graph.getType() == DIRECTED) {
                this->curForm = new directedM<EDGE_T>;
            } else {
                this->curForm = new nonDirectedM<EDGE_T>;
            }
        }


        for (VERTEX_T *vertex : old_graph.vertices) {
            pushVertex(vertex->getName());
        }

        for (edgeIterator<VERTEX_T, EDGE_T> iter = old_graph.edge_begin(); iter != old_graph.edge_end(); ++iter) {
            pushEdge(getVertex((*iter)->getSrc()->getIndex()),
                        getVertex((*iter)->getDest()->getIndex()), (*iter)->getWeight());
        }
    }

    graph(unsigned long num_of_vertex, unsigned long num_of_edges, graphTypeE type, graphFormE form) {
        if (form == L) {
            if (type == DIRECTED) {
                this->curForm = new directedL<EDGE_T>;
            } else {
                this->curForm = new nonDirectedL<EDGE_T>;
            }
        } else {
            if (type == DIRECTED) {
                this->curForm = new directedM<EDGE_T>;
            } else {
                this->curForm = new nonDirectedM<EDGE_T>;
            }
        }

        for (int i = 0; i < num_of_vertex; ++i) {
            pushVertex();
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

            if (getEdge(vertices[v1], vertices[v2]) == nullptr) {
                pushEdge(vertices[v1], vertices[v2]);

                if (type == NON_DIRECTED) {
                    i+=2;
                } else {
                    ++i;
                }
            }
        }
    }

    ~graph() {

        delete curForm;

        for (VERTEX_T *vertex : vertices) {
            delete vertex;
        }

        vertices.clear();
    }

    [[nodiscard]] graphTypeE getType() const {
        return curForm->getType();
    }

    [[nodiscard]] graphFormE get_form() const {
        return curForm->getForm();
    }

    void clear() {
        delete curForm;

        for (VERTEX_T *vertex : vertices) {
            delete vertex;
        }

        vertices.clear();
    }

    [[nodiscard]] unsigned long getVertexCount() const {
        return vertices.size();
    }

    [[nodiscard]] unsigned long getEdgeCount() const {
        return curForm->getEdgeCount();
    }

    VERTEX_T *pushVertex() {
        unsigned long index;
        if ((index = curForm->pushVertex())== -1) {
            return nullptr;
        }

        VERTEX_T *vertex = new VERTEX_T(index);
        vertices.push_back(vertex);

        return vertex;
    }

    VERTEX_T *pushVertex(std::string name) {
        VERTEX_T *vertex = pushVertex();
        vertex->setName(name);
        return vertex;
    }

    EDGE_T *pushEdge(VERTEX_T *v1, VERTEX_T *v2) {
        if (v1 == nullptr || v2 == nullptr) {
            return nullptr;
        }

        EDGE_T *edge = new EDGE_T(v1, v2);

        if (curForm->pushEdge(v1->getIndex(), v2->getIndex(), edge)) {
            return edge;
        }

        delete edge;
        return nullptr;
    }

    // Добавляет ребро между вершинами графа, заданными адресами
    // дескрипторов v1 и v2, с весом w и возвращает адрес дескриптора вновь созданного ребра (или уже существующего).
    EDGE_T *pushEdge(VERTEX_T *v1, VERTEX_T *v2, double weight) {
        if (v1 == nullptr || v2 == nullptr) {
            return nullptr;
        }

        EDGE_T *edge = new EDGE_T(v1, v2, weight);

        if (curForm->pushEdge(v1->getIndex(), v2->getIndex(), edge)) {
            return edge;
        }

        delete edge;
        return nullptr;
    }

    EDGE_T *getEdge(VERTEX_T *v1, VERTEX_T *v2) {
        if (v1 == nullptr || v2 == nullptr) {
            return nullptr;
        }

        return curForm->getEdge(v1->getIndex(), v2->getIndex());
    }

    VERTEX_T *getVertex(size_t idx) const {
        if (idx > this->vertices.size() - 1) {
            return nullptr;
        }

        return this->vertices[idx];
    }

    // Удаляет ребро, соединяющее вершины, заданные адресами дескрипторов v1 и v2
    bool popEdge(VERTEX_T *v1, VERTEX_T *v2) {
        if (v1 == nullptr || v2 == nullptr) {
            return false;
        }

        return curForm->popEdge(v1->getIndex(), v2->getIndex());
    }

    bool popEdge(size_t v1_index, size_t v2_index) {
        return curForm->popEdge(v1_index, v2_index);
    }


    // Удаляет вершину из графа, заданную адресом дескриптора
    bool popVertex(VERTEX_T *vertex_ptr) {
        if (vertex_ptr == nullptr) {
            return false;
        }

        size_t index = vertex_ptr->getIndex();


        return popVertex(index);
    }

    // Удаляет вершину из графа по её индексу
    bool popVertex(size_t index) {
        VERTEX_T *vertex_ptr;
        if (index >= vertices.size()) {
            return false;
        }

        vertex_ptr = vertices[index];

        bool is_removed;

        if ((is_removed = curForm->popVertex(index))) {
            vertices.erase(vertices.begin() + index);
            delete vertex_ptr;
        }

        if (is_removed) {
            for (unsigned long i = index; i < vertices.size(); ++i) {
                vertices[i]->forceIndex(i);
            }
        }

        return is_removed;
    }

    vertexIterator<VERTEX_T> vertex_begin() {
        return vertexIterator<VERTEX_T>(vertices.begin());
    }

    vertexIterator<VERTEX_T> vertex_end() {
        return vertexIterator<VERTEX_T>(vertices.end());
    }

    vertexEdgeIter<VERTEX_T, EDGE_T> edge_v_begin(VERTEX_T *vertex) {
        vertexEdgeIter<VERTEX_T, EDGE_T> iter(this, vertex);
        return iter;
    }

    vertexEdgeIter<VERTEX_T, EDGE_T> edge_v_end(VERTEX_T *vertex) {
        vertexEdgeIter<VERTEX_T, EDGE_T> iter(this, vertex);
        iter.setEdge(nullptr);
        return iter;
    }

    edgeIterator<VERTEX_T, EDGE_T> edge_begin() {
        edgeIterator<VERTEX_T, EDGE_T> iter(this);

        EDGE_T *tmp;

        for (VERTEX_T *vertex : vertices) {
            if ((tmp = firstEdge(vertex)) != nullptr) {
                if (getType() == NON_DIRECTED) {
                    do {
                        if (vertex == tmp->getDest()) {
                            continue;
                        }

                        break;
                    } while ((tmp = nextEdge(vertex, tmp)));

                    if (tmp == nullptr) {
                        continue;
                    }
                }

                iter.setVertex(vertex);
                iter.setEdge(tmp);

                return iter;
            }
        }

        iter = edge_end();
        return iter;
    }

    edgeIterator<VERTEX_T, EDGE_T> edge_end() {
        edgeIterator<VERTEX_T, EDGE_T> iter(this);
        iter.setEdge(nullptr);
        iter.setVertex(*vertices.rbegin());

        return iter;
    }

    [[nodiscard]] double getCoefficient() const {
        if (getType() == DIRECTED) {
            return static_cast<double>(getEdgeCount()) / (getVertexCount() * (getVertexCount() - 1));
        }

        return static_cast<double>(getEdgeCount()) / (getVertexCount() * (getVertexCount() - 1) / 2);
    }

    void convertToL() {
        if (get_form() == L) {
            return;
        }

        form<EDGE_T> *newForm;

        if (getType() == DIRECTED) {
            newForm = new directedL<EDGE_T>;
        } else {
            newForm = new nonDirectedL<EDGE_T>;
        }

        for (VERTEX_T *vertex : vertices) {
            newForm->pushVertex();
        }

        edgeIterator<VERTEX_T, EDGE_T> iter(this);

        for (iter = edge_begin(); iter != edge_end(); ++iter) {
            newForm->pushEdge((*iter)->getSrc()->getIndex(),
                                  (*iter)->getDest()->getIndex(), new EDGE_T(**iter));
        }

        delete curForm;
        curForm = newForm;
    }

    void convertToM() {
        if (get_form() == M) {
            return;
        }

        form<EDGE_T> *newForm;

        if (getType() == DIRECTED) {
            newForm = new directedM<EDGE_T>;
        } else {
            newForm = new nonDirectedM<EDGE_T>;
        }

        for (VERTEX_T *vertex : vertices) {
            newForm->pushVertex();
        }

        edgeIterator<VERTEX_T, EDGE_T> iter(this);

        for (iter = edge_begin(); iter != edge_end(); ++iter) {
            newForm->pushEdge((*iter)->getSrc()->getIndex(),
                                  (*iter)->getDest()->getIndex(), new EDGE_T(**iter));
        }

        delete curForm;
        curForm = newForm;
    }

    friend std::ostream& operator<< <>(std::ostream &os, graph<VERTEX_T, EDGE_T> &graph_ptr);
};

#endif //GRAPH_H

