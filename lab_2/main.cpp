#include "bst.h"
#include <iostream>

#define KEY_TYPE unsigned int
#define DATA_TYPE int

using namespace std;

int main() {
    bst<KEY_TYPE, DATA_TYPE> tree;

    tree.insert(50, 50);
    tree.insert(30, 30);
    tree.insert(10, 10);
    tree.insert(40, 40);
    tree.insert(20, 20);
    tree.insert(45, 45);
    tree.insert(70, 70);
    tree.insert(60, 60);
    tree.insert(65, 65);
    tree.insert(80, 80);

    bst<KEY_TYPE, DATA_TYPE>::iterator iter = tree.begin();
    bst<KEY_TYPE, DATA_TYPE>::reverse_iterator rev_iter = tree.rbegin();

    KEY_TYPE key;


    short decision;

    while (true) {
        cout<<"\n"
              "\n1.  Вывод дерева;\t\t\t\t10. установка прямого итератора в begin();"
              "\n2.  опрос размера дерева;\t\t\t11. установка прямого итератора в end();"
              "\n3.  очистка дерева;\t\t\t\t12. сравнение прямого итератор с end()"
              "\n4.  проверка дерева на пустоту;\t\t\t13. разыменование прямого итератора;"
              "\n5.  доступ по чтению/записи к\t\t\t14. инкремент прямого итератора;\n"
              "    данным по ключу;\t\t\t\t15. декремент прямого итератора;"
              "\n6.  включение данных с заданным ключом;\t\t16. установка обратного итератора в rbegin();"
              "\n7.  удаление данных с заданным ключом;\t\t17. установка обратного итератора в rend();"
              "\n8.  формирование списка ключей в дереве\t\t18. сравнение обратного итератор с rend()\n"
              "    в поряде Lt->t-Rt;\t\t\t\t19. разыменование обратного итератор;"
              "\n9.  поиск и подъем в корень дерева узла\t\t20. инкремент обратного итератора;\n"
              "    с ближайшим ключом, большим заданного\t21. декремент обратного итератора;\n"
              "    значения;"
              "\n---> "<<ends;
        cin>>decision;

        switch (decision) {
            case 1:
                cout<<tree;
                break;
            case 2:
                cout<<tree.get_size();
                break;
            case 3:
                tree.clear();
                break;
            case 4:
                cout<<tree.is_empty();
                break;
            case 5: {
                cout<<"Ключ ---> ";
                cin>>key;

                try {
                    DATA_TYPE &data = tree.get_by_key(key);
                    cout<<"Ключу "<<key<<" соответствует значение "<<data;
                    cout<<"\nИзменить? Да(1), нет(2).\n---> ";

                    while (true) {
                        cin>>decision;
                        switch (decision) {
                            case 1: {
                                cout<<"\nНовое значение:\n---> ";
                                cin>>data;
                                goto exit_loop_5;
                            }
                            case 2: {
                                goto exit_loop_5;
                            }
                            default: {
                                cout<<"\nПовторите ввод!\n--->";
                            }
                        }
                    }
                }catch (exception &e) {
                    cout<<"Исключение";
                }

                exit_loop_5:
                break;
            }

            case 6: {
                DATA_TYPE data;

                cout<<"Ключ ---> ";
                cin>>key;
                cout<<"\nЗначение ---> ";

                cin>>data;

                cout<<tree.insert(key, data);
                break;
            }

            case 7:
                cout<<"Ключ ---> ";
                cin>>key;

                cout<<tree.remove(key);
                break;

            case 8:
                tree.print_traversal();
                break;
            case 9:
                cout<<"Ключ ---> ";
                cin>>key;

                cout<<tree.climbing_greater_node(key);
                break;
            case 10:
                iter = tree.begin();
                break;
            case 11:
                iter = tree.end();
                break;
            case 12:
                cout<<(iter == tree.end());
                break;
            case 13:
                try {
                    DATA_TYPE &data = *iter;

                    cout<<"Значение узла итератора "<<data;
                    cout<<"\nИзменить? Да(1), нет(2).\n---> ";

                    while (true) {
                        cin>>decision;
                        switch (decision) {
                            case 1: {
                                cout<<"\nНовое значение:\n---> ";
                                cin>>data;
                                goto exit_loop_12;
                            }
                            case 2: {
                                goto exit_loop_12;
                            }
                            default: {
                                cout<<"\nПовторите ввод!\n--->";
                            }
                        }
                    }
                } catch (exception &e) {
                    cout<<"Исключение";
                }

                exit_loop_12:
                break;
            case 14:
                try {
                    ++iter;
                } catch (exception &e) {
                    cout<<"Исключение";
                }
                break;
            case 15:
                try {
                    --iter;
                } catch (exception &e) {
                    cout<<"Исключение";
                }
                break;
            case 16:
                rev_iter = tree.rbegin();
            break;
            case 17:
                rev_iter = tree.rend();
            break;
            case 18:
                cout<<(rev_iter == tree.rend());
                break;
            case 19:
                try {
                    DATA_TYPE &data = *rev_iter;

                    cout<<"Значение узла итератора "<<data;
                    cout<<"\nИзменить? Да(1), нет(2).\n---> ";

                    while (true) {
                        cin>>decision;
                        switch (decision) {
                            case 1: {
                                cout<<"\nНовое значение:\n---> ";
                                cin>>data;
                                goto exit_loop_17;
                            }
                            case 2: {
                                goto exit_loop_17;
                            }
                            default: {
                                cout<<"\nПовторите ввод!\n--->";
                            }
                        }
                    }
                } catch (exception &e) {
                    cout<<"Исключение";
                }

            exit_loop_17:
                break;

            case 20:
                try {
                    ++rev_iter;
                } catch (exception &e) {
                    cout<<"Исключение";
                }
                break;
            case 21:
                try {
                    --rev_iter;
                } catch (exception &e) {
                    cout<<"Исключение";
                }
                break;
        }
    }
}
