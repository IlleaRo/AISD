#include <iostream>

using namespace std;

int tests()
{
    int function_counter = 0;
    /*
     * if (test_function() != success)
     * {
     *     return function_counter;
     * }
     * function_counter++;
     */
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