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
    example_vertex *vertex1, *vertex2;
    string name = get_user_input<string>("Введите имя первой вершины: ");

    // TODO: сделать API для получения вершины по имени (привет хэш-таблицам)
}

// 7.
void menu_get_vertex(example_graph &pretty_graph, bool use_weights) {
    // TODO: то же, что и сверху
}

// 8.
void menu_get_edge(example_graph &pretty_graph, bool use_weights) {
    // TODO: почему публично торчат методы, которые требуют вершины, но при этом нет публичных методов для получения
    //  вершин? тупое задание
}

// 9.
void menu_delete_vertex(example_graph &pretty_graph, bool use_weights) {
    // TODO: парни, вы издеваетесь?
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
    // TODO: API для очистки графа? в задании его нет, но в меню вроде полезная функция... может сделать итератором?
}

// 13. TODO: проверить работоспособность
void menu_control_vertex_iterator(example_graph &pretty_graph, bool use_weights) {
    int option = 1;

    if (pretty_graph.get_num_of_vertex() == 0) {
        cout << "В графе нет вершин" << endl;
        return;
    }

    if (menu_vertex_iterator.is_undefined()) {
        menu_vertex_iterator = pretty_graph.vertex_begin();
    }

    while (true) {
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
                menu_vertex_iterator = pretty_graph.vertex_end();
                break;
            case 0:
                return;
            default:
                continue;
        }
        anykey();
    }
}

// 14. TODO: проверить работоспособность
void menu_control_edge_iterator(example_graph &pretty_graph, bool use_weights) {
    int option = 1;

    if (pretty_graph.get_num_of_edges() == 0) {
        cout << "В графе нет рёбер" << endl;
        return;
    }

    if (menu_edge_iterator.is_undefined()) {
        menu_edge_iterator = pretty_graph.edge_begin();
    }

    while (true) {
        cout << "Имя первой вершины: " << (*menu_edge_iterator)->get_v1()->get_name() << endl;
        cout << "Имя второй вершины: " << (*menu_edge_iterator)->get_v2()->get_name() << endl;
        cout << "Значение итератора: " << (int) (*menu_edge_iterator)->get_data() << endl;

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
                menu_edge_iterator = pretty_graph.edge_end();
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
