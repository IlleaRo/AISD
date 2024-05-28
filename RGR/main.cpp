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

    std::vector<Vertex *> test_vector;
    //for (int i = 0; i <= 4; i++)
    //{
    //    test_vector.push_back(pretty_graph->pushVertex());
    //}
    //pretty_graph->pushEdge(test_vector[0], test_vector[1], 1);
    //pretty_graph->pushEdge(test_vector[1], test_vector[2], 2);
    //pretty_graph->pushEdge(test_vector[2], test_vector[3], 2);
    //pretty_graph->pushEdge(test_vector[2], test_vector[4], 4);
    //pretty_graph->pushEdge(test_vector[3], test_vector[2], 3);
    //pretty_graph->pushEdge(test_vector[4], test_vector[3], 5);

    //for (int i = 0; i <= 7; i++)
    //{
    //    test_vector.push_back(pretty_graph->pushVertex());
    //}
    //pretty_graph->pushEdge(test_vector[0], test_vector[1]);
    //pretty_graph->pushEdge(test_vector[1], test_vector[2]);
    //pretty_graph->pushEdge(test_vector[2], test_vector[3]);
    //pretty_graph->pushEdge(test_vector[3], test_vector[0]);
    //pretty_graph->pushEdge(test_vector[0], test_vector[4]);
    //pretty_graph->pushEdge(test_vector[5], test_vector[1]);
    //pretty_graph->pushEdge(test_vector[2], test_vector[7]);
    //pretty_graph->pushEdge(test_vector[6], test_vector[3]);
    //pretty_graph->pushEdge(test_vector[4], test_vector[6]);
    //pretty_graph->pushEdge(test_vector[5], test_vector[4]);
    //pretty_graph->pushEdge(test_vector[7], test_vector[5]);
    //pretty_graph->pushEdge(test_vector[6], test_vector[7]);
    //pretty_graph->pushEdge(test_vector[7], test_vector[4]);

    for (int i = 0; i <= 4; i++)
    {
        char test[512];
        sprintf(reinterpret_cast<char *>(test), "%d", i);
        test_vector.push_back(pretty_graph->pushVertex(test));
    }
    pretty_graph->pushEdge(test_vector[0], test_vector[1], 3);
    pretty_graph->pushEdge(test_vector[0], test_vector[2], 8);
    pretty_graph->pushEdge(test_vector[0], test_vector[4], 4);
    pretty_graph->pushEdge(test_vector[1], test_vector[3], 20);
    pretty_graph->pushEdge(test_vector[1], test_vector[4], 7);
    pretty_graph->pushEdge(test_vector[2], test_vector[1], 4);
    pretty_graph->pushEdge(test_vector[3], test_vector[2], 5);
    pretty_graph->pushEdge(test_vector[4], test_vector[3], 6);


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
