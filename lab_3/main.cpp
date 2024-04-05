#include "rbst.h"
#include <iostream>


int main() {
    srand((unsigned) time(nullptr));
    rbst<unsigned long, int> pretty_tree;
    
    for (int i = 2; i < 10; i++) {
        std::cout<<pretty_tree.insert(i * 10,i)<<std::endl; 
    }

    std::cout<<pretty_tree.insert(3,14)<<std::endl;
    std::cout<<pretty_tree.insert(45, 10)<<std::endl;


    rbst<unsigned long, int> copy(pretty_tree);

    std::cout<<pretty_tree<<"Hello Wolrd!"<<std::endl;
   
    pretty_tree.clear();

    std::cout<<pretty_tree<<"Hello Wolrd!"<<std::endl;

    return(EXIT_SUCCESS);	
}
