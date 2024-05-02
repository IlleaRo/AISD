#include <iostream>
#include "menu.h"
#include "prompts.h"

using namespace std;

static example_vertex_iterator menu_vertex_iterator;
static example_edge_iterator menu_edge_iterator;


// 1.
void menu_get_type(example_graph &pretty_graph, bool use_weights) {
    string type_strings[] = {
        "DIRECTED",
        "NON_DIRECTED",
        "UNKNOWN"
    };

    cout << pretty_graph.get_type() << " ";

    switch (pretty_graph.get_type())
    {
        case DIRECTED:
            cout << "(" << type_strings[0] << ")" << endl;
            break;
        case NON_DIRECTED:
            cout << "(" << type_strings[1] << ")" << endl;
            break;
        default:
            cout << "(" << type_strings[2] << ")" << endl;
            break;
    }
}

// 2.
void menu_get_form(example_graph &pretty_graph, bool use_weights) {
    string form_strings[] = {
        "L",
        "M",
        "UNKNOWN"
    };

    cout << pretty_graph.get_form() << " ";

    switch (pretty_graph.get_form())
    {
        case L:
            cout << "(" << form_strings[0] << ")" << endl;
            break;
        case M:
            cout << "(" << form_strings[1] << ")" << endl;
            break;
        default:
            cout << "(" << form_strings[2] << ")" << endl;
            break;
    }
}

// 3.
void menu_get_vertices_count(example_graph &pretty_graph, bool use_weights) {
    cout << pretty_graph.get_num_of_vertex() << endl;
}

// 4.
void menu_get_edges_count(example_graph &pretty_graph, bool use_weights) {
    cout << pretty_graph.get_num_of_edges() << endl;
}

// 5.
void menu_insert_vertex(example_graph &pretty_graph, bool use_weights) {
    string name = get_user_input<string>("Введите имя новой вершины: ");
    example_vertex *vertex = pretty_graph.insert_vertex(name);
    cout << vertex << endl;
}

// 6.
void menu_insert_edge(example_graph &pretty_graph, bool use_weights) {
    int weight;
    example_vertex *vertex1, *vertex2;
    example_edge *edge;
    size_t v1_index, v2_index;

    v1_index = get_user_input<size_t>("Введите индекс первой вершины: ");
    vertex1 = pretty_graph.get_vertex(v1_index);

    if (!vertex1) {
        cout << "Такой вершины нет" << endl;
        return;
    }

    v2_index = get_user_input<size_t>("Введите индекс второй вершины: ");
    vertex2 = pretty_graph.get_vertex(v2_index);

    if (!vertex2) {
        cout << "Такой вершины нет" << endl;
        return;
    }

    if (use_weights) {
        weight = get_user_input<int>("Введите вес ребра: ");
        edge = pretty_graph.insert_edge(vertex1, vertex2, weight);
    }
    else {
        edge = pretty_graph.insert_edge(vertex1, vertex2);
    }

    cout << edge << endl;
}

// 7.
void menu_get_vertex(example_graph &pretty_graph, bool use_weights) {
    example_vertex *vertex;
    size_t index = get_user_input<size_t>("Введите индекс вершины: ");

    vertex = pretty_graph.get_vertex(index);

    cout << "Адрес: " << vertex << endl;
    if (vertex)
    {
        cout << "Данные: " << vertex->get_data() << endl;
        cout << "Имя: " << vertex->get_name() << endl;
    }
}

// 8.
void menu_get_edge(example_graph &pretty_graph, bool use_weights) {
    example_vertex *vertex1, *vertex2;
    example_edge *edge;
    size_t v1_index, v2_index;

    v1_index = get_user_input<size_t>("Введите индекс первой вершины: ");
    vertex1 = pretty_graph.get_vertex(v1_index);

    if (!vertex1) {
        cout << "Такой вершины нет" << endl;
        return;
    }

    v2_index = get_user_input<size_t>("Введите индекс второй вершины: ");
    vertex2 = pretty_graph.get_vertex(v2_index);

    if (!vertex2) {
        cout << "Такой вершины нет" << endl;
        return;
    }

    edge = pretty_graph.get_edge(vertex1, vertex2);

    cout << "Адрес: " << edge << endl;
    if (edge)
    {
        cout << "Данные: " << edge->get_data() << endl;
        if (use_weights)
        {
            cout << "Вес: " << edge->get_weight() << endl;
        }
    }
}

// 9.
void menu_delete_vertex(example_graph &pretty_graph, bool use_weights) {
    example_vertex *vertex;
    size_t index = get_user_input<size_t>("Введите индекс вершины: ");

    cout << "Результат: " << pretty_graph.remove_vertex(index) << endl;
}

// 10.
void menu_print_graph(example_graph &pretty_graph, bool use_weights) {
    cout << pretty_graph << endl;
}

// 11.
void menu_print_vertex(example_graph &pretty_graph, bool use_weights) {
    example_vertex_iterator iter = pretty_graph.vertex_begin();

    while (iter != pretty_graph.vertex_end())
    {
        cout << (*iter)->get_index() << ". Данные: " << (*iter)->get_data() << " Имя: " << (*iter)->get_name() << endl;
        ++iter;
    }
}

// 12.
void menu_clear_graph(example_graph &pretty_graph, bool use_weights) {
    pretty_graph.clear();
}

// 13.
void menu_control_vertex_iterator(example_graph &pretty_graph, bool use_weights) {
    int option = 1;

    if (pretty_graph.get_num_of_vertex() == 0) {
        cout << "В графе нет вершин" << endl;
        return;
    }

    while (true) {
        if (menu_vertex_iterator.is_undefined() || menu_vertex_iterator == pretty_graph.vertex_end()) {
            cout << "Итератор не установлен, установка итератора в начало" << endl;
            menu_vertex_iterator = pretty_graph.vertex_begin();
        }

        cout << "Имя итератора: " << (*menu_vertex_iterator)->get_name() << endl;
        cout << "Значение итератора: " << (*menu_vertex_iterator)->get_data() << endl;

        option = get_user_input<int>(prompt_vertex_iter_menu);
        switch (option)
        {
            case 1:
                // Изменить значение
                (*menu_vertex_iterator)->get_data() = get_user_input<int>("Введите новое значение: ");
                break;
            case 2:
                // Инкрементировать
                ++menu_vertex_iterator;
                break;
            case 3:
                // Установить в начало
                menu_vertex_iterator = pretty_graph.vertex_begin();
                break;
            case 4:
                // Установить в конец
                menu_vertex_iterator = pretty_graph.vertex_end(); // TODO: есть ли в этом смысл?
                break;
            case 0:
                return;
            default:
                continue;
        }
        anykey();
    }
}

// 14. TODO: починить итераторы рёбер
void menu_control_edge_iterator(example_graph &pretty_graph, bool use_weights) {
    int option = 1;

    if (pretty_graph.get_num_of_edges() == 0) {
        cout << "В графе нет рёбер" << endl;
        return;
    }

    while (true) {
        if (menu_edge_iterator.is_undefined() || menu_edge_iterator == pretty_graph.edge_end()) {
            cout << "Итератор не установлен, установка итератора в начало" << endl;
            menu_edge_iterator = pretty_graph.edge_begin();
        }
        cout << "Имя первой вершины: " << (*menu_edge_iterator)->get_v1()->get_name() << endl;
        cout << "Имя второй вершины: " << (*menu_edge_iterator)->get_v2()->get_name() << endl;
        cout << "Значение итератора: " << (*menu_edge_iterator)->get_data() << endl;

        option = get_user_input<int>(prompt_edge_iter_menu);
        switch (option)
        {
            case 1:
                // Инкрементировать
                ++menu_edge_iterator;
                break;
            case 2:
                // Установить в начало
                menu_edge_iterator = pretty_graph.edge_begin();
                break;
            case 3:
                // Установить в конец
                menu_edge_iterator = pretty_graph.edge_end(); // TODO: есть ли в этом смысл?
                break;
            case 0:
                return;
            default:
                continue;
        }
        anykey();
    }
}

// 15.
void menu_tasks(example_graph &pretty_graph, bool use_weights) {
    // TODO: implement menu_tasks
}
