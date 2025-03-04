#include "summary/program.h"

#include <string>
#include <vector>

int main(const int argc, const char **argv) {
    const bool in_terminal = argc <= 1;
    std::vector<std::string> code;

    // ReSharper disable once CppDFALoopConditionNotUpdated
     do {
        run(argc, argv, in_terminal, code);

        if (in_terminal) {
            code.clear();
        }
    } while (in_terminal);
}
