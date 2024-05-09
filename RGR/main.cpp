#include <cstring>

#include "ui/prompts.h"
#include "ui/menu.h"
#include "ui/test.h"
#include "graph/graph.h"

#define TYPE L

int main(int argc, char *argv[])
{
    int input;
    bool use_weights = true;
    bool correct_input = false;
    Graph *pretty_graph;

    if (argc > 1 && (strcmp(argv[1], "test") == 0)) {
        return run_test();
    }

    while (!correct_input)
    {
        input = getInput<int>("Выберите тип графа:\n"
                              "\t1. Неориентированный, невзвешенный\n"
                              "\t2. Ориентированный, невзвешенный\n"
                              "\t3. Неориентированный, взвешенный\n"
                              "\t4. Ориентированный, взвешенный\n"
                            "Ввод: ");
        switch (input)
        {
            case 1:
                // Неориентированный, невзвешенный
                pretty_graph = new Graph(0, NON_DIRECTED, TYPE);
                use_weights = false;
                break;
            case 2:
                // Ориентированный, невзвешенный
                pretty_graph = new Graph(0, DIRECTED, TYPE);
                use_weights = false;
                break;
            case 3:
                // Неориентированный, взвешенный
                pretty_graph = new Graph(0, NON_DIRECTED, TYPE);
                use_weights = true;
                break;
            case 4:
                // Ориентированный, взвешенный
                pretty_graph = new Graph(0, DIRECTED, TYPE);
                use_weights = true;
                break;

            default:
                continue;
        }
        correct_input = true;
    }

    pretty_graph->pushEdge(
        pretty_graph->pushVertex("A1"),
        pretty_graph->pushVertex("A2"),
        use_weights ? 10 : 0
    );

    pretty_graph->pushEdge(
        pretty_graph->pushVertex("B1"),
        pretty_graph->pushVertex("B2"),
        use_weights ? 20 : 0
    );

    while (true)
    {
        input = getInput<int>(prompt_main_menu);
        switch (input)
        {
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
