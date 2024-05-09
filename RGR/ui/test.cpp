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

    for (std::vector<double> &distRow : task->result())
    {
        for (double &dist : distRow)
        {
            if (dist == INFINITY)
            {
                cout << "inf" << " ";
            }
            else
            {
                cout << dist << " ";
            }
        }
        cout << endl;
    }

    cout << endl;

    nonWeightedTask<Vertex, Edge> *task2 = new nonWeightedTask<Vertex, Edge>(pretty_graph);

    cout << "Задание для невзвешенного графа: " << endl;

    cout << *(task2->result()) << endl;

    return 0;
}
