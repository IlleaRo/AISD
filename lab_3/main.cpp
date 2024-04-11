#include "rbst.h"
#include <iostream>


int main() {
    srand((unsigned) time(nullptr));
    rbst<unsigned long, int> pretty_tree;
    
    for (int i = 1; i < 10; i++) {
        pretty_tree.insert(i * 10,i);
    }

    pretty_tree.insert(45, 10);
    pretty_tree.insert(3,14);

    pretty_tree.remove(45);

    //pretty_tree.remove(40);

    for (int i = 1; i < 10; i++) {
        pretty_tree.remove(i * 10);
    }

    std::cout<<pretty_tree<<std::endl;

    std::cout << "Subtree sizes correct: " << pretty_tree.check_subtree_sizes() << std::endl;

    return(EXIT_SUCCESS);
}
