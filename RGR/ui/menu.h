#ifndef RGR_MENU_H
#define RGR_MENU_H
#include "../graphs/graph.h"

// 1.
template <class VERTEX_T, class EDGE_T>
void menu_get_type(graph<VERTEX_T, EDGE_T> &pretty_graph, bool use_weights);

// 2.
template <class VERTEX_T, class EDGE_T>
void menu_get_form(graph<VERTEX_T, EDGE_T> &pretty_graph, bool use_weights);

// 3.
template <class VERTEX_T, class EDGE_T>
void menu_get_vertices_count(graph<VERTEX_T, EDGE_T> &pretty_graph, bool use_weights);

// 4.
template <class VERTEX_T, class EDGE_T>
void menu_get_edges_count(graph<VERTEX_T, EDGE_T> &pretty_graph, bool use_weights);

// 5.
template <class VERTEX_T, class EDGE_T>
void menu_insert_vertex(graph<VERTEX_T, EDGE_T> &pretty_graph, bool use_weights);

// 6.
template <class VERTEX_T, class EDGE_T>
void menu_insert_edge(graph<VERTEX_T, EDGE_T> &pretty_graph, bool use_weights);

// 7.
template <class VERTEX_T, class EDGE_T>
void menu_get_vertex(graph<VERTEX_T, EDGE_T> &pretty_graph, bool use_weights);

// 8.
template <class VERTEX_T, class EDGE_T>
void menu_get_edge(graph<VERTEX_T, EDGE_T> &pretty_graph, bool use_weights);

// 9.
template <class VERTEX_T, class EDGE_T>
void menu_delete_vertex(graph<VERTEX_T, EDGE_T> &pretty_graph, bool use_weights);

// 10.
template <class VERTEX_T, class EDGE_T>
void menu_print_graph(graph<VERTEX_T, EDGE_T> &pretty_graph, bool use_weights);

// 11.
template <class VERTEX_T, class EDGE_T>
void menu_clear_graph(graph<VERTEX_T, EDGE_T> &pretty_graph, bool use_weights);

// 12.
template <class VERTEX_T, class EDGE_T>
void menu_control_iterator(graph<VERTEX_T, EDGE_T> &pretty_graph, bool use_weights);

// 13.
template <class VERTEX_T, class EDGE_T>
void menu_tasks(graph<VERTEX_T, EDGE_T> &pretty_graph, bool use_weights);

#endif //RGR_MENU_H
