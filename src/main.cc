#include <iostream>
#include "compiler_options.h"

int main (int argc, char** argv) {
    minic::utils::CompilerOptions options;
    options.ParseCommandLine(argc, argv);
    return 0;
}