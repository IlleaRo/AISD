#include <iostream>
#include "menu.h"
#include "prompts.h"
#include "../tasks/nonWeighted.h"
#include "../tasks/weighted.h"

using namespace std;

static VertexIterator menu_vertex_iterator;
static Vertex *ev_vertex = nullptr;
static VertexEdgeIterator menu_ev_iterator;
static EdgeIterator menu_edge_iterator;

static weightedTask<Vertex, Edge> *wtask = nullptr;
static nonWeightedTask<Vertex, Edge> *nwtask = nullptr;

// 1.
void menu_get_type(Graph *pretty_graph, bool use_weights)
{
    string type_strings[] = {
        "DIRECTED",
        "NON_DIRECTED",
        "UNKNOWN"
    };

    cout << pretty_graph->getType() << " ";

    switch (pretty_graph->getType())
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
void menu_get_form(Graph *pretty_graph, bool use_weights)
{
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
void menu_get_vertices_count(Graph *pretty_graph, bool use_weights)
{
    cout << pretty_graph->getVertexCount() << endl;
}

// 4.
void menu_get_edges_count(Graph *pretty_graph, bool use_weights)
{
    cout << pretty_graph->getEdgeCount() << endl;
}

// 5.
void menu_get_graph_saturation_factor(Graph *pretty_graph, bool use_weights)
{
    cout << pretty_graph->getCoefficient() << endl;
}

// 6.
void menu_insert_vertex(Graph *pretty_graph, bool use_weights)
{
    string name = getInput<string>("Введите имя новой вершины: ");
    Vertex *vertex = pretty_graph->pushVertex(name);
    cout << vertex << endl;
}

// 7.
void menu_insert_edge(Graph *pretty_graph, bool use_weights)
{
    int weight;
    Vertex *vertex1, *vertex2;
    Edge *edge;
    size_t srcIndex, destIdx;

    srcIndex = getInput<size_t>("Введите индекс первой вершины: ");
    vertex1 = pretty_graph->getVertex(srcIndex);

    if (!vertex1)
    {
        cout << "Такой вершины нет" << endl;
        return;
    }

    destIdx = getInput<size_t>("Введите индекс второй вершины: ");
    vertex2 = pretty_graph->getVertex(destIdx);

    if (!vertex2)
    {
        cout << "Такой вершины нет" << endl;
        return;
    }

    if (use_weights)
    {
        weight = getInput<int>("Введите вес ребра: ");
        edge = pretty_graph->pushEdge(vertex1, vertex2, weight);
    }
    else
    {
        edge = pretty_graph->pushEdge(vertex1, vertex2);
    }

    cout << edge << endl;
}

// 8.
void menu_get_vertex(Graph *pretty_graph, bool use_weights)
{
    Vertex *vertex;
    size_t index = getInput<size_t>("Введите индекс вершины: ");

    vertex = pretty_graph->getVertex(index);

    cout << "Адрес: " << vertex << endl;
    if (vertex)
    {
        cout << "Данные: " << vertex->getData() << endl;
        cout << "Имя: " << vertex->getName() << endl;
    }
}

// 9.
void menu_get_edge(Graph *pretty_graph, bool use_weights)
{
    Vertex *vertex1, *vertex2;
    Edge *edge;
    size_t srcIndex, destIdx;

    srcIndex = getInput<size_t>("Введите индекс первой вершины: ");
    vertex1 = pretty_graph->getVertex(srcIndex);

    if (!vertex1)
    {
        cout << "Такой вершины нет" << endl;
        return;
    }

    destIdx = getInput<size_t>("Введите индекс второй вершины: ");
    vertex2 = pretty_graph->getVertex(destIdx);

    if (!vertex2)
    {
        cout << "Такой вершины нет" << endl;
        return;
    }

    edge = pretty_graph->getEdge(vertex1, vertex2);

    cout << "Адрес: " << edge << endl;
    if (edge)
    {
        cout << "Данные: " << edge->getData() << endl;
        if (use_weights)
        {
            cout << "Вес: " << edge->getWeight() << endl;
        }
    }
}

// 10.
void menu_delete_vertex(Graph *pretty_graph, bool use_weights)
{
    Vertex *vertex;
    size_t index = getInput<size_t>("Введите индекс вершины: ");

    cout << "Результат: " << pretty_graph->popVertex(index) << endl;
}

// 11.
void menu_delete_edge(Graph *pretty_graph, bool use_weights)
{
    Vertex *vertex1, *vertex2;
    Edge *edge;
    size_t srcIndex, destIdx;

    srcIndex = getInput<size_t>("Введите индекс первой вершины: ");
    vertex1 = pretty_graph->getVertex(srcIndex);

    if (!vertex1)
    {
        cout << "Такой вершины нет" << endl;
        return;
    }

    destIdx = getInput<size_t>("Введите индекс второй вершины: ");
    vertex2 = pretty_graph->getVertex(destIdx);

    if (!vertex2)
    {
        cout << "Такой вершины нет" << endl;
        return;
    }

    cout << "Результат: " << pretty_graph->popEdge(vertex1, vertex2) << endl;
}

// 12.
void menu_print_graph(Graph *pretty_graph, bool use_weights)
{
    cout << *pretty_graph << endl;
}

// 13.
void menu_print_vertex(Graph *pretty_graph, bool use_weights)
{
    VertexIterator iter = pretty_graph->vertex_begin();

    while (iter != pretty_graph->vertex_end())
    {
        cout << (*iter)->getIndex() << ". Данные: " << (*iter)->getData() << " Имя: " << (*iter)->getName() << endl;
        ++iter;
    }
}

// 14.
void menu_clear_graph(Graph *&pretty_graph, bool use_weights)
{
    pretty_graph->clear();
    pretty_graph = new Graph(0, pretty_graph->getType(), pretty_graph->get_form());
}

// 15.
void menu_reform_graph(Graph *pretty_graph, bool use_weights)
{
    pretty_graph->get_form() == L ? pretty_graph->convertToM() : pretty_graph->convertToL();
}

// 16.
void menu_control_vertex_iterator(Graph *pretty_graph, bool use_weights)
{
    int option = 1;

    while (true)
    {
        try
        {
            if (menu_vertex_iterator.isUndefined())
            {
                menu_vertex_iterator = pretty_graph->vertex_begin();
            }
            *menu_vertex_iterator;
            cout << "Имя итератора: " << (*menu_vertex_iterator)->getName() << endl;
            cout << "Значение итератора: " << (*menu_vertex_iterator)->getData() << endl;
        }
        catch (std::exception &exception)
        {
            cout << "Ошибка получения данных итератора: " << exception.what() << endl;
        }

        option = getInput<int>(prompt_iter_menu);
        try
        {
            switch (option)
            {
                case 1:
                    // Изменить значение
                    (*menu_vertex_iterator)->setData(getInput<int>("Введите новое значение: "));
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
void menu_control_edge_iterator_for_v(Graph *pretty_graph, bool use_weights)
{
    int option = 1;

    while (true)
    {
        try
        {
            if (ev_vertex == nullptr)
            {
                int vertexIdx = getInput<int>("Введите индекс вершины: ");
                ev_vertex = pretty_graph->getVertex(vertexIdx);
                if (ev_vertex == nullptr)
                {
                    cout << "Такой вершины нет" << endl;
                    return;
                }
                menu_ev_iterator = pretty_graph->edge_v_begin(ev_vertex);
            }
            *menu_ev_iterator;
            cout << "Имя первой вершины: " << (*menu_ev_iterator)->getSrc()->getName() << endl;
            cout << "Имя второй вершины: " << (*menu_ev_iterator)->getDest()->getName() << endl;
            cout << "Значение итератора: " << (*menu_ev_iterator)->getData() << endl;
        }
        catch (std::exception &exception)
        {
            cout << "Ошибка получения данных итератора: " << exception.what() << endl;
        }

        option = getInput<int>(prompt_ev_iter_menu);

        try
        {
            switch (option)
            {
                case 1:
                    // Изменить значение
                    (*menu_ev_iterator)->setData(getInput<int>("Введите новое значение: "));
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
void menu_control_edge_iterator(Graph *pretty_graph, bool use_weights)
{
    int option = 1;

    while (true)
    {
        try
        {
            if (menu_edge_iterator.isUndefined())
            {
                menu_edge_iterator = pretty_graph->edge_begin(); // это происходит только при первом заходе в меню, всё нормально
            }
            *menu_edge_iterator; // проверка, чтобы при ошибке в консоль не начало "Имя первой вершины: " выводиться
            cout << "Имя первой вершины: " << (*menu_edge_iterator)->getSrc()->getName() << endl;
            cout << "Имя второй вершины: " << (*menu_edge_iterator)->getDest()->getName() << endl;
            cout << "Значение итератора: " << (*menu_edge_iterator)->getData() << endl;
        }
        catch (std::exception &exception)
        {
            cout << "Ошибка получения данных итератора: " << exception.what() << endl;
        }

        option = getInput<int>(prompt_iter_menu);

        try
        {
            switch (option)
            {
                case 1:
                    // Изменить значение
                    (*menu_edge_iterator)->setData(getInput<int>("Введите новое значение: "));
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

static void menu_weighted_task(Graph *pretty_graph)
{
    int option;
    string hackyString = "Из ";
    double resultDists;
    std::vector<Vertex *> resultPaths;
    int a;
    int b;

    while (true)
    {
        option = getInput<int>("1. Вывести результат (расстояния)\n"
                                     "2. Вывести результат (пути)\n"
                                     "3. Повторно выполнить задачу\n"
                                     "0. Выйти\n"
                                     "Ввод: ");
        try
        {
            if (!wtask) wtask = new weightedTask<Vertex, Edge>(pretty_graph);
            switch (option)
            {
                case 1:
                    a = getInput<int>("Введите исходную вершину: ");
                    b = getInput<int>("Введите конечную вершину: ");
                    resultDists = wtask->resultDist(a, b);
                    cout << "Результат: " << resultDists << endl;
                    break;
                case 2:
                    a = getInput<int>("Введите исходную вершину: ");
                    b = getInput<int>("Введите конечную вершину: ");
                    resultPaths = wtask->resultPath(a, b);
                    cout << "Результат: ";
                    for (Vertex *v : resultPaths)
                    {
                        cout << v->getIndex() << " ";
                    }
                    cout << endl;
                    break;
                case 3:
                    wtask->restart();
                    break;
                case 0:
                    return;
                default:
                    continue;
            }
        }
        catch (std::exception &exception)
        {
            cout << "Ошибка выполнения операции: " << exception.what() << endl;
        }
        anykey();
    }
}

static void menu_nonweighted_task(Graph *pretty_graph)
{
    int option;
    std::vector<Vertex *> result;
    if (!nwtask) nwtask = new nonWeightedTask<Vertex, Edge>(pretty_graph);
    while (true)
    {
        option = getInput<int>("1. Вывести результат\n"
            "2. Повторно выполнить задачу\n"
            "0. Выйти\n"
            "Ввод: ");
        switch (option)
        {
            case 1:
                result = nwtask->result();
                for (const auto& v: result)
                {
                    cout << v->getIndex() << " ";
                }
                    cout << endl;
                break;
            case 2:
                nwtask->restart();
                break;
            case 0:
                return;
            default:
                continue;
        }
        anykey();
    }
}

// 19.
void menu_tasks(Graph *pretty_graph, bool use_weights)
{
    if (use_weights)
    {
        menu_weighted_task(pretty_graph);
    }
    else
    {
        menu_nonweighted_task(pretty_graph);
    }
}
