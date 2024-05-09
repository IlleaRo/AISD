#ifndef L_H
#define L_H

#include <vector>

#include "common.h"

template <class EDGE_T>
class nonDirectedL : public form<EDGE_T> {
protected:
    using form<EDGE_T>::edgeCount;

    class node {
    public:
        EDGE_T *edge;
        unsigned long dest;
        node *next;
    };

    std::vector<node *> vertices;

    void print(std::ostream &os) override {
        for (int i = 0; i < vertices.size(); ++i) {
            os << i << " : ";
            node *current = vertices[i];
            while (current != nullptr) {
                os << current->dest << " ";
                current = current->next;
            }
            os << std::endl;
        }
    }

public:
    nonDirectedL() : form<EDGE_T>(NON_DIRECTED, L, 0) {};

    ~nonDirectedL() {
        for (int i = 0; i < vertices.size(); ++i) {
            node *current = vertices[i];
            while (current != nullptr) {
                node *temp = current;
                current = current->next;

                if (temp->dest < i) { // Очищаем память каждого ребра только единожды
                    delete temp->edge;
                }
                delete temp;
            }
        }

        vertices.clear();
    }

    unsigned long pushVertex() override {
        vertices.push_back(nullptr);
        return vertices.size() - 1;
    }

    bool pushEdge(unsigned long v_index_1, unsigned long v_index_2, EDGE_T *edge) override {
        if (v_index_1 >= vertices.size() || v_index_2 >= vertices.size()) {
            throw std::out_of_range("out of range exception");
        }

        node *tmp = vertices[v_index_1];

        while (tmp) {
            if (tmp->dest == v_index_2) {
                return false;
            }
            tmp = tmp->next;
        }

        node *new_node = new node;
        new_node->edge = edge;
        new_node->dest = v_index_2;
        new_node->next = vertices[v_index_1];
        vertices[v_index_1] = new_node;

        new_node = new node;
        new_node->edge = edge;
        new_node->dest = v_index_1;
        new_node->next = vertices[v_index_2];
        vertices[v_index_2] = new_node;

        edgeCount++;

        return true;
    }

    bool popVertex(unsigned long vertex_index) override {
        if (vertex_index >= vertices.size()) {
            return false;
        }

        for (unsigned int i = 0; i < vertices.size(); ++i) {
            if (i == vertex_index) {
                node *current = vertices[i];
                while (current != nullptr) {
                    node *temp = current;
                    current = current->next;
                    delete temp;
                }
                continue;
            }

            if (vertices[i] != nullptr) {

                node *current = vertices[i];
                node *prev = nullptr;

                while (current != nullptr) {
                    if (current->dest == vertex_index) {
                        if (current == vertices[i]) {
                            vertices[i] = current->next;
                            if (form<EDGE_T>::type == DIRECTED) {
                                delete current->edge;
                                edgeCount--;
                            }
                            delete current;
                            current = vertices[i];
                            continue;
                        }

                        node *temp = current;
                        prev->next = current->next;
                        current = current->next;

                        delete temp->edge;
                        edgeCount--;

                        delete temp;
                        continue;
                    } else if (current->dest > vertex_index) {
                        current->dest--;
                    }

                    prev = current;
                    current = current->next;
                }
            }
        }

        vertices.erase(vertices.begin() + vertex_index);

        return true;
    }

    EDGE_T *getEdge(unsigned long v1_index, unsigned long v2_index) override {
        if (v1_index >= vertices.size() || v2_index >= vertices.size()) {
            return nullptr;
        }

        node *current = vertices[v1_index];
        while (current != nullptr) {
            if (current->dest == v2_index) {
                return current->edge;
            }
            current = current->next;
        }

        return nullptr;
    }

    bool popEdge(unsigned long v1_index, unsigned long v2_index) override {
        if (v1_index >= vertices.size() || v2_index >= vertices.size()) {
            return false;
        }

        node *current = vertices[v1_index];
        node *prev = nullptr;
        bool verticesRemoved = false;

        while (current != nullptr) {
            if (current->dest == v2_index) {
                if (current == vertices[v1_index]) {
                    vertices[v1_index] = current->next;

                    delete current;

                    verticesRemoved = true;
                    break;
                }

                node *temp = current;
                prev->next = current->next;

                delete temp;

                verticesRemoved = true;
                break;
            }

            prev = current;
            current = current->next;
        }

        if (!verticesRemoved) {
            return false;
        }

        current = vertices[v2_index];
        prev = nullptr;

        while (current != nullptr) {
            if (current->dest == v1_index) {
                if (current == vertices[v2_index]) {
                    vertices[v2_index] = current->next;

                    delete current->edge;
                    delete current;

                    edgeCount--;
                    return true;
                }

                node *temp = current;
                prev->next = current->next;

                delete temp->edge;
                delete temp;

                edgeCount--;
                return true;
            }

            prev = current;
            current = current->next;
        }

        throw std::out_of_range("out of range exception");
    }

    EDGE_T *firstEdge(unsigned long vertex_index) override {
        if (vertex_index >= vertices.size()) {
            throw std::out_of_range("out of range exception");
        }

        return vertices[vertex_index] ? vertices[vertex_index]->edge : nullptr;
    }

    EDGE_T *nextEdge(unsigned long vertex_index, EDGE_T *edge) override {
        if (vertex_index >= vertices.size()) {
            throw std::out_of_range("out of range exception");
        }

        node *current = vertices[vertex_index];
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
class directedL : public nonDirectedL<EDGE_T> {
    using typename nonDirectedL<EDGE_T>::node;
    using nonDirectedL<EDGE_T>::vertices;
    using form<EDGE_T>::type;
    using form<EDGE_T>::edgeCount;

public:
    directedL() : nonDirectedL<EDGE_T>() {
        type = DIRECTED;
    }

    ~directedL() {
        for (typename std::vector<node *>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
            node *current = *it;
            while (current != nullptr) {
                node *temp = current;
                current = current->next;
                delete temp->edge;
                delete temp;
            }
        }

        vertices.clear();
    }

    bool pushEdge(unsigned long v_index_1, unsigned long v_index_2, EDGE_T *edge) override {
        node *tmp = vertices[v_index_1];
        if (tmp == nullptr) {
            node *newNode = new node;
            newNode->edge = edge;
            newNode->dest = v_index_2;
            newNode->next = nullptr;
            vertices[v_index_1] = newNode;

            edgeCount++;

            return true;
        }

        while (tmp->next) {
            if (tmp->dest == v_index_2) {
                return false;
            }
            tmp = tmp->next;
        }

        node *new_node = new node;
        new_node->edge = edge;
        new_node->dest = v_index_2;
        new_node->next = nullptr;
        tmp->next = new_node;

        edgeCount++;

        return true;
    }

    bool popEdge(unsigned long v1_index, unsigned long v2_index) override {
        if (v1_index >= vertices.size() || v2_index >= vertices.size()) {
            return false;
        }

        node *current = vertices[v1_index];
        node *prev = nullptr;

        while (current != nullptr) {
            if (current->dest == v2_index) {
                if (current == vertices[v1_index]) {
                    vertices[v1_index] = current->next;

                    delete current->edge;
                    delete current;

                    edgeCount--;
                    return true;
                }

                node *temp = current;
                prev->next = current->next;

                delete current->edge;
                delete temp;

                edgeCount--;
                return true;
            }

            prev = current;
            current = current->next;
        }

        return false;
    }

    bool popVertex(unsigned long vertex_index) override {
        if (vertex_index >= vertices.size()) {
            return false;
        }

        for (unsigned int i = 0; i < vertices.size(); ++i) {
            if (i == vertex_index) {
                node *current = vertices[i];
                while (current != nullptr) {
                    node *temp = current;
                    current = current->next;
                    delete temp;
                }
                continue;
            }

            if (vertices[i] != nullptr) {

                node *current = vertices[i];
                node *prev = nullptr;

                while (current != nullptr) {
                    if (current->dest == vertex_index) {
                        if (current == vertices[i]) {
                            vertices[i] = current->next;
                            delete current->edge;
                            edgeCount--;

                            delete current;
                            current = vertices[i];
                            continue;
                        }

                        node *temp = current;
                        prev->next = current->next;
                        current = current->next;

                        delete temp->edge;
                        edgeCount--;

                        delete temp;
                        continue;
                    } else if (current->dest > vertex_index) {
                        current->dest--;
                    }

                    prev = current;
                    current = current->next;
                }
            }
        }

        vertices.erase(vertices.begin() + vertex_index);

        return true;
    }
};

#endif //L_H
