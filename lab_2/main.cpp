#include "bst.h"
#include <iostream>


void test() {
    bst<unsigned long, int> pretty_tree;

    pretty_tree.insert(50, 50);
    pretty_tree.insert(30, 30);
    pretty_tree.insert(10, 10);
    pretty_tree.insert(40, 40);
    pretty_tree.insert(20, 20);
    pretty_tree.insert(45, 45);
    pretty_tree.insert(70, 70);
    pretty_tree.insert(60, 60);
    pretty_tree.insert(65, 65);
    pretty_tree.insert(80, 80);

    std::cout<<"Исходное дерево:\n"<<pretty_tree<<"\n-----"<<std::endl;

    std::cout<<"Лист обхода L T R:\n"<<std::endl;
    pretty_tree.print_traversal();
    std::cout<<"\n-----"<<std::endl;


    std::cout<<"Удаление 60: "<<pretty_tree.remove(60)<<'\n'<<pretty_tree<<std::endl;

    std::cout<<"Повторное удаление 60: "<<pretty_tree.remove(60)<<'\n'<<pretty_tree<<std::endl;


    std::cout<<"Поднятие вершины с ключом больше 53: "<<pretty_tree.climbing_greater_node(53)<<'\n'<<pretty_tree<<std::endl;

    std::cout<<"Удаление корня (70): "<<pretty_tree.remove(70)<<'\n'<<pretty_tree<<std::endl;

    std::cout<<"Запрос прямого итератора begin()";
    bst<unsigned long, int>::iterator iter = pretty_tree.begin();

    try {
        while (*iter) {

            ++iter;
            std::cout<<*iter<<" ";
        }
    } catch (std::exception &e) {
           std::cout<<e.what();
    }

    std::cout<<"\nЗапрос обратного итератора rbegin()";
    bst<unsigned long, int>::reverse_iterator riter = pretty_tree.rbegin();

    try {
        while (*riter) {

            ++riter;
            std::cout<<*riter<<" ";
        }
    } catch (std::exception &e) {
        std::cout<<e.what();
    }
}


int main() {

    test();
    return(EXIT_SUCCESS);	
}
