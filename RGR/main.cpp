#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <cstring>
#include "ui/test.h"
#include "ui/prompts.h"
#include "ui/menu.h"
#include "graphs/graph.h"

#pragma execution_character_set( "utf-8" )
#define WIN_UTF_ID 65001
#define GRAPH_TYPE L // TODO: надо бы в рантайме разрешить указывать тип

typedef graph<vertex<std::string, int>, edge<vertex<std::string, int>, double, int>> example_graph;

int main(int argc, char *argv[]) {
    int input;
    bool use_weights;
    bool correct_input = false;
    example_graph pretty_graph;

#ifdef _WIN32
    SetConsoleOutputCP( WIN_UTF_ID);
#endif

    if (argc > 1 && (strcmp(argv[1], "test") == 0)) {
        return run_test();
    }

    while (!correct_input) {
        input = get_user_input<int>(prompt_type);
        switch (input) {
            case 1:
                // Неориентированный, невзвешенный
                pretty_graph = *new example_graph(0, NON_DIRECTED, GRAPH_TYPE);
                use_weights = false;
                break;
            case 2:
                // Ориентированный, невзвешенный
                pretty_graph = *new example_graph(0, DIRECTED, GRAPH_TYPE);
                use_weights = false;
                break;
            case 3:
                // Неориентированный, взвешенный
                pretty_graph = *new example_graph(0, NON_DIRECTED, GRAPH_TYPE);
                use_weights = true;
                break;
            case 4:
                // Ориентированный, взвешенный
                pretty_graph = *new example_graph(0, DIRECTED, GRAPH_TYPE);
                use_weights = true;
                break;

            default:
                continue;
        }
        correct_input = true;
    }

    while (true) {
        input = get_user_input<int>(prompt_main_menu);
        switch (input) {
            case 1:
                // Получить тип
                menu_get_type(pretty_graph, use_weights);
                break;
            case 2:
                // Получить форму
                menu_get_form(pretty_graph, use_weights);
                break;
            case 3:
                // Получить количество вершин
                menu_get_vertices_count(pretty_graph, use_weights);
                break;
            case 4:
                // Получить количество рёбер
                menu_get_edges_count(pretty_graph, use_weights);
                break;
            case 5:
                // Вставить вершину
                menu_insert_vertex(pretty_graph, use_weights);
                break;
            case 6:
                // Вставить ребро
                menu_insert_edge(pretty_graph, use_weights);
                break;
            case 7:
                // Получить вершину
                menu_get_vertex(pretty_graph, use_weights);
                break;
            case 8:
                // Получить ребро
                menu_get_edge(pretty_graph, use_weights);
                break;
            case 9:
                // Удалить вершину
                menu_delete_vertex(pretty_graph, use_weights);
                break;
            case 10:
                // Вывести граф
                menu_print_graph(pretty_graph, use_weights);
                break;
            case 11:
                // Очистить граф
                menu_clear_graph(pretty_graph, use_weights);
                break;
            case 12:
                // Управление итератором вершин
                menu_control_vertex_iterator(pretty_graph, use_weights);
                break;
            case 13:
                // Управление итератором рёбер
                menu_control_edge_iterator(pretty_graph, use_weights);
                break;
            case 14:
                // Меню с заданиями, согласно варианту
                menu_tasks(pretty_graph, use_weights);
                break;
            case 0:
                return 0;
            default:
                continue;
        }
        anykey();
    }
}