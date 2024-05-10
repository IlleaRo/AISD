#ifndef RGR_MENU_H
#define RGR_MENU_H
#include "../graph/graph.h"

// 1.
void menu_get_type(Graph *pretty_graph, bool use_weights);

// 2.
void menu_get_form(Graph *pretty_graph, bool use_weights);

// 3.
void menu_get_vertices_count(Graph *pretty_graph, bool use_weights);

// 4.
void menu_get_edges_count(Graph *pretty_graph, bool use_weights);

// 5.
void menu_get_graph_saturation_factor(Graph *pretty_graph, bool use_weights);

// 6.
void menu_insert_vertex(Graph *pretty_graph, bool use_weights);

// 7.
void menu_insert_edge(Graph *pretty_graph, bool use_weights);

// 8.
void menu_get_vertex(Graph *pretty_graph, bool use_weights);

// 9.
void menu_get_edge(Graph *pretty_graph, bool use_weights);

// 10.
void menu_delete_vertex(Graph *pretty_graph, bool use_weights);

// 11.
void menu_delete_edge(Graph *pretty_graph, bool use_weights);

// 12.
void menu_print_graph(Graph *pretty_graph, bool use_weights);

// 13.
void menu_print_vertex(Graph *pretty_graph, bool use_weights);

// 14.
void menu_clear_graph(Graph *&pretty_graph, bool use_weights);

// 15.
void menu_reform_graph(Graph *pretty_graph, bool use_weights);

// 16.
void menu_control_vertex_iterator(Graph *pretty_graph, bool use_weights);

// 17.
void menu_control_edge_iterator_for_v(Graph *pretty_graph, bool use_weights);

// 18.
void menu_control_edge_iterator(Graph *pretty_graph, bool use_weights);

// 19.
void menu_tasks(Graph *pretty_graph, bool use_weights);

#endif //RGR_MENU_H
