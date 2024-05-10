#ifndef M_H
#define M_H

#include <vector>

template<class EDGE_T>
class nonDirectedM : public form<EDGE_T>
{
    protected:
        using form<EDGE_T>::edgeCount;
        std::vector<std::vector<EDGE_T *> > edges;

        void print(std::ostream &os) override
        {
            os << "   ";

            for (int i = 0; i < edges.size(); ++i)
            {
                os << i << " ";
            }

            for (unsigned long i = 0; i < edges.size(); ++i)
            {
                os << '\n' << i << "  ";
                for (unsigned long j = 0; j < edges[i].size(); ++j)
                {
                    os << (edges[i][j] ? "*" : " ") << " ";
                }
            }
        }

    public:
        nonDirectedM() : form<EDGE_T>(NON_DIRECTED, M, 0)
        {
        };

        ~nonDirectedM()
        {
            for (unsigned long i = 0; i < edges.size(); ++i)
            {
                for (unsigned long j = 0; j < edges[i].size(); ++j)
                {
                    if (edges[i][j] != nullptr && edges[i][j]->getDest()->getIndex() < i)
                    {
                        delete edges[i][j];
                    }
                }
            }
        }

        unsigned long pushVertex() override
        {
            edges.push_back(std::vector<EDGE_T *>(edges.size(), nullptr));
            for (std::vector<EDGE_T *> &edge: edges)
            {
                edge.push_back(nullptr);
            }
            return edges.size() - 1;
        }

        bool pushEdge(unsigned long v_index_1, unsigned long v_index_2, EDGE_T *edge) override
        {
            if (v_index_1 >= edges.size() || v_index_2 >= edges.size())
            {
                throw std::out_of_range("out of range exception");
            }

            if (edges[v_index_1][v_index_2] != nullptr)
            {
                return false;
            }

            edges[v_index_1][v_index_2] = edge;
            edges[v_index_2][v_index_1] = edge;

            edgeCount++;

            return true;
        }

        bool popVertex(unsigned long vertex_index) override
        {
            if (vertex_index >= edges.size())
            {
                return false;
            }

            std::vector<EDGE_T *> adjacentEdges = edges[vertex_index];

            for (std::vector<EDGE_T *> &edges: edges)
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

            for (EDGE_T *&edge: adjacentEdges)
            {
                delete edge;
            }

            for (unsigned int i = vertex_index; i < edges.size() - 1; ++i)
            {
                edges[i] = edges[i + 1];
            }

            for (EDGE_T *&edge: edges.back())
            {
                delete edge;
            }
            edges.pop_back();

            edgeCount = 0;
            for (size_t i = 0; i < edges.size(); i++)
            {
                for (size_t j = 0; j < edges[i].size(); j++)
                {
                    if (edges[i][j] != nullptr)
                    {
                        edgeCount++;
                    }
                }
            }

            return true;
        }

        EDGE_T *getEdge(unsigned long v1_index, unsigned long v2_index) override
        {
            if (v1_index >= edges.size() || v2_index >= edges.size())
            {
                return nullptr;
            }

            return edges[v1_index][v2_index];
        }

        bool popEdge(unsigned long v1_index, unsigned long v2_index) override
        {
            if (v1_index >= edges.size() || v2_index >= edges.size())
            {
                return false;
            }

            if (edges[v1_index][v2_index] == nullptr)
            {
                return false;
            }

            delete edges[v1_index][v2_index];
            edges[v1_index][v2_index] = nullptr;

            edges[v2_index][v1_index] = nullptr;

            edgeCount--;

            return true;
        }

        EDGE_T *firstEdge(unsigned long vertex_index) override
        {
            if (vertex_index >= edges.size())
            {
                throw std::out_of_range("out of range exception");
            }

            for (unsigned long i = 0; i < edges.size(); ++i)
            {
                if (edges[vertex_index][i] != nullptr)
                {
                    return edges[vertex_index][i];
                }
            }

            return nullptr;
        }

        EDGE_T *nextEdge(unsigned long vertex_index, EDGE_T *edge) override
        {
            if (vertex_index >= edges.size())
            {
                throw std::out_of_range("out of range exception");
            }

            for (unsigned long i = 0; i < edges.size(); ++i)
            {
                if (edges[vertex_index][i] == edge)
                {
                    for (unsigned long j = i + 1; j < edges.size(); ++j)
                    {
                        if (edges[vertex_index][j] != nullptr)
                        {
                            return edges[vertex_index][j];
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
    using nonDirectedM<EDGE_T>::edges;
    using form<EDGE_T>::edgeCount;
    using form<EDGE_T>::type;

    public:
        directedM() : nonDirectedM<EDGE_T>()
        {
            type = DIRECTED;
        }

        ~directedM()
        {
            for (std::vector<EDGE_T *> &edge: edges)
            {
                for (EDGE_T *e: edge)
                {
                    delete e;
                }
            }
            edges.clear();
        }

        bool pushEdge(unsigned long v_index_1, unsigned long v_index_2, EDGE_T *edge) override
        {
            if (v_index_1 >= edges.size() || v_index_2 >= edges.size())
            {
                throw std::out_of_range("out of range exception");
            }

            if (edges[v_index_1][v_index_2] != nullptr)
            {
                return false;
            }

            edges[v_index_1][v_index_2] = edge;

            edgeCount++;

            return true;
        }

        bool popEdge(unsigned long v1_index, unsigned long v2_index) override
        {
            if (v1_index >= edges.size() || v2_index >= edges.size())
            {
                return false;
            }

            if (edges[v1_index][v2_index] == nullptr)
            {
                return false;
            }

            delete edges[v1_index][v2_index];
            edges[v1_index][v2_index] = nullptr;

            edgeCount--;

            return true;
        }
};

#endif //M_H
