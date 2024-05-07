#ifndef WEIGHTED_H
#define WEIGHTED_H
#include <cfloat>

#include "../graphs/graph.h"

template <class VERTEX_T, class EDGE_T>
class weightedTask
{
    private:
    graph<VERTEX_T, EDGE_T> *g;
    std::vector<double> dist;

    void allocateDist()
    {
        dist.clear();
    }

    void BellmanFord()
    {

    }

    void solve()
    {
        allocateDist();
        BellmanFord();
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

    std::vector<double> &result()
    {
        return this->dist;
    }
};
#endif //WEIGHTED_H
