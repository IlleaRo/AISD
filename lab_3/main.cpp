#include "rbst.h"
#include <iostream>

using namespace std;
int main() {
    rbst<unsigned long, int> pretty_tree;
    for (int i = 0; i < 10; ++i) {

        pretty_tree.insert(45, 45);
        pretty_tree.insert(35, 35);
        pretty_tree.insert(47, 47);
        pretty_tree.insert(30, 30);
        pretty_tree.insert(40, 40);
        pretty_tree.insert(46, 46);
        pretty_tree.insert(48, 48);


        //cout << pretty_tree << "\n\n";
        unsigned long size = pretty_tree.get_size();

        pretty_tree.remove(45);
        if (pretty_tree.get_size() + 1 != size) {
            cout << pretty_tree;
            return 0;
        }
        cout <<"Вывод 1\n"<< pretty_tree;

        pretty_tree.remove(35);
        if (pretty_tree.get_size() + 2 != size) {
            cout << pretty_tree;
            return 0;
        }
        cout <<"Вывод 2\n"<< pretty_tree;
        pretty_tree.remove(47);
        if (pretty_tree.get_size() + 3 != size) {
            cout << pretty_tree;
            return 0;
        }
        cout <<"Вывод 3\n"<< pretty_tree;
        pretty_tree.remove(30);
        if (pretty_tree.get_size() + 4 != size) {
            cout << pretty_tree;
            return 0;
        }
        cout <<"Вывод 4\n"<< pretty_tree;
        pretty_tree.remove(40);
        if (pretty_tree.get_size() + 5 != size) {
            cout << pretty_tree;
            return 0;
        }
        cout <<"Вывод 5\n"<< pretty_tree;
        pretty_tree.remove(46);
        if (pretty_tree.get_size() + 6 != size) {
            cout << pretty_tree;
            return 0;
        }
        cout <<"Вывод 6\n"<< pretty_tree;
        pretty_tree.remove(48);
        if (pretty_tree.get_size() + 7 != size) {
            cout << pretty_tree;
            return 0;
        }

        cout <<"Результат:"<< pretty_tree << "\nКонец результата\n";
    }


    return(EXIT_SUCCESS);	
}
