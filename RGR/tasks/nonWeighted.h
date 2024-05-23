#ifndef NON_WEIGHTED_H
#define NON_WEIGHTED_H

#include <algorithm>

template<class VERTEX_T, class EDGE_T>
class nonWeightedTask
{
    private:
        graph<VERTEX_T, EDGE_T> *g;
        std::vector<std::vector<VERTEX_T *>> res;

        bool isSafe(VERTEX_T *vertex, std::vector<VERTEX_T *> &path, graph<VERTEX_T, EDGE_T> *g)
        {
            if (path.size() == g->getVertexCount() - 1)
            {
                // checking for edge between first and last vertices
                return g->getEdge(path[path.size() - 1], vertex) != nullptr;
            }

            // if current vertex is adjacent to the last vertex in the path and if the vertex is not already in the path
            return g->getEdge(path[path.size() - 1], vertex) && std::find(path.begin(), path.end(), vertex) == path.end();
        }
        bool HamiltonianCycle(graph<VERTEX_T, EDGE_T> *g, std::vector<VERTEX_T *> &path)
        {
            // cycle found
            if (path.size() == g->getVertexCount())
            {
                // If there is an edge between the last vertex and first vertex in the path
                if (g->getEdge(path[path.size() - 1], path[0]))
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }

            // try for all vertices as the next vertex in the cycle
            for (size_t i = 0; i < g->getVertexCount(); i++)
            {
                VERTEX_T *vertex = g->getVertex(i);
                if (isSafe(vertex, path, g))
                {
                    // add the vertex to the path
                    path.push_back(vertex);

                    // recurse for the rest of the graph
                    if (HamiltonianCycle(g, path))
                    {
                        return true;
                    }

                    // remove the vertex from the path, before trying other vertices (backtracking)
                    path.pop_back();
                }
            }

            return false;
        }

        void findHamiltonianCycles()
        {
            std::vector<VERTEX_T *> path;
            bool isHamiltonian;

            // try for all vertices as the starting vertex
            for (size_t i = 0; i < g->getVertexCount(); i++)
            {
                VERTEX_T *vertex = g->getVertex(i);
                path.clear();
                path.push_back(vertex);

                isHamiltonian = HamiltonianCycle(g, path);

                // save the cycle if one is found
                if (isHamiltonian)
                {
                    this->res.push_back(path);
                }
            }
        }

        void solve()
        {
            res.clear();
            findHamiltonianCycles();
        }

    public:
        explicit nonWeightedTask(graph<VERTEX_T, EDGE_T> *g)
        {
            this->g = g;
            solve();
        }

        nonWeightedTask(nonWeightedTask<VERTEX_T, EDGE_T> &task)
        {
            this->g = task.g;
            solve();
        }

        ~nonWeightedTask() = default;

        void set(graph<VERTEX_T, EDGE_T> &g)
        {
            this = nonWightedTask(g);
        }

        void restart()
        {
            solve();
        }

        std::vector<std::vector<VERTEX_T *>> &result()
        {
            return this->res;
        }
};

#endif //NON_WEIGHTED_H
