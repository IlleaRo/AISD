#include "test.h"
#include "menu.h"
#include "../graphs/graph.h"
#include "../tasks/weighted.h"

using namespace std;

int run_test() {
    std::vector<example_vertex *> test_vertices;
    example_graph *pretty_graph = new example_graph();

    for (int i = 0; i < 10; i++)
    {
        example_vertex *vertex = pretty_graph->insert_vertex();
        test_vertices.push_back(vertex);
    }

    for (int i = 0; i < 9; i += 2)
    {
        pretty_graph->insert_edge(test_vertices[i], test_vertices[i + 1]);
    }

    weightedTask<example_vertex, example_edge> *task = new weightedTask<example_vertex, example_edge>(pretty_graph);

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
    return 0;
}
