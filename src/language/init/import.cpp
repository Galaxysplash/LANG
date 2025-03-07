#include "import.h"

#include <fstream>


void import::file(
    const int argc, const char **argv, std::string &ret
) {
    if (argc < 2) return;

    std::ifstream file;

    file.open(argv[1]);
    file >> ret;
    file.close();
}