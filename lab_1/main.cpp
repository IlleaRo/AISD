#include "list.h"
#include <iostream>

#define TYPE int

using namespace std;


// ANSI Escape-последовательности для цветов
const string ANSI_COLOR_RED = "\033[31m";
const string ANSI_COLOR_GREEN = "\033[32m";
const string ANSI_COLOR_YELLOW = "\033[33m";
const string ANSI_COLOR_BLUE = "\033[34m";
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
    cerr << "Removed " << test_list.remove(2) << " from list in " << test_list.get_traverse_count() << " its" << endl;
    cerr << "Removed " << test_list.remove(1) << " from list in " << test_list.get_traverse_count() << " its" << endl;
    cerr << "Removed " << test_list.remove(0) << " from list in " << test_list.get_traverse_count() << " its" << endl;
    return 0;
}

int main()
{
    list<TYPE> list;
    TYPE value;
    unsigned int idx;
    short decision;

    while (true) {
        cout<<ANSI_COLOR_RESET<<"\n\n1. Вывод списка\n2. Получить размер списка\n"
                                "3. Вставка элемента\n4. Удаление элемента\n"
                                "5. Опрос наличия элемента\n6. Чтение значения с заданным номером в списке\n"
                                "7. Проверка на пустоту\n"
                                "8. Очистка списка\n"
                                "9. Выход\n---> "<<ends;
        cin>>decision;
        switch (decision) {
            case 1:
                system("clear");
                cout<<list;
                break;
            case 2:
                system("clear");
                cout<<"Размер списка: "<<list.get_size()<<endl;
                break;
            case 3:
                system("clear");
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
                    system("clear");
                    break;
            case 4:
                while (true) {
                    cout<<ANSI_COLOR_RESET<<"\n1. Удаление заданного значения\n"
                                            "2. удаление значения из позиции с заданным номером\n"
                                            "3. отмена\n---> "<<ends;

                    cin>>decision;

                    switch (decision) {
                        case 1:
                            system("clear");
                            cout<<"Введите удаляемое значение:\n--->"<<ends;
                            cin>>value;

                            list.remove(value);
                            goto exit_from_loop_3;
                        case 2:
                            cout<<"Введите позицию:\n---> "<<ends;
                            cin>>idx;
                            list.remove(idx);
                            goto exit_from_loop_3;
                        case 3:
                            goto exit_from_loop_3;
                        default:
                            cout<<ANSI_COLOR_RED<<"Пожалуйста, повторите ввод!\n";
                    }
                }
            exit_from_loop_3:
                system("clear");
                break;
            case 5:
                system("clear");
                cout<<"Введите проверяемое значение:\n--->"<<ends;
                cin>>value;

                cout<<"\nЭлемент \""<<
                ((value<<list.contains(value)) ? "\" содержится в спискe\n" : "\" отсутствует в списке\n")<<endl;
                system("clear");
                break;
            case 6:
                system("clear");
                cout<<"Введите позицию:\n---> "<<ends;
                cin>>idx;
                cout<<"Запрашиваемое значение: "<<list.get_element_by_idx(idx)<<endl;
                system("clear");
                break;
            case 7:
                system("clear");
                cout<<(list.is_empty() ? "Список пуст" : "Список содержит элементы")<<endl;
                break;
            case 8:
                system("clear");
                list.free();
                cout<<ANSI_COLOR_YELLOW<<"Список был очищен!"<<endl;
                break;
            case 9:
                exit(EXIT_SUCCESS);
            default:
                system("clear");
                cout<<ANSI_COLOR_RED<<"Пожалуйста, повторите ввод!\n";
        }
    }
}
