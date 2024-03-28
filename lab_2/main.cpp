#include "bst.h"
#include <iostream>


void test() {
    bst<unsigned long, int> pretty_tree;

    pretty_tree.insert(50, 2);
    pretty_tree.insert(30, 3);
    pretty_tree.insert(10, 6);
    pretty_tree.insert(40, 23);
    pretty_tree.insert(20, 6);
    pretty_tree.insert(45, 12);
    pretty_tree.insert(70, 6);
    pretty_tree.insert(60, 7);
    pretty_tree.insert(65, 7);
    pretty_tree.insert(80, 7);

    std::cout<<"Исходное дерево:\n"<<pretty_tree<<"\n-----"<<std::endl;

    std::cout<<"Лист обхода L T R:\n"<<std::endl;
    pretty_tree.print_traversal();
    std::cout<<"\n-----"<<std::endl;


    std::cout<<"Удаление 60: "<<pretty_tree.remove(60)<<'\n'<<pretty_tree<<std::endl;

    std::cout<<"Повторное удаление 60: "<<pretty_tree.remove(60)<<'\n'<<pretty_tree<<std::endl;


    std::cout<<"Поднятие вершины с ключом больше 53: "<<pretty_tree.climbing_greater_node(53)<<'\n'<<pretty_tree<<std::endl;

    std::cout<<"Удаление корня (70): "<<pretty_tree.remove(70)<<'\n'<<pretty_tree<<std::endl;

}


int main() {

    test();
    return(EXIT_SUCCESS);	
}
