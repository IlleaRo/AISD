#include <iostream>

#include "test.h"
#include "menu.h"
#include "../graph/graph.h"
#include "../tasks/weighted.h"
#include "../tasks/nonWeighted.h"

using namespace std;

int run_test()
{
    std::vector<Vertex *> test_vertices;
    Graph *pretty_graph = new Graph(0, DIRECTED, L);

    for (int i = 0; i < 10; i++)
    {
        Vertex *vertex = pretty_graph->pushVertex();
        test_vertices.push_back(vertex);
    }

    for (int i = 0; i < 9; i++)
    {
        pretty_graph->pushEdge(test_vertices[i], test_vertices[i + 1], rand() % 100);
        pretty_graph->pushEdge(test_vertices[i], test_vertices[i + 2], rand() % 100);
        pretty_graph->pushEdge(test_vertices[i + 2], test_vertices[i], rand() % 100);
    }

    weightedTask<Vertex, Edge> *task = new weightedTask<Vertex, Edge>(pretty_graph);

    cout << "Исходный граф:" << endl;

    cout << *pretty_graph << endl;

    cout << "Задание для взвешенного графа: " << endl;

    for (size_t i = 0; i < pretty_graph->getVertexCount(); i++)
    {
        for (size_t j = 0; j < pretty_graph->getVertexCount(); j++)
        {
            if (task->resultDist(i, j) == INFINITY)
            {
                cout << "inf" << " ";
            }
            else
            {
                cout << task->resultDist(i, j) << " ";
            }
        }
        cout << endl;
    }

    for (size_t i = 0; i < pretty_graph->getVertexCount(); i++)
    {
        cout << "Пути из вершины " << i << ":" << endl;
        for (size_t j = 0; j < pretty_graph->getVertexCount(); j++)
        {
            cout << "В вершину " << j << ": ";
            for (size_t k = 0; k < task->resultPath(i, j).size(); k++)
            {
                cout << task->resultPath(i, j)[k]->getIndex() << " ";
            }
            cout << endl;
        }
    }

    cout << endl;

    nonWeightedTask<Vertex, Edge> *task2 = new nonWeightedTask<Vertex, Edge>(pretty_graph);

    cout << "Задание для невзвешенного графа: " << endl;

    for (const auto& cycle : task2->result())
    {
        for (Vertex *v : cycle)
        {
            cout << v->getIndex() << " ";
        }
    }

    cout << endl;

    return 0;
}
