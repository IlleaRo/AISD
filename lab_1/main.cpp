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

int main()
{
    list<TYPE> pretty_list;
    TYPE value;
    unsigned int idx;
    short decision;

    for (int i = 0; i < 10; ++i) {
        pretty_list.push(i);
    }

    list<TYPE>::iterator iter = pretty_list.begin();
    list<TYPE>::reverse_iterator riter = pretty_list.rbegin();

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
                                "11. использовать конструктор копирования (выводит оригинал и копию);\n"
                                "12. разыменование прямого итератора;\n"
                                "13. установка прямого итератора в начало - begin();\n"
                                "14. установить прямой итератор в end();\n"
                                "15. инкремент прямого итератора;\n"
                                "16. декремент прямого итератора;\n"
                                "17. сравнить прямой итератор с end();\n"
                                "18. разыменование обратного итератора;\n"
                                "19. установка обратного итератора в конец списка - rbegin();\n"
                                "20. установить обратный итератор в rend();\n"
                                "21. инкремент обратного итератора;\n"
                                "22. декремент обратного итератора;\n"
                                "23. сравнить обратный итератор с rend();\n"
                                "24. выход.\n"
                                "---> "<<ends;
        cin>>decision;
        switch (decision) {
            case 0:
                system(CLEAR);
                cout << "Просмотрено " << ANSI_COLOR_YELLOW <<
                     pretty_list.get_traverse_count() << ANSI_COLOR_RESET << " элемента(ов)" << endl;
                break;
            case 1:
                system(CLEAR);
                cout << pretty_list;
                break;
            case 2:
                system(CLEAR);
                cout << "Размер списка: " << pretty_list.get_size() << endl;
                break;
            case 3:
                cout<<"Введите добавляемое значение:\n---> "<<ends;
                cin>>value;

                while (true) {
                    cout<<ANSI_COLOR_RESET<<"\nВставка в конец(1), на конкретную позицию (2), отмена (3)\n---> "<<ends;

                    cin>>decision;

                    switch (decision) {
                        case 1:
                            pretty_list.push(value);
                            goto exit_from_loop_2;
                        case 2:
                            cout<<"Введите позицию:\n---> "<<ends;
                            cin>>idx;

                            try {
                                pretty_list.push(value, idx);
                                system(CLEAR);
                                cout << "Просмотрено " << ANSI_COLOR_YELLOW <<
                                     pretty_list.get_traverse_count() << ANSI_COLOR_RESET << " элемента(ов)" << endl;
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
                                cout << "Значение " << value <<
                                     (pretty_list.remove_item(value) ? " было удалено" : " не было найдено!") << endl;
                                cout << "Просмотрено " << ANSI_COLOR_YELLOW <<
                                     pretty_list.get_traverse_count() << ANSI_COLOR_RESET << " элемента(ов)" << endl;
                            } catch (exception &e) {
                                cerr<<ANSI_COLOR_RED<<e.what()<<endl;
                            }
                            goto exit_from_loop_3;
                        case 2:
                            cout<<"Введите позицию:\n---> "<<ends;
                            cin>>idx;
                            try {
                                system(CLEAR);
                                cout << "Значение " << pretty_list.remove_idx(idx) << " было удалено!" << endl;
                                cout << "Просмотрено " << ANSI_COLOR_YELLOW <<
                                     pretty_list.get_traverse_count() << ANSI_COLOR_RESET << " элемента(ов)" << endl;
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
                (pretty_list.contains(value) ? " содержится в спискe" : " отсутствует в списке")
                <<endl;
                cout << "Просмотрено " << ANSI_COLOR_YELLOW <<
                     pretty_list.get_traverse_count() << ANSI_COLOR_RESET << " элемента(ов)" << endl;
                break;
            case 6:
                cout<<"Введите позицию:\n---> "<<ends;
                cin>>idx;

                try {
                    system(CLEAR);
                    cout << "Запрашиваемое значение: " << pretty_list.get_element_by_idx(idx) << endl;
                    cout << "Просмотрено " << ANSI_COLOR_YELLOW <<
                         pretty_list.get_traverse_count() << ANSI_COLOR_RESET << " элемента(ов)" << endl;
                } catch (exception &e) {
                    cerr<<ANSI_COLOR_RED<<e.what()<<endl;
                }

                break;
            case 7:
                cout<<"\nВведите значение:\n---> "<<ends;
                cin>>value;

                try {
                    system(CLEAR);
                    cout << "Значение " << value << " находится на позиции " << pretty_list.get_idx(value) << endl;
                    cout << "Просмотрено " << ANSI_COLOR_YELLOW <<
                         pretty_list.get_traverse_count() << ANSI_COLOR_RESET << " элемента(ов)" << endl;
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
                    cout << "Значение " << pretty_list.set_element_by_idx(value, idx) << " было заменено на " << value << endl;
                    cout << "Просмотрено " << ANSI_COLOR_YELLOW <<
                         pretty_list.get_traverse_count() << ANSI_COLOR_RESET << " элемента(ов)" << endl;
                } catch (exception &e) {
                    cerr<<ANSI_COLOR_RED<<e.what()<<endl;
                }

                break;
            case 9:
                system(CLEAR);
                cout << (pretty_list.is_empty() ? "Список пуст" : "Список содержит элементы") << endl;
                break;
            case 10:
                system(CLEAR);
                pretty_list.free();
                cout<<ANSI_COLOR_YELLOW<<"Список был очищен!"<<endl;
                break;
            case 11: {
                system(CLEAR);

                list<TYPE> copied_list(pretty_list);
                cout<<"Oригинал:\n"<<pretty_list<<"Копия:\n"<<copied_list;
                break;
            }
            case 12:
                system(CLEAR);

                try {
                    cout<<*iter<<endl;
                } catch (exception &e) {
                    cerr<<ANSI_COLOR_RED<<e.what()<<endl;
                }

                break;
            case 13:
                system(CLEAR);

                cout<<ANSI_COLOR_YELLOW<<"Итератор установлен на первый элемент."<<endl;
                iter = pretty_list.begin();
                break;
            case 14:
                system(CLEAR);

                cout<<ANSI_COLOR_YELLOW<<"Итератор переведен в неустановленное состояние."<<endl;
                iter = pretty_list.end();

                break;
            case 15:
                system(CLEAR);

                try {
                    iter++;
                    cout<<"OK"<<endl;
                } catch (exception &e) {
                    cerr<<ANSI_COLOR_RED<<e.what()<<endl;
                }

                break;
            case 16:
                system(CLEAR);

                try {
                    iter--;
                    cout<<"OK"<<endl;
                } catch (exception &e) {
                    cerr<<ANSI_COLOR_RED<<e.what()<<endl;
                }

                break;
            case 17:
                system(CLEAR);

                cout<<(iter == pretty_list.end() ?
                       "Итератор в неустановленном состоянии" : "Итератор установлен и отличается от end()")<<endl;
                break;
            case 18:
                system(CLEAR);

                try {
                    cout<<*riter<<endl;
                } catch (exception &e) {
                    cerr<<ANSI_COLOR_RED<<e.what()<<endl;
                }

                break;
            case 19:
                system(CLEAR);

                riter = pretty_list.rbegin();

                break;
            case 20:
                system(CLEAR);

                cout<<ANSI_COLOR_YELLOW<<"Итератор переведен в неустановленное состояние."<<endl;
                riter = pretty_list.rend();

                break;
            case 21:
                system(CLEAR);

                try {
                    riter++;
                    cout<<"OK"<<endl;
                } catch (exception &e) {
                    cerr<<ANSI_COLOR_RED<<e.what()<<endl;
                }

                break;
            case 22:
                system(CLEAR);

                try {
                    riter--;
                    cout<<"OK"<<endl;
                } catch (exception &e) {
                    cerr<<ANSI_COLOR_RED<<e.what()<<endl;
                }

                break;
            case 23:
                system(CLEAR);

                cout<<(riter == pretty_list.rend() ?
                       "Итератор в неустановленном состоянии" : "Итератор установлен и отличается от end()")<<endl;

                break;
            case 24:
                exit(EXIT_SUCCESS);
            default:
                system(CLEAR);
                cout<<ANSI_COLOR_RED<<"Пожалуйста, повторите ввод!\n";
        }
    }
}
