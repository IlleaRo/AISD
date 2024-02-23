#include "list.h"
#include <iostream>

using namespace std;

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
    int test_result;
    cout << "Running tests" << endl;
    test_result = tests();
    if (test_result != 0)
    {
        cout << "Tests failed at function #" << test_result << endl;
    }
    else
    {
        cout << "Success" << endl;
    }
    return 0;
}
