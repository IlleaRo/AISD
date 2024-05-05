#include "test.h"
#include "menu.h"
#include "../graphs/graph.h"
#include "../tasks/task_2/PFS.h"
#include "../tasks/task_3/allSP.h"

#define TEST_EDGE_REMOVAL (0)
#define TEST_EDGE_TYPE NON_DIRECTED
#define TEST_EDGE_FORM L

int run_test() {
#if TEST_EDGE_REMOVAL
    std::vector<example_vertex *> test_vertices;
    example_graph pretty_graph = example_graph(0, TEST_EDGE_TYPE, TEST_EDGE_FORM);

    for (int i = 0; i < 10; i++)
    {
        example_vertex *vertex = pretty_graph.insert_vertex();
        test_vertices.push_back(vertex);
    }

    for (int i = 0; i < 9; i += 2)
    {
        pretty_graph.insert_edge(test_vertices[i], test_vertices[i + 1]);
    }

    std::cout << "Исходный граф:" << std::endl;
    std::cout << pretty_graph << std::endl;

    std::cout << "Удаление рёбер:" << std::endl;
    for (int i = 0; i < 9; i += 2)
    {
        pretty_graph.remove_edge(test_vertices[i], test_vertices[i + 1]);
        std::cout << pretty_graph << std::endl;
    }

    std::cout << "------------------------------------------" << std::endl;

    for (int i = 0; i < 9; i++)
    {
        pretty_graph.insert_edge(test_vertices[i], test_vertices[i + 1]);
    }

    std::cout << "Исходный граф:" << std::endl;
    std::cout << pretty_graph << std::endl;

    std::cout << "Удаление рёбер:" << std::endl;
    for (int i = 0; i < 9; i++)
    {
        pretty_graph.remove_edge(test_vertices[i], test_vertices[i + 1]);
        std::cout << pretty_graph << std::endl;
    }

#else
    graph<vertex<std::string, int>, edge<vertex<std::string, int>, double, int>> pretty_graph;
    pretty_graph.insert_vertex();
    pretty_graph.insert_vertex("Hello");

    std::cout << "Вершина 0: " << pretty_graph.get_vertex(0)->get_name() << std::endl;
    std::cout << "Вершина 1: " << pretty_graph.get_vertex(1)->get_name() << std::endl;

    vertex<std::string, int> *ptr_1 = pretty_graph.insert_vertex();
    vertex<std::string, int> *ptr_2 = pretty_graph.insert_vertex("Hello_2");
    pretty_graph.insert_edge(ptr_1, ptr_2);
    pretty_graph.insert_edge(ptr_1, pretty_graph.insert_vertex("Hello_3"));

    std::cout<<pretty_graph<<std::endl;

    pretty_graph.remove_vertex(ptr_2);

    std::cout<<pretty_graph<<std::endl;

    graph<vertex<std::string, int>, edge<vertex<std::string, int>, double, int>> directed_graph(5, DIRECTED, L);
    vertex<std::string, int> *d_vertex_1 = directed_graph.insert_vertex("d_vertex_1");
    vertex<std::string, int> *d_vertex_2 = directed_graph.insert_vertex("d_vertex_2");

    directed_graph.insert_edge(d_vertex_1, d_vertex_2);
    directed_graph.insert_edge(d_vertex_2, d_vertex_1);

    directed_graph.remove_edge(d_vertex_2, d_vertex_1);
    std::cout<<directed_graph<<std::endl;


    for (vertex_iterator<vertex<std::string, int>> it = directed_graph.vertex_begin(); it != directed_graph.vertex_end(); ++it) {
        std::cout<<(*it)->get_index()<<std::endl;
    }

    graph<vertex<std::string, int>, edge<vertex<std::string, int>, double, int>> graph_M(2, NON_DIRECTED, M);
    std::cout<<graph_M<<std::endl;

    vertex<std::string, int> *for_del_d_vertex_1 = graph_M.insert_vertex("d_vertex_2");
    d_vertex_2 = graph_M.insert_vertex("d_vertex_3");

    graph_M.insert_edge(for_del_d_vertex_1, d_vertex_2);
    std::cout<<graph_M<<std::endl;

    vertex<std::string, int> *for_del_d_vertex_4 = graph_M.insert_vertex("d_vertex_4");
    vertex<std::string, int> *for_del_d_vertex_5 = graph_M.insert_vertex("d_vertex_5");

    graph_M.insert_edge(for_del_d_vertex_4, for_del_d_vertex_5);
    std::cout<<graph_M<<std::endl;

    d_vertex_1 = graph_M.insert_vertex("d_vertex_6");
    d_vertex_2 = graph_M.insert_vertex("d_vertex_7");

    graph_M.insert_edge(d_vertex_1, for_del_d_vertex_1);

    std::cout<<graph_M<<std::endl;

    graph_M.remove_edge(d_vertex_1, d_vertex_2);

    graph_M.remove_edge(for_del_d_vertex_4, for_del_d_vertex_5);

    graph_M.remove_vertex(for_del_d_vertex_1);

    std::cout<<graph_M<<std::endl;

    graph<vertex<std::string, int>, edge<vertex<std::string, int>, double, int>> graph_M_2(10, 15, DIRECTED, L);

    vertex<std::string, int> *d_vertex10 = graph_M_2.insert_vertex("d_vertex_10");
    vertex<std::string, int> *d_vertex11 = graph_M_2.insert_vertex("d_vertex_11");

    graph_M_2.insert_edge(d_vertex11, d_vertex10);
    graph_M_2.insert_edge(d_vertex10, d_vertex10);

    std::cout<<graph_M_2<<std::endl;

    graph_M_2.to_matrix_graph();

    std::cout<<graph_M_2<<std::endl;

    graph_M_2.to_list_graph();

    std::cout<<graph_M_2<<std::endl;

    graph_M_2.to_matrix_graph();

    std::cout<<graph_M_2<<std::endl;

    PFS shortest_way(&graph_M_2);

    shortest_way.result();

    PFS shortest_way_2(shortest_way);

    shortest_way.result();

    std::cout<<directed_graph;
    shortest_way_2.set_graph(&directed_graph);

    shortest_way_2.restart();
    shortest_way_2.result();


    //TODO: протестировать диаметр!
    graph<vertex<std::string, int>, edge<vertex<std::string, int>, double, int>> graph_M_3(10, 15, NON_DIRECTED, L);

    allSP all(&graph_M_3);
    std::cout<<graph_M_3;
    std::cout<<"\n---\n"<<all.dist(2, 8);

    std::cout<<"\n\n---> "<<all.radius();

#endif
    return 0;
}
