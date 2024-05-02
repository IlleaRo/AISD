#ifndef RGR_MENU_H
#define RGR_MENU_H
#include "../graphs/graph.h"

typedef vertex<std::string, int> example_vertex;
typedef edge<vertex<std::string, int>, int, int> example_edge;
typedef graph<example_vertex, example_edge> example_graph;
typedef vertex_iterator<example_vertex> example_vertex_iterator;
typedef edge_iterator<example_vertex, example_edge> example_edge_iterator;

// 1.
void menu_get_type(example_graph &pretty_graph, bool use_weights);

// 2.
void menu_get_form(example_graph &pretty_graph, bool use_weights);

// 3.
void menu_get_vertices_count(example_graph &pretty_graph, bool use_weights);

// 4.
void menu_get_edges_count(example_graph &pretty_graph, bool use_weights);

// 5.
void menu_insert_vertex(example_graph &pretty_graph, bool use_weights);

// 6.
void menu_insert_edge(example_graph &pretty_graph, bool use_weights);

// 7.
void menu_get_vertex(example_graph &pretty_graph, bool use_weights);

// 8.
void menu_get_edge(example_graph &pretty_graph, bool use_weights);

// 9.
void menu_delete_vertex(example_graph &pretty_graph, bool use_weights);

// 10.
void menu_delete_edge(example_graph &pretty_graph, bool use_weights);

// 11.
void menu_print_graph(example_graph &pretty_graph, bool use_weights);

// 12.
void menu_print_vertex(example_graph &pretty_graph, bool use_weights);

// 13.
void menu_clear_graph(example_graph &pretty_graph, bool use_weights);

// 14.
void menu_control_vertex_iterator(example_graph &pretty_graph, bool use_weights);

// 15.
void menu_control_edge_iterator(example_graph &pretty_graph, bool use_weights);

// 16.
void menu_tasks(example_graph &pretty_graph, bool use_weights);

#endif //RGR_MENU_H
