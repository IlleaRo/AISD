#include <iostream>
#include <cstring>
#include "ui/test.h"
#include "graphs/graph.h"


int main(int argc, char *argv[]) {
    if (argc > 1 && (strcmp(argv[1], "test") == 0)) {
        return run_test();
    }



    return 0;
}