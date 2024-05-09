#ifndef NON_WEIGHTED_H
#define NON_WEIGHTED_H

#include <stack>

template<class VERTEX_T, class EDGE_T>
class nonWeightedTask
{
    private:
        graph<VERTEX_T, EDGE_T> *g;
        graph<VERTEX_T, EDGE_T> *gResult;

        void allocateGraph()
        {
            delete gResult;

            gResult = new graph<VERTEX_T, EDGE_T>(*g);
        }

        std::vector<std::vector<size_t> > Tarjan()
        {
            size_t vertexCount = gResult->getVertexCount();
            size_t visits = 0;

            std::vector<size_t> disc(vertexCount, 0);
            std::vector<size_t> low(vertexCount, 0);
            std::vector<bool> visited(vertexCount, false);
            std::stack<size_t> vertexStack;
            std::vector<std::vector<size_t> > SCCs(vertexCount);

            for (size_t i = 0; i < vertexCount; i++)
                if (disc[i] == 0)
                {
                    SCCs[i] = TarjanVisit(i, visits, disc, low, vertexStack, visited);
                }
            return SCCs;
        }

        std::vector<size_t> TarjanVisit(size_t index, size_t &visits, std::vector<size_t> &disc, std::vector<size_t> &low, std::stack<size_t> &vertexStack,
                                        std::vector<bool> &visited)
        {
            // A static variable is used for simplicity, we can
            // avoid use of static variable by passing a pointer.
            std::vector<size_t> SCCsPart;

            disc[index] = low[index] = ++visits;
            vertexStack.push(index);
            visited[index] = true;

            for (auto iter = gResult->edge_v_begin(gResult->getVertex(index));
                 iter != gResult->edge_v_end(gResult->getVertex(index));
                 ++iter)
            {
                VERTEX_T *adj = (*iter)->getDest();

                if (!visited[adj->getIndex()])
                {
                    TarjanVisit(adj->getIndex(), visits, disc, low, vertexStack, visited);

                    low[index] = std::min(low[index], low[adj->getIndex()]);
                }
                else
                {
                    low[index] = std::min(low[index], disc[adj->getIndex()]);
                }
            }

            if (low[index] == disc[index])
            {
                size_t curIndex = 0;
                while (vertexStack.top() != index)
                {
                    curIndex = vertexStack.top();
                    SCCsPart.push_back(curIndex);
                    visited[curIndex] = false;
                    vertexStack.pop();
                }
                curIndex = vertexStack.top();
                SCCsPart.push_back(curIndex);
                visited[curIndex] = false;
                vertexStack.pop();
            }
            return SCCsPart;
        }

        void reduce(std::vector<std::vector<size_t> > SCCs)
        {
            for (auto &component: SCCs)
            {
                for (size_t i = 0; i < component.size(); ++i)
                {
                    for (size_t j = i + 1; j < component.size(); ++j)
                    {
                        gResult->popEdge(component[i], component[j]);
                    }
                }
            }
        }

        void solve()
        {
            std::vector<std::vector<size_t> > SCCs;
            allocateGraph();
            SCCs = Tarjan();
            reduce(SCCs);
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
            return this->gResult;
        }
};

#endif //NON_WEIGHTED_H
