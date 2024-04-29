#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <cstring>
#include "ui/test.h"
#include "ui/prompts.h"
#include "graphs/graph.h"

#pragma execution_character_set( "utf-8" )
#define WIN_UTF_ID 65001

int main(int argc, char *argv[]) {
    int input;
    bool correct_input = false;

#ifdef _WIN32
    SetConsoleOutputCP( WIN_UTF_ID);
#endif

    if (argc > 1 && (strcmp(argv[1], "test") == 0)) {
        return run_test();
    }

    while (!correct_input)
    {
        input = get_user_input(prompt_type);
        switch (input)
        {
            case 1:
                // Неориентированный, невзвешенный
                break;
            case 2:
                // Ориентированный, невзвешенный
                break;
            case 3:
                // Неориентированный, взвешенный
                break;
            case 4:
                // Ориентированный, взвешенный
                break;

            default:
                continue;
        }
        correct_input = true;
    }

    correct_input = false;
    while (!correct_input)
    {
        input = get_user_input(prompt_main_menu);
        switch (input)
        {
            case 1:
                // Получить тип
                break;
            case 2:
                // Получить форму
                break;
            case 3:
                // Получить количество вершин
                break;
            case 4:
                // Получить количество рёбер
                break;
            case 5:
                // Вставить вершину
                break;
            case 6:
                // Вставить ребро
                break;
            case 7:
                // Получить вершину
                break;
            case 8:
                // Получить ребро
                break;
            case 9:
                // Удалить вершину
                break;
            case 10:
                // Вывести граф
                break;
            case 11:
                // Очистить граф
                break;
            case 12:
                // Управление итератором
                break;
            case 13:
                // Меню с заданиями, согласно варианту
                break;
            case 0:
                return 0;
            default:
                continue;
        }
    }
}