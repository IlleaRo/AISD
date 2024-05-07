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

int main(int argc, char *argv[]) {
    int input;
    bool use_weights = true;
    bool correct_input = false;
    example_graph *pretty_graph;

#ifdef _WIN32
    SetConsoleOutputCP( WIN_UTF_ID);
#endif

    if (argc > 1 && (strcmp(argv[1], "test") == 0)) {
        return run_test();
    }

    if (argc > 1 && strcmp(argv[1], "rand") == 0) {
        // Случайный граф
        unsigned long num_of_vertexes = get_user_input<unsigned long>("Введите количество вершин: ");
        unsigned long num_of_edges = get_user_input<unsigned long>("Введите количество рёбер: ");

        int type;
        do {
            type = get_user_input<int>("Введите тип графа (0 - неориентированный, 1 - ориентированный): ");
        } while (type != 0 && type != 1);

        int form;
        do {
            form = get_user_input<int>("Введите форму графа (0 - L-граф, 1 - M-граф) ");
        } while (form != 0 && form != 1);

        pretty_graph = new example_graph(num_of_vertexes, num_of_edges,
                                          type ? DIRECTED : NON_DIRECTED, form ? M : L);
    } else {
        while (!correct_input) {
            input = get_user_input<int>(prompt_type);
            switch (input) {
                case 1:
                    // Неориентированный, невзвешенный
                    pretty_graph = new example_graph(0, NON_DIRECTED, GRAPH_TYPE);
                    use_weights = false;
                    break;
                case 2:
                    // Ориентированный, невзвешенный
                    pretty_graph = new example_graph(0, DIRECTED, GRAPH_TYPE);
                    use_weights = false;
                    break;
                case 3:
                    // Неориентированный, взвешенный
                    pretty_graph = new example_graph(0, NON_DIRECTED, GRAPH_TYPE);
                    use_weights = true;
                    break;
                case 4:
                    // Ориентированный, взвешенный
                    pretty_graph = new example_graph(0, DIRECTED, GRAPH_TYPE);
                    use_weights = true;
                    break;

                default:
                    continue;
            }
            correct_input = true;
        }

        pretty_graph->insert_edge(
                pretty_graph->insert_vertex("A1"),
                pretty_graph->insert_vertex("A2"),
                use_weights ? 10 : 0
        );

        pretty_graph->insert_edge(
                pretty_graph->insert_vertex("B1"),
                pretty_graph->insert_vertex("B2"),
                use_weights ? 20 : 0
        );
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
                // Получить коэффициент насыщенности графа
                menu_get_graph_saturation_factor(pretty_graph, use_weights);
                break;
            case 6:
                // Вставить вершину
                menu_insert_vertex(pretty_graph, use_weights);
                break;
            case 7:
                // Вставить ребро
                menu_insert_edge(pretty_graph, use_weights);
                break;
            case 8:
                // Получить вершину
                menu_get_vertex(pretty_graph, use_weights);
                break;
            case 9:
                // Получить ребро
                menu_get_edge(pretty_graph, use_weights);
                break;
            case 10:
                // Удалить вершину
                menu_delete_vertex(pretty_graph, use_weights);
                break;
            case 11:
                // Удалить ребро
                menu_delete_edge(pretty_graph, use_weights);
                break;
            case 12:
                // Вывести граф
                menu_print_graph(pretty_graph, use_weights);
                break;
            case 13:
                // Вывести список вершин
                menu_print_vertex(pretty_graph, use_weights);
                break;
            case 14:
                // Очистить граф
                menu_clear_graph(pretty_graph, use_weights);
                break;
            case 15:
                // Преобразовать граф из L в M и наоборот
                menu_reform_graph(pretty_graph, use_weights);
                break;
            case 16:
                // Управление итератором вершин
                menu_control_vertex_iterator(pretty_graph, use_weights);
                break;
            case 17:
                // Управление итератором исходящих рёбер вершины
                menu_control_edge_iterator_for_v(pretty_graph, use_weights);
                break;
            case 18:
                // Управление итератором рёбер
                menu_control_edge_iterator(pretty_graph, use_weights);
                break;
            case 19:
                // Меню с заданиями, согласно варианту
                menu_tasks(pretty_graph, use_weights);
                break;
            case 0:
                delete pretty_graph;
                return 0;
            default:
                continue;
        }
        anykey();
    }
}