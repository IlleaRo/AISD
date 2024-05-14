#include <iostream>
#include <unordered_map>
#include "menu.h"
#include "prompts.h"
#include "../tasks/task_2/PFS.h"
#include "../tasks/task_3/allSP.h"

using namespace std;

static example_vertex_iterator menu_vertex_iterator;
static example_vertex *ev_vertex = nullptr;
static example_ev_iterator menu_ev_iterator;
static example_edge_iterator menu_edge_iterator;

static unordered_map<std::string, example_vertex *> vertexes_map; // We use map for saving vertexes with their names

static example_vertex *get_vertex(example_graph *pretty_graph) {
    int decision;

    do {
        decision = get_user_input<int>("1. Получить по индексу\n2. Получить по имени\n");
    } while(decision != 1 && decision != 2);

    switch (decision) {
        case 1: {
            size_t index = get_user_input<size_t>("Введите индекс вершины: ");

            return pretty_graph->get_vertex(index);
        }
        case 2: {
            string name = get_user_input<string>("Введите имя вершины: ");
            try {
                return vertexes_map.at(name);
            } catch (...) {
                return nullptr;
            }
        }
    }

    return nullptr;
}

// 1.
void menu_get_type(example_graph *pretty_graph, bool use_weights) {
    string type_strings[] = {
        "DIRECTED",
        "NON_DIRECTED",
        "UNKNOWN"
    };

    cout << pretty_graph->get_type() << " ";

    switch (pretty_graph->get_type())
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
void menu_get_form(example_graph *pretty_graph, bool use_weights) {
    string form_strings[] = {
        "L",
        "M",
        "UNKNOWN"
    };

    cout << pretty_graph->get_form() << " ";

    switch (pretty_graph->get_form())
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
void menu_get_vertices_count(example_graph *pretty_graph, bool use_weights) {
    cout << pretty_graph->get_num_of_vertex() << endl;
}

// 4.
void menu_get_edges_count(example_graph *pretty_graph, bool use_weights) {
    cout << pretty_graph->get_num_of_edges() << endl;
}

// 5.
void menu_get_graph_saturation_factor(example_graph *pretty_graph, bool use_weights) {
    cout << pretty_graph->get_koeff() << endl;
}

// 6.
void menu_insert_vertex(example_graph *pretty_graph, bool use_weights) {
    string name;
    example_vertex *vertex = nullptr;

    while (true) {
        try {
            name = get_user_input<string>("Введите имя новой вершины: ");
            vertex = vertexes_map.at(name);
            cout << "Вершина с именем \"" << name << "\" уже существует!\n";
        } catch(...) {
            vertex = pretty_graph->insert_vertex(name);
            vertexes_map[name] = vertex;

            break;
        }
    }
    cout << vertex << endl;
}

// 7.
void menu_insert_edge(example_graph *pretty_graph, bool use_weights) {
    int weight;
    example_vertex *vertex1, *vertex2;
    example_edge *edge;

    cout << "Первая вершина:\n";
    vertex1 = get_vertex(pretty_graph);

    if (!vertex1) {
        cout << "Такой вершины нет" << endl;
        return;
    }

    cout << "Вторая вершина:\n";
    vertex2 = get_vertex(pretty_graph);

    if (!vertex2) {
        cout << "Такой вершины нет" << endl;
        return;
    }

    if (use_weights) {
        weight = get_user_input<int>("Введите вес ребра: ");
        edge = pretty_graph->insert_edge(vertex1, vertex2, weight);
    }
    else {
        edge = pretty_graph->insert_edge(vertex1, vertex2);
    }

    cout << edge << endl;
}

// 8.
void menu_get_vertex(example_graph *pretty_graph, bool use_weights) {
    example_vertex *vertex = get_vertex(pretty_graph);
    if (!vertex) {
        cout << "вершина не найдена!\n";

        return;
    }

    cout << "Адрес: " << vertex <<'\n';
    cout << "Индекс: " << vertex->get_index() <<'\n';
    cout << "1. Данные: " << vertex->get_data() <<'\n';
    cout << "2. Имя: " << vertex->get_name() << endl;

    int decision;
    do {
        decision = get_user_input<int>("Выберите данные для изменения (0 - продолжить): ");

        switch (decision) {
            case 1: {
                int new_data = get_user_input<int>("Новые данные: ");
                vertex->set_data(new_data);
                continue;
            }
            case 2: {
                string new_name = get_user_input<string>("Новое имя: ");
                vertexes_map.erase(vertex->get_name());
                vertex->set_name(new_name);
                vertexes_map[new_name] = vertex;
                continue;
            }
        }
    } while (decision != 0);
}

// 9.
void menu_get_edge(example_graph *pretty_graph, bool use_weights) {
    example_vertex *vertex1, *vertex2;
    example_edge *edge;

    cout << "Первая вершина:\n";
    vertex1 = get_vertex(pretty_graph);
    if (!vertex1) {
        cout << "Такой вершины нет" << endl;
        return;
    }

    cout << "Вторая вершина:\n";
    vertex2 = get_vertex(pretty_graph);

    if (!vertex2) {
        cout << "Такой вершины нет" << endl;
        return;
    }

    edge = pretty_graph->get_edge(vertex1, vertex2);

    if (!edge) {
        cout << 0 << endl;

        return;
    }

    cout << "Адрес: " << edge << endl;
    cout << "1. Данные: " << edge->get_data() << endl;
    if (use_weights) {
        cout << "2. Вес: " << edge->get_weight() << endl;
    }

    int decision;
    do {
        decision = get_user_input<int>("Выберите данные для изменения (0 - продолжить): ");

        switch (decision) {
            case 1: {
                int new_data = get_user_input<int>("Новые данные: ");
                edge->set_data(new_data);
                continue;
            }
            case 2: {
                int new_weight = get_user_input<int>("Новый вес: ");
                edge->set_weight(new_weight);
                continue;
            }
        }
    } while (decision != 0);
}

// 10.
void menu_delete_vertex(example_graph *pretty_graph, bool use_weights) {
    example_vertex *vertex = get_vertex(pretty_graph);
    if (!vertex) {
        return;
    }

    vertexes_map.erase(vertex->get_name());
    cout << "Результат: " << pretty_graph->remove_vertex(vertex) << endl;
}

// 11.
void menu_delete_edge(example_graph *pretty_graph, bool use_weights) {
    example_vertex *vertex1, *vertex2;
    example_edge *edge;

    cout << "Первая вершина:\n";
    vertex1 = get_vertex(pretty_graph);

    if (!vertex1) {
        cout << "Такой вершины нет" << endl;
        return;
    }

    cout << "Вторая вершина:\n";
    vertex2 = get_vertex(pretty_graph);

    if (!vertex2) {
        cout << "Такой вершины нет" << endl;
        return;
    }

    cout << "Результат: " << pretty_graph->remove_edge(vertex1, vertex2) << endl;
}

// 12.
void menu_print_graph(example_graph *pretty_graph, bool use_weights) {
    cout << *pretty_graph << endl;
}

// 13.
void menu_print_vertex(example_graph *pretty_graph, bool use_weights) {
    example_vertex_iterator iter = pretty_graph->vertex_begin();

    while (iter != pretty_graph->vertex_end())
    {
        cout << (*iter)->get_index() << ". Данные: " << (*iter)->get_data() << " Имя: " << (*iter)->get_name() << endl;
        ++iter;
    }
}

// 14.
void menu_clear_graph(example_graph *&pretty_graph, bool use_weights) {
    pretty_graph->clear();
    pretty_graph = new example_graph(0, pretty_graph->get_type(), pretty_graph->get_form());
}

// 15.
void menu_reform_graph(example_graph *pretty_graph, bool use_weights) {
    pretty_graph->get_form() == L ? pretty_graph->to_matrix_graph() : pretty_graph->to_list_graph();
}

// 16.
void menu_control_vertex_iterator(example_graph *pretty_graph, bool use_weights) {
    int option = 1;
/*
    if (pretty_graph->get_num_of_vertex() == 0) {
        cout << "В графе нет вершин" << endl;
        return;
    }
*/
    while (true) {
        if (menu_vertex_iterator.is_undefined()) {
            menu_vertex_iterator = pretty_graph->vertex_begin(); // это происходит только при первом заходе в меню, всё нормально
        }

        try
        {
            *menu_vertex_iterator; // проверка, чтобы при ошибке в консоль не начало "Имя итератора: " выводиться
            cout << "Имя итератора: " << (*menu_vertex_iterator)->get_name() << endl;
            cout << "Значение итератора: " << (*menu_vertex_iterator)->get_data() << endl;
        }
        catch (std::exception &exception)
        {
            cout << "Ошибка получения данных итератора: " << exception.what() << endl;
        }

        option = get_user_input<int>(prompt_iter_menu);
        try
        {
            switch (option)
            {
                case 1:
                    // Изменить значение
                    (*menu_vertex_iterator)->set_data(get_user_input<int>("Введите новое значение: "));
                    break;
                case 2:
                    // Инкрементировать
                    ++menu_vertex_iterator;
                    break;
                case 3:
                    // Установить в начало
                    menu_vertex_iterator = pretty_graph->vertex_begin();
                    break;
                case 4:
                    // Установить в конец
                    menu_vertex_iterator = pretty_graph->vertex_end();
                    break;
                case 0:
                    return;
                default:
                    continue;
            }
            anykey();
        }
        catch (std::exception &exception)
        {
            cout << "Ошибка выполнения операции: " << exception.what() << endl;
        }
    }
}

// 17.
void menu_control_edge_iterator_for_v(example_graph *pretty_graph, bool use_weights)
{
    int option = 1;
/*
    if (pretty_graph->get_num_of_vertex() == 0) {
        cout << "В графе нет вершин" << endl;
        return;
    }
    */
/*
    if (pretty_graph->get_num_of_edges() == 0) {
        cout << "В графе нет граней" << endl;
        return;
    }
*/
    while (true) {
        if (ev_vertex == nullptr) {
            int vertex_index = get_user_input<int>("Введите индекс вершины: ");
            ev_vertex = pretty_graph->get_vertex(vertex_index);
            if (ev_vertex == nullptr)
            {
                cout << "Такой вершины нет" << endl;
                return;
            }
            menu_ev_iterator = pretty_graph->edge_v_begin(ev_vertex);
        }

        try
        {
            *menu_ev_iterator;
            cout << "Имя первой вершины: " << (*menu_ev_iterator)->get_v1()->get_name() << endl;
            cout << "Имя второй вершины: " << (*menu_ev_iterator)->get_v2()->get_name() << endl;
            cout << "Значение итератора: " << (*menu_ev_iterator)->get_data() << endl;
        }
        catch (std::exception &exception)
        {
            cout << "Ошибка получения данных итератора: " << exception.what() << endl;
        }

        option = get_user_input<int>(prompt_ev_iter_menu);

        try
        {
            switch (option)
            {
                case 1:
                    // Изменить значение
                    (*menu_ev_iterator)->set_data(get_user_input<int>("Введите новое значение: "));
                break;
                case 2:
                    // Инкрементировать
                    ++menu_ev_iterator;
                break;
                case 3:
                    // Установить в начало
                    menu_ev_iterator = pretty_graph->edge_v_begin(ev_vertex);
                break;
                case 4:
                    // Установить в конец
                    menu_ev_iterator = pretty_graph->edge_v_end(ev_vertex);
                break;
                case 5:
                    // Изменить вершину
                    ev_vertex = nullptr;
                    continue;
                case 0:
                    return;
                default:
                    continue;
            }
            anykey();
        }
        catch (std::exception &exception)
        {
            cout << "Ошибка выполнения операции: " << exception.what() << endl;
        }
    }
}

// 18.
void menu_control_edge_iterator(example_graph *pretty_graph, bool use_weights) {
    int option = 1;
/*
    if (pretty_graph->get_num_of_edges() == 0) {
        cout << "В графе нет рёбер" << endl;
        return;
    }
*/
    while (true) {
        if (menu_edge_iterator.is_undefined()) {
            menu_edge_iterator = pretty_graph->edge_begin(); // это происходит только при первом заходе в меню, всё нормально
        }

        try
        {
            *menu_edge_iterator; // проверка, чтобы при ошибке в консоль не начало "Имя первой вершины: " выводиться
            cout << "Имя первой вершины: " << (*menu_edge_iterator)->get_v1()->get_name() << endl;
            cout << "Имя второй вершины: " << (*menu_edge_iterator)->get_v2()->get_name() << endl;
            cout << "Значение итератора: " << (*menu_edge_iterator)->get_data() << endl;
        }
        catch (std::exception &exception)
        {
            cout << "Ошибка получения данных итератора: " << exception.what() << endl;
        }

        option = get_user_input<int>(prompt_iter_menu);

        try
        {
            switch (option)
            {
                case 1:
                    // Изменить значение
                    (*menu_edge_iterator)->set_data(get_user_input<int>("Введите новое значение: "));
                    break;
                case 2:
                    // Инкрементировать
                    ++menu_edge_iterator;
                    break;
                case 3:
                    // Установить в начало
                    menu_edge_iterator = pretty_graph->edge_begin();
                    break;
                case 4:
                    // Установить в конец
                    menu_edge_iterator = pretty_graph->edge_end();
                    break;
                case 0:
                    return;
                default:
                    continue;
            }
            anykey();
        }
        catch (std::exception &exception)
        {
            cout << "Ошибка выполнения операции: " << exception.what() << endl;
        }

    }
}

static void menu_weighted_task(example_graph *pretty_graph) {
    allSP<example_vertex, example_edge> spt(pretty_graph);

    int decision;

    while (true) {
        decision = get_user_input<int>(task_3_menu);
        switch (decision)
        {
            case 1:
                spt.restart();
                break;
            case 2:
                cout<<"Radius: "<<spt.get_radius()<<'\n';
                break;
            case 3:
                cout<<"Radius path: ";
                spt.print_path();
                cout<<'\n';
                break;
            case 0:
                return;
            default:
                continue;
        }
    }
}

static void menu_nonweighted_task(example_graph *pretty_graph) {
    PFS<example_vertex, example_edge> pfs(pretty_graph);

    int decision;

    while (true) {
        cout<<'\n';
        decision = get_user_input<int>(task_2_menu);
        switch (decision)
        {
            case 1:
                pfs.restart();
                break;
            case 2: {
                vector<vector<vector<unsigned long>>> tmp = pfs.result();
                cout<<"Получен трехмерный вектор"<<endl;
                break;
            }
            case 3:
                pfs.print_result();
                break;
            case 4: {
                unsigned long from, to;
                from = get_user_input<unsigned long>("Стартовая вершина: ");
                to = get_user_input<unsigned long>("Конечная вершина: ");

                vector<unsigned long> path = pfs.result(from, to);
                cout<<"Получен вектор:\n";
                for (unsigned long index : path) {
                    cout<<index<<" ";
                }
                cout<<endl;
                break;
            }
            case 0:
                return;
            default:
                continue;
        }
    }
}

// 19.
void menu_tasks(example_graph *pretty_graph, bool use_weights) {
    start:
    int option = get_user_input<int>(task_select);

    switch (option) {
        case 1:
            menu_nonweighted_task(pretty_graph);
            break;
        case 2:
            menu_weighted_task(pretty_graph);
            break;
        case 0:
            return;
        default:
            goto start;
    }
}
