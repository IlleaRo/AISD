#ifndef WEIGHTED_H
#define WEIGHTED_H
#include <cfloat>

#include "../graph/graph.h"

template<class VERTEX_T, class EDGE_T>
class weightedTask
{
    private:
        graph<VERTEX_T, EDGE_T> *g;
        std::vector<std::vector<double>> distMatrix;
        std::vector<std::vector<std::vector<VERTEX_T *>>> pathMatrix;

        void allocateVectors()
        {
            distMatrix.clear();
            distMatrix.resize(g->getVertexCount());
            for (std::vector<double> &dists: distMatrix)
            {
                dists.resize(g->getVertexCount());
            }

            pathMatrix.clear();
            pathMatrix.resize(g->getVertexCount());
            for (auto &pathsFrom : pathMatrix)
            {
                pathsFrom.resize(g->getVertexCount());
            }
        }

        void initVectors(std::vector<double> &dists, size_t source)
        {
            for (double &dist: dists)
            {
                dist = INFINITY;
            }
            dists[source] = 0;
        }

        void relaxEdges(std::vector<double> &dists, int source)
        {
            for (size_t i = 0; i < g->getVertexCount() - 1; i++)
            {
                for (EdgeIterator edgeIter = g->edge_begin(); edgeIter != g->edge_end(); ++edgeIter)
                {
                    size_t v1 = (*edgeIter)->getSrc()->getIndex();
                    size_t v2 = (*edgeIter)->getDest()->getIndex();
                    double weight = (*edgeIter)->getWeight();

                    if (dists[v1] != INFINITY && dists[v1] + weight < dists[v2])
                    {
                        dists[v2] = dists[v1] + weight;
                        pathMatrix[source][v2] = pathMatrix[source][v1];
                        pathMatrix[source][v2].push_back(g->getVertex(v2));
                    }
                }
            }
        }

        void checkCycles(std::vector<double> &dists, int source)
        {
            for (EdgeIterator edgeIter = g->edge_begin(); edgeIter != g->edge_end(); ++edgeIter)
            {
                size_t v1 = (*edgeIter)->getSrc()->getIndex();
                size_t v2 = (*edgeIter)->getSrc()->getIndex();
                double weight = (*edgeIter)->getWeight();

                if (dists[v1] != INFINITY && dists[v1] + weight < dists[v2])
                {
                    throw std::out_of_range("negative weight cycle detected");
                }
            }
        }

        void BellmanFord(std::vector<double> &dists, int source)
        {
            initVectors(dists, source);
            relaxEdges(dists, source);
            checkCycles(dists, source);
        }

        void solve()
        {
            allocateVectors();
            for (int i = 0; i < g->getVertexCount(); i++)
            {
                BellmanFord(distMatrix[i], i);
            }
        }

    public:
        explicit weightedTask(graph<VERTEX_T, EDGE_T> *g)
        {
            this->g = g;
            solve();
        }

        weightedTask(weightedTask<VERTEX_T, EDGE_T> &task)
        {
            this->g = task.g;
            solve();
        }

        ~weightedTask() = default;

        void set(graph<VERTEX_T, EDGE_T> &g)
        {
            this = weightedTask(g);
        }

        void restart()
        {
            solve();
        }

        double resultDist(size_t a, size_t b)
        {
            if (a >= this->distMatrix.size() || b >= this->distMatrix[a].size())
            {
                throw std::out_of_range("out of range");
            }
            return this->distMatrix[a][b];
        }

        std::vector<VERTEX_T *> &resultPath(int a, int b)
        {
            if (a >= this->pathMatrix.size() || b >= this->pathMatrix[a].size())
            {
                throw std::out_of_range("out of range");
            }
            return this->pathMatrix[a][b];
        }
};
#endif //WEIGHTED_H
