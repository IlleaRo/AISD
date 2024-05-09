#include "test.h"
#include "menu.h"
#include "../graphs/graph.h"
#include "../tasks/weighted.h"
#include "../tasks/non-weighted.h"

using namespace std;

int run_test() {
    std::vector<example_vertex *> test_vertices;
    example_graph *pretty_graph = new example_graph(0, DIRECTED, L);

    for (int i = 0; i < 10; i++)
    {
        example_vertex *vertex = pretty_graph->insert_vertex();
        test_vertices.push_back(vertex);
    }

    for (int i = 0; i < 9; i++)
    {
        pretty_graph->insert_edge(test_vertices[i], test_vertices[i + 1], rand() % 100);
        pretty_graph->insert_edge(test_vertices[i], test_vertices[i + 2], rand() % 100);
        pretty_graph->insert_edge(test_vertices[i + 2], test_vertices[i], rand() % 100);
    }

    weightedTask<example_vertex, example_edge> *task = new weightedTask<example_vertex, example_edge>(pretty_graph);

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

    nonWeightedTask<example_vertex, example_edge> *task2 = new nonWeightedTask<example_vertex, example_edge>(pretty_graph);

    cout << "Задание для невзвешенного графа: " << endl;

    cout << *(task2->result()) << endl;

    return 0;
}
