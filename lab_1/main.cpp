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

    for (int i = 0; i < 10; ++i) {
        list.push(i);
    }

    while (true) {
        cout<<ANSI_COLOR_RESET<<"\n\n"
                                "0.  Запрос числа элементов списка, просмотренных предыдущей операцией;\n"
                                "1.  вывод списка;\n"
                                "2.  получить размер списка;\n"
                                "3.  вставка элемента;\n"
                                "4.  удаление элемента;\n"
                                "5.  опрос наличия элемента;\n"
                                "6.  чтение значения с заданным номером в списке;\n"
                                "7.  получение позиции в списке для заданного значения;\n"
                                "8.  изменение значения с заданным номером в списке;\n"
                                "9.  проверка на пустоту;\n"
                                "10. очистка списка;\n"
                                "11. выход.\n"
                                "---> "<<ends;
        cin>>decision;
        switch (decision) {
            case 0:
                system(CLEAR);
                cout<<"Просмотрено "<<ANSI_COLOR_YELLOW<<
                    list.get_traverse_count()<<ANSI_COLOR_RESET<<" элемента(ов)"<<endl;
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

                            try {
                                list.push(value, idx);
                                system(CLEAR);
                                cout<<"Просмотрено "<<ANSI_COLOR_YELLOW<<
                                    list.get_traverse_count()<<ANSI_COLOR_RESET<<" элемента(ов)"<<endl;
                            } catch (exception &e) {
                                cerr<<ANSI_COLOR_RED<<e.what()<<endl;
                            }

                            goto exit_from_loop_2;
                        case 3:
                            goto exit_from_loop_2;
                        default:
                            cout<<ANSI_COLOR_RED<<"Пожалуйста, повторите ввод!\n";
                    }
                }
                exit_from_loop_2:
                    break;
            case 4:
                while (true) {
                    cout<<ANSI_COLOR_RESET<<"\n1. Удаление заданного значения;\n"
                                            "2. удаление значения из позиции с заданным номером;\n"
                                            "3. отмена\n---> "<<ends;

                    cin>>decision;

                    switch (decision) {
                        case 1:
                            cout<<"Введите удаляемое значение:\n--->"<<ends;
                            cin>>value;
                            try {
                                system(CLEAR);
                                cout<<"Значение "<<value<<
                                    (list.remove_item(value) ? " было удалено" : " не было найдено!")<<endl;
                                cout<<"Просмотрено "<<ANSI_COLOR_YELLOW<<
                                    list.get_traverse_count()<<ANSI_COLOR_RESET<<" элемента(ов)"<<endl;
                            } catch (exception &e) {
                                cerr<<ANSI_COLOR_RED<<e.what()<<endl;
                            }
                            goto exit_from_loop_3;
                        case 2:
                            cout<<"Введите позицию:\n---> "<<ends;
                            cin>>idx;
                            try {
                                system(CLEAR);
                                cout<<"Значение "<<list.remove_idx(idx)<<" было удалено!"<<endl;
                                cout<<"Просмотрено "<<ANSI_COLOR_YELLOW<<
                                    list.get_traverse_count()<<ANSI_COLOR_RESET<<" элемента(ов)"<<endl;
                            } catch (exception &e) {
                                cerr<<ANSI_COLOR_RED<<e.what()<<endl;
                            }
                            goto exit_from_loop_3;
                        case 3:
                            system(CLEAR);
                            goto exit_from_loop_3;
                        default:
                            cout<<ANSI_COLOR_RED<<"Пожалуйста, повторите ввод!\n";
                    }
                }
            exit_from_loop_3:
                break;
            case 5:
                cout<<"Введите проверяемое значение:\n--->"<<ends;
                cin>>value;

                system(CLEAR);
                cout<<"Значение "<< value <<
                ((value<<list.contains(value)) ? " содержится в спискe" : " отсутствует в списке")<<endl;
                cout<<"Просмотрено "<<ANSI_COLOR_YELLOW<<
                    list.get_traverse_count()<<ANSI_COLOR_RESET<<" элемента(ов)"<<endl;
                break;
            case 6:
                cout<<"Введите позицию:\n---> "<<ends;
                cin>>idx;

                try {
                    system(CLEAR);
                    cout<<"Запрашиваемое значение: "<<list.get_element_by_idx(idx)<<endl;
                    cout<<"Просмотрено "<<ANSI_COLOR_YELLOW<<
                        list.get_traverse_count()<<ANSI_COLOR_RESET<<" элемента(ов)"<<endl;
                } catch (exception &e) {
                    cerr<<ANSI_COLOR_RED<<e.what()<<endl;
                }

                break;
            case 7:
                cout<<"\nВведите значение:\n---> "<<ends;
                cin>>value;

                try {
                    system(CLEAR);
                    cout<<"Значение "<<value<<" находится на позиции "<<list.get_idx(value)<<endl;
                    cout<<"Просмотрено "<<ANSI_COLOR_YELLOW<<
                        list.get_traverse_count()<<ANSI_COLOR_RESET<<" элемента(ов)"<<endl;
                } catch (exception &e) {
                    cerr<<ANSI_COLOR_RED<<e.what()<<endl;
                }

                break;
            case 8:
                cout<<"Введите позицию:\n---> "<<ends;
                cin>>idx;
                cout<<"\nВведите новый элемент:\n---> "<<ends;
                cin>>value;

                try {
                    system(CLEAR);
                    cout<<"Значение "<<list.set_element_by_idx(value, idx)<<" было заменено на "<<value<<endl;
                    cout<<"Просмотрено "<<ANSI_COLOR_YELLOW<<
                        list.get_traverse_count()<<ANSI_COLOR_RESET<<" элемента(ов)"<<endl;
                } catch (exception &e) {
                    cerr<<ANSI_COLOR_RED<<e.what()<<endl;
                }

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
