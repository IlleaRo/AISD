#ifndef M_H
#define M_H

#include <vector>

template<class EDGE_T>
class nonDirectedM : public form<EDGE_T>
{
    protected:
        using form<EDGE_T>::edgeCount;
        std::vector<std::vector<EDGE_T *> > vertices;

        void print(std::ostream &os) override
        {
            os << "   ";

            for (int i = 0; i < vertices.size(); ++i)
            {
                os << i << " ";
            }

            for (unsigned long i = 0; i < vertices.size(); ++i)
            {
                os << '\n' << i << "  ";
                for (unsigned long j = 0; j < vertices[i].size(); ++j)
                {
                    os << (vertices[i][j] ? "1" : " ") << " ";
                }
            }
        }

    public:
        nonDirectedM() : form<EDGE_T>(NON_DIRECTED, M, 0)
        {
        };

        ~nonDirectedM()
        {
            for (unsigned long i = 0; i < vertices.size(); ++i)
            {
                for (unsigned long j = 0; j < vertices[i].size(); ++j)
                {
                    if (vertices[i][j] != nullptr && vertices[i][j]->getDest()->getIndex() < i)
                    {
                        delete vertices[i][j];
                    }
                }
            }
        }

        unsigned long pushVertex() override
        {
            vertices.push_back(std::vector<EDGE_T *>(vertices.size(), nullptr));
            for (std::vector<EDGE_T *> &edge: vertices)
            {
                edge.push_back(nullptr);
            }
            return vertices.size() - 1;
        }

        bool pushEdge(unsigned long v_index_1, unsigned long v_index_2, EDGE_T *edge) override
        {
            if (v_index_1 >= vertices.size() || v_index_2 >= vertices.size())
            {
                throw std::out_of_range("out of range exception");
            }

            if (vertices[v_index_1][v_index_2] != nullptr)
            {
                return false;
            }

            vertices[v_index_1][v_index_2] = edge;
            vertices[v_index_2][v_index_1] = edge;

            edgeCount++;

            return true;
        }

        bool popVertex(unsigned long vertex_index) override
        {
            if (vertex_index >= vertices.size())
            {
                return false;
            }

            std::vector<EDGE_T *> adjacentEdges = vertices[vertex_index];

            for (std::vector<EDGE_T *> &edges: vertices)
            {
                if (edges == adjacentEdges)
                {
                    continue;
                }

                for (unsigned long i = vertex_index; i < edges.size() - 1; ++i)
                {
                    edges[i] = edges[i + 1];
                }

                edges.pop_back();
            }

            for (EDGE_T *edge: adjacentEdges)
            {
                delete edge;
            }

            for (unsigned int i = vertex_index; i < vertices.size() - 1; ++i)
            {
                vertices[i] = vertices[i + 1];
            }

            for (EDGE_T *edge: vertices.back())
            {
                delete edge;
            }
            vertices.pop_back();

            return true;
        }

        EDGE_T *getEdge(unsigned long v1_index, unsigned long v2_index) override
        {
            if (v1_index >= vertices.size() || v2_index >= vertices.size())
            {
                return nullptr;
            }

            return vertices[v1_index][v2_index];
        }

        bool popEdge(unsigned long v1_index, unsigned long v2_index) override
        {
            if (v1_index >= vertices.size() || v2_index >= vertices.size())
            {
                return false;
            }

            if (vertices[v1_index][v2_index] == nullptr)
            {
                return false;
            }

            delete vertices[v1_index][v2_index];
            vertices[v1_index][v2_index] = nullptr;

            vertices[v2_index][v1_index] = nullptr;

            edgeCount--;

            return true;
        }

        EDGE_T *firstEdge(unsigned long vertex_index) override
        {
            if (vertex_index >= vertices.size())
            {
                throw std::out_of_range("out of range exception");
            }

            for (unsigned long i = 0; i < vertices.size(); ++i)
            {
                if (vertices[vertex_index][i] != nullptr)
                {
                    return vertices[vertex_index][i];
                }
            }

            return nullptr;
        }

        EDGE_T *nextEdge(unsigned long vertex_index, EDGE_T *edge) override
        {
            if (vertex_index >= vertices.size())
            {
                throw std::out_of_range("out of range exception");
            }

            for (unsigned long i = 0; i < vertices.size(); ++i)
            {
                if (vertices[vertex_index][i] == edge)
                {
                    for (unsigned long j = i + 1; j < vertices.size(); ++j)
                    {
                        if (vertices[vertex_index][j] != nullptr)
                        {
                            return vertices[vertex_index][j];
                        }
                    }
                    return nullptr;
                }
            }

            return nullptr;
        }
};

template<class EDGE_T>
class directedM : public nonDirectedM<EDGE_T>
{
    using nonDirectedM<EDGE_T>::vertices;
    using form<EDGE_T>::edgeCount;
    using form<EDGE_T>::type;

    public:
        directedM() : nonDirectedM<EDGE_T>()
        {
            type = DIRECTED;
        }

        ~directedM()
        {
            for (std::vector<EDGE_T *> &edge: vertices)
            {
                for (EDGE_T *e: edge)
                {
                    delete e;
                }
            }
            vertices.clear();
        }

        bool pushEdge(unsigned long v_index_1, unsigned long v_index_2, EDGE_T *edge) override
        {
            if (v_index_1 >= vertices.size() || v_index_2 >= vertices.size())
            {
                throw std::out_of_range("out of range exception");
            }

            if (vertices[v_index_1][v_index_2] != nullptr)
            {
                return false;
            }

            vertices[v_index_1][v_index_2] = edge;

            edgeCount++;

            return true;
        }

        bool popEdge(unsigned long v1_index, unsigned long v2_index) override
        {
            if (v1_index >= vertices.size() || v2_index >= vertices.size())
            {
                return false;
            }

            if (vertices[v1_index][v2_index] == nullptr)
            {
                return false;
            }

            delete vertices[v1_index][v2_index];
            vertices[v1_index][v2_index] = nullptr;

            edgeCount--;

            return true;
        }
};

#endif //M_H
