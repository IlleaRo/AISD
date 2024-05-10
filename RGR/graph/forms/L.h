#ifndef L_H
#define L_H

#include <vector>

#include "common.h"

template<class EDGE_T>
class nonDirectedL : public form<EDGE_T>
{
    protected:
        using form<EDGE_T>::edgeCount;

        class node
        {
            public:
                EDGE_T *edge;
                unsigned long dest;
                node *next;
        };

        std::vector<node *> vertices;

        void print(std::ostream &os) override
        {
            for (int i = 0; i < vertices.size(); ++i)
            {
                os << i << ": ";
                node *current = vertices[i];
                while (current != nullptr)
                {
                    os << current->dest << " ";
                    current = current->next;
                }
                os << std::endl;
            }
        }

    public:
        nonDirectedL() : form<EDGE_T>(NON_DIRECTED, L, 0)
        {
        };

        ~nonDirectedL()
        {
            for (int i = 0; i < vertices.size(); ++i)
            {
                node *current = vertices[i];
                while (current != nullptr)
                {
                    node *temp = current;
                    current = current->next;

                    if (temp->dest < i)
                    {
                        delete temp->edge;
                    }
                    delete temp;
                }
            }

            vertices.clear();
        }

        unsigned long pushVertex() override
        {
            vertices.push_back(nullptr);
            return vertices.size() - 1;
        }

        bool pushEdge(unsigned long srcIdx, unsigned long destIdx, EDGE_T *edge) override
        {
            if (srcIdx >= vertices.size() || destIdx >= vertices.size())
            {
                throw std::out_of_range("out of range exception");
            }

            node *tmp = vertices[srcIdx];

            while (tmp)
            {
                if (tmp->dest == destIdx)
                {
                    return false;
                }
                tmp = tmp->next;
            }

            node *new_node = new node;
            new_node->edge = edge;
            new_node->dest = destIdx;
            new_node->next = vertices[srcIdx];
            vertices[srcIdx] = new_node;

            new_node = new node;
            new_node->edge = edge;
            new_node->dest = srcIdx;
            new_node->next = vertices[destIdx];
            vertices[destIdx] = new_node;

            edgeCount++;

            return true;
        }

        bool popVertex(unsigned long vertexIdx) override
        {
            if (vertexIdx >= vertices.size())
            {
                return false;
            }

            for (unsigned int i = 0; i < vertices.size(); ++i)
            {
                if (i == vertexIdx)
                {
                    node *current = vertices[i];
                    while (current != nullptr)
                    {
                        node *temp = current;
                        current = current->next;
                        delete temp;
                    }
                    continue;
                }

                if (vertices[i] != nullptr)
                {
                    node *current = vertices[i];
                    node *prev = nullptr;

                    while (current != nullptr)
                    {
                        if (current->dest == vertexIdx)
                        {
                            if (current == vertices[i])
                            {
                                vertices[i] = current->next;
                                if (form<EDGE_T>::type == DIRECTED)
                                {
                                    delete current->edge;
                                }
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
                        }
                        else if (current->dest > vertexIdx)
                        {
                            current->dest--;
                        }

                        prev = current;
                        current = current->next;
                    }
                }
            }

            vertices.erase(vertices.begin() + vertexIdx);

            return true;
        }

        EDGE_T *getEdge(unsigned long srcIndex, unsigned long destIdx) override
        {
            if (srcIndex >= vertices.size() || destIdx >= vertices.size())
            {
                return nullptr;
            }

            node *current = vertices[srcIndex];
            while (current != nullptr)
            {
                if (current->dest == destIdx)
                {
                    return current->edge;
                }
                current = current->next;
            }

            return nullptr;
        }

        bool popEdge(unsigned long srcIndex, unsigned long destIdx) override
        {
            if (srcIndex >= vertices.size() || destIdx >= vertices.size())
            {
                return false;
            }

            node *current = vertices[srcIndex];
            node *prev = nullptr;
            bool verticesRemoved = false;

            while (current != nullptr)
            {
                if (current->dest == destIdx)
                {
                    if (current == vertices[srcIndex])
                    {
                        vertices[srcIndex] = current->next;

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

            if (!verticesRemoved)
            {
                return false;
            }

            current = vertices[destIdx];
            prev = nullptr;

            while (current != nullptr)
            {
                if (current->dest == srcIndex)
                {
                    if (current == vertices[destIdx])
                    {
                        vertices[destIdx] = current->next;

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

        EDGE_T *firstEdge(unsigned long vertexIdx) override
        {
            if (vertexIdx >= vertices.size())
            {
                throw std::out_of_range("out of range exception");
            }

            return vertices[vertexIdx] ? vertices[vertexIdx]->edge : nullptr;
        }

        EDGE_T *nextEdge(unsigned long vertexIdx, EDGE_T *edge) override
        {
            if (vertexIdx >= vertices.size())
            {
                throw std::out_of_range("out of range exception");
            }

            node *current = vertices[vertexIdx];
            while (current != nullptr)
            {
                if (current->edge == edge)
                {
                    return current->next ? current->next->edge : nullptr;
                }
                current = current->next;
            }

            return nullptr;
        }
};

template<class EDGE_T>
class directedL : public nonDirectedL<EDGE_T>
{
    using typename nonDirectedL<EDGE_T>::node;
    using nonDirectedL<EDGE_T>::vertices;
    using form<EDGE_T>::type;
    using form<EDGE_T>::edgeCount;

    public:
        directedL() : nonDirectedL<EDGE_T>()
        {
            type = DIRECTED;
        }

        ~directedL()
        {
            for (typename std::vector<node *>::iterator it = vertices.begin(); it != vertices.end(); ++it)
            {
                node *current = *it;
                while (current != nullptr)
                {
                    node *temp = current;
                    current = current->next;
                    delete temp->edge;
                    delete temp;
                }
            }

            vertices.clear();
        }

        bool pushEdge(unsigned long srcIdx, unsigned long destIdx, EDGE_T *edge) override
        {
            node *tmp = vertices[srcIdx];
            if (tmp == nullptr)
            {
                node *newNode = new node;
                newNode->edge = edge;
                newNode->dest = destIdx;
                newNode->next = nullptr;
                vertices[srcIdx] = newNode;

                edgeCount++;

                return true;
            }

            while (tmp->next)
            {
                if (tmp->dest == destIdx)
                {
                    return false;
                }
                tmp = tmp->next;
            }

            node *new_node = new node;
            new_node->edge = edge;
            new_node->dest = destIdx;
            new_node->next = nullptr;
            tmp->next = new_node;

            edgeCount++;

            return true;
        }

        bool popEdge(unsigned long srcIndex, unsigned long destIdx) override
        {
            if (srcIndex >= vertices.size() || destIdx >= vertices.size())
            {
                return false;
            }

            node *current = vertices[srcIndex];
            node *prev = nullptr;

            while (current != nullptr)
            {
                if (current->dest == destIdx)
                {
                    if (current == vertices[srcIndex])
                    {
                        vertices[srcIndex] = current->next;

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

        bool popVertex(unsigned long vertexIdx) override
        {
            if (vertexIdx >= vertices.size())
            {
                return false;
            }

            for (unsigned int i = 0; i < vertices.size(); ++i)
            {
                if (i == vertexIdx)
                {
                    node *current = vertices[i];
                    while (current != nullptr)
                    {
                        node *temp = current;
                        current = current->next;
                        delete temp;
                        edgeCount--;
                    }
                    continue;
                }

                if (vertices[i] != nullptr)
                {
                    node *current = vertices[i];
                    node *prev = nullptr;

                    while (current != nullptr)
                    {
                        if (current->dest == vertexIdx)
                        {
                            if (current == vertices[i])
                            {
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
                        }
                        else if (current->dest > vertexIdx)
                        {
                            current->dest--;
                        }

                        prev = current;
                        current = current->next;
                    }
                }
            }

            vertices.erase(vertices.begin() + vertexIdx);

            return true;
        }
};

#endif //L_H
