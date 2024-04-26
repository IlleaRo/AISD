#include <iostream>
#include "graphs/graph.h"

int main() {
    graph<vertex<std::string, int>, edge<vertex<std::string, int>, double, int>> pretty_graph;
    pretty_graph.insert_vertex();
    pretty_graph.insert_vertex("Hello");

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


    for (vertex_iterator<vertex<std::string, int>> it = directed_graph.begin(); it != directed_graph.end(); ++it) {
        std::cout<<(*it).get_index()<<std::endl;
    }

    return 0;
}