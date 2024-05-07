#ifndef NON_WEIGHTED_H
#define NON_WEIGHTED_H

template <class VERTEX_T, class EDGE_T>
class nonWeightedTask
{
    private:
    graph<VERTEX_T, EDGE_T> *g;
    graph<VERTEX_T, EDGE_T> *gResult;

    void allocateGraph()
    {
        delete gResult;

        gResult = new graph<VERTEX_T, EDGE_T>();
    }

    void reduce()
    {

    }

    void solve()
    {
        allocateGraph();
        reduce();
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

    ~nonWeightedTask()
    {
        delete this->gResult;
    }

    void set(graph<VERTEX_T, EDGE_T> &g)
    {
        this = nonWightedTask(g);
    }

    void restart()
    {
        solve();
    }

    graph<VERTEX_T, EDGE_T> *result()
    {
        return this->g;
    }
};

#endif //NON_WEIGHTED_H
