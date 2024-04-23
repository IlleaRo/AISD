#include <iostream>
#include "graphs/graph.h"

int main() {
    graph<vertex<std::string, int>, edge<vertex<std::string, int>, int, int>> pretty_graph;
    pretty_graph.insert_vertex();
    pretty_graph.insert_vertex("Hello");

    vertex<std::string, int> *ptr_1 = pretty_graph.insert_vertex();
    vertex<std::string, int> *ptr_2 = pretty_graph.insert_vertex("Hello_2");
    pretty_graph.insert_edge(ptr_1, ptr_2);
    pretty_graph.insert_edge(ptr_1, pretty_graph.insert_vertex("Hello_3"));

    std::cout<<pretty_graph<<std::endl;

    pretty_graph.remove_vertex(ptr_2);

    std::cout<<pretty_graph<<std::endl;
    return 0;
}