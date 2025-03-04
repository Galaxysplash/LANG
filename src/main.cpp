#include "summary/program.h"

#include <string>
#include <vector>

int main(const int argc, const char **argv) {
    std::vector<std::string> code;

    run(argc, argv, code);
}
