#include "list.h"
#include <iostream>

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

#define TYPE int

using namespace std;


// ANSI Escape-последовательности для цветов
const string ANSI_COLOR_RED = "\033[31m";
const string ANSI_COLOR_YELLOW = "\033[33m";
const string ANSI_COLOR_RESET = "\033[0m";

int tests()
{
    list<int> test_list;
    int function_counter = 0;
    /*
     * if (test_function() != success)
     * {
     *     return function_counter;
     * }
     * function_counter++;
     */
    test_list.push(2);
    cerr << "Pushed 2 to the end of the list" << endl;
    test_list.push(1, 0);
    cerr << "Pushed 1 to pos 0 of the list" << endl;
    test_list.push(3);
    cerr << "Pushed 3 to the end of the list" << endl;
    cerr << "Current list: " << test_list << endl;
    cerr << "Removed " << test_list.remove_item(2) << " from list in " << test_list.get_traverse_count() << " its" << endl;
    cerr << "Removed " << test_list.remove_item(1) << " from list in " << test_list.get_traverse_count() << " its" << endl;
    cerr << "Removed " << test_list.remove_item(0) << " from list in " << test_list.get_traverse_count() << " its" << endl;
    return 0;
}

int main()
{
    list<TYPE> list;
    TYPE value;
    unsigned int idx;
    short decision;

    while (true) {
        cout<<ANSI_COLOR_RESET<<"\n\n"
                                "0.  Запрос числа элементов списка, просмотренных предыдущей операцией,\n"
                                "1.  вывод списка,\n"
                                "2.  получить размер списка,\n"
                                "3.  вставка элемента,\n"
                                "4.  удаление элемента,\n"
                                "5.  опрос наличия элемента,\n"
                                "6.  чтение значения с заданным номером в списке,\n"
                                "7.  получение позиции в списке для заданного значения,\n"
                                "8.  изменение значения с заданным номером в списке,\n"
                                "9.  проверка на пустоту,\n"
                                "10. очистка списка,\n"
                                "11. выход.\n"
                                "---> "<<ends;
        cin>>decision;
        switch (decision) {
            case 0:
                system(CLEAR);
                cout<<"Просмотрено "<<list.get_traverse_count()<<" элемента(ов)"<<endl;
                break;
            case 1:
                system(CLEAR);
                cout<<list;
                break;
            case 2:
                system(CLEAR);
                cout<<"Размер списка: "<<list.get_size()<<endl;
                break;
            case 3:
                system(CLEAR);
                cout<<"Введите добавляемое значение:\n---> "<<ends;
                cin>>value;

                while (true) {
                    cout<<ANSI_COLOR_RESET<<"\nВставка в конец(1), на конкретную позицию (2), отмена (3)\n---> "<<ends;

                    cin>>decision;

                    switch (decision) {
                        case 1:
                            list.push(value);
                            goto exit_from_loop_2;
                        case 2:
                            cout<<"Введите позицию:\n---> "<<ends;
                            cin>>idx;
                            list.push(value, idx);
                            goto exit_from_loop_2;
                        case 3:
                            goto exit_from_loop_2;
                        default:
                            cout<<ANSI_COLOR_RED<<"Пожалуйста, повторите ввод!\n";
                    }
                }
                exit_from_loop_2:
                    system(CLEAR);
                    break;
            case 4:
                while (true) {
                    cout<<ANSI_COLOR_RESET<<"\n1. Удаление заданного значения;\n"
                                            "2. удаление значения из позиции с заданным номером;\n"
                                            "3. отмена\n---> "<<ends;

                    cin>>decision;

                    switch (decision) {
                        case 1:
                            system(CLEAR);
                            cout<<"Введите удаляемое значение:\n--->"<<ends;
                            cin>>value;

                            list.remove_item(value);
                            goto exit_from_loop_3;
                        case 2:
                            cout<<"Введите позицию:\n---> "<<ends;
                            cin>>idx;
                            list.remove_idx(idx);
                            goto exit_from_loop_3;
                        case 3:
                            goto exit_from_loop_3;
                        default:
                            cout<<ANSI_COLOR_RED<<"Пожалуйста, повторите ввод!\n";
                    }
                }
            exit_from_loop_3:
                system(CLEAR);
                break;
            case 5:
                system(CLEAR);
                cout<<"Введите проверяемое значение:\n--->"<<ends;
                cin>>value;

                system(CLEAR);
                cout<<"\nЗначение \""<< value <<
                ((value<<list.contains(value)) ? "\" содержится в спискe\n" : "\" отсутствует в списке\n")<<endl;
                break;
            case 6:
                system(CLEAR);
                cout<<"Введите позицию:\n---> "<<ends;
                cin>>idx;
                cout<<"Запрашиваемое значение: "<<list.get_element_by_idx(idx)<<endl;
                system(CLEAR);
                break;
            case 7:
                system(CLEAR);
                cout<<"\nВведите значение:\n---> "<<ends;
                cin>>value;
                system(CLEAR);
                cout<<"Значение "<<value<<" находится на позиции "<<list.get_idx(value)<<endl;
                break;
            case 8:
                system(CLEAR);
                cout<<"Введите позицию:\n---> "<<ends;
                cin>>idx;
                cout<<"\nВведите новый элемент:\n---> "<<ends;
                cin>>value;
                system(CLEAR);
                cout<<"Значение "<<list.set_element_by_idx(value, idx)<<" было заменено на "<<value<<endl;
                break;
            case 9:
                system(CLEAR);
                cout<<(list.is_empty() ? "Список пуст" : "Список содержит элементы")<<endl;
                break;
            case 10:
                system(CLEAR);
                list.free();
                cout<<ANSI_COLOR_YELLOW<<"Список был очищен!"<<endl;
                break;
            case 11:
                exit(EXIT_SUCCESS);
            default:
                system(CLEAR);
                cout<<ANSI_COLOR_RED<<"Пожалуйста, повторите ввод!\n";
        }
    }
}
