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
