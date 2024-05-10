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

        bool pushEdge(unsigned long srcIdx, unsigned long destIdx, EDGE_T *edge) override
        {
            if (srcIdx >= edges.size() || destIdx >= edges.size())
            {
                throw std::out_of_range("out of range exception");
            }

            if (edges[srcIdx][destIdx] != nullptr)
            {
                return false;
            }

            edges[srcIdx][destIdx] = edge;
            edges[destIdx][srcIdx] = edge;

            edgeCount++;

            return true;
        }

        bool popVertex(unsigned long index) override
        {
            if (index >= edges.size())
            {
                return false;
            }

            std::vector<EDGE_T *> adjacentEdges = edges[index];

            for (std::vector<EDGE_T *> &edges: edges)
            {
                if (edges == adjacentEdges)
                {
                    continue;
                }

                for (unsigned long i = index; i < edges.size() - 1; ++i)
                {
                    edges[i] = edges[i + 1];
                }

                edges.pop_back();
            }

            for (EDGE_T *&edge: adjacentEdges)
            {
                delete edge;
            }

            for (unsigned int i = index; i < edges.size() - 1; ++i)
            {
                edges[i] = edges[i + 1];
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

        EDGE_T *getEdge(unsigned long srcIdx, unsigned long destIdx) override
        {
            if (srcIdx >= edges.size() || destIdx >= edges.size())
            {
                return nullptr;
            }

            return edges[srcIdx][destIdx];
        }

        bool popEdge(unsigned long srcIdx, unsigned long destIdx) override
        {
            if (srcIdx >= edges.size() || destIdx >= edges.size())
            {
                return false;
            }

            if (edges[srcIdx][destIdx] == nullptr)
            {
                return false;
            }

            delete edges[srcIdx][destIdx];
            edges[srcIdx][destIdx] = nullptr;

            edges[destIdx][srcIdx] = nullptr;

            edgeCount--;

            return true;
        }

        EDGE_T *firstEdge(unsigned long vertexIdx) override
        {
            if (vertexIdx >= edges.size())
            {
                throw std::out_of_range("out of range exception");
            }

            for (unsigned long i = 0; i < edges.size(); ++i)
            {
                if (edges[vertexIdx][i] != nullptr)
                {
                    return edges[vertexIdx][i];
                }
            }

            return nullptr;
        }

        EDGE_T *nextEdge(unsigned long vertexIdx, EDGE_T *edge) override
        {
            if (vertexIdx >= edges.size())
            {
                throw std::out_of_range("out of range exception");
            }

            for (unsigned long i = 0; i < edges.size(); ++i)
            {
                if (edges[vertexIdx][i] == edge)
                {
                    for (unsigned long j = i + 1; j < edges.size(); ++j)
                    {
                        if (edges[vertexIdx][j] != nullptr)
                        {
                            return edges[vertexIdx][j];
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

        bool pushEdge(unsigned long srcIdx, unsigned long destIdx, EDGE_T *edge) override
        {
            if (srcIdx >= edges.size() || destIdx >= edges.size())
            {
                throw std::out_of_range("out of range exception");
            }

            if (edges[srcIdx][destIdx] != nullptr)
            {
                return false;
            }

            edges[srcIdx][destIdx] = edge;

            edgeCount++;

            return true;
        }

        bool popEdge(unsigned long srcIndex, unsigned long destIdx) override
        {
            if (srcIndex >= edges.size() || destIdx >= edges.size())
            {
                return false;
            }

            if (edges[srcIndex][destIdx] == nullptr)
            {
                return false;
            }

            delete edges[srcIndex][destIdx];
            edges[srcIndex][destIdx] = nullptr;

            edgeCount--;

            return true;
        }
};

#endif //M_H
