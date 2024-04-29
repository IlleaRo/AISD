#include <iostream>
#include "prompts.h"

using namespace std;

int get_user_input(const char *prompt) {
    int input;

    if (prompt) {
        cout << prompt;
    }
    cin >> input;

    return input;
}

#ifdef _WIN32
void anykey()
{
    system("pause");
}
#else
void anykey()
{
    std::cout << "Нажмите ENTER, чтобы продолжить";
    std::cout.flush();
    system("bash -c read");
}
#endif
