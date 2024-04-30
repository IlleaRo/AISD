#include <iostream>
#include "prompts.h"

using namespace std;

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
