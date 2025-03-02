#include <iostream>
#include <string>
#include <vector>

#include <summary/program.h>
#include <framework/init.h>

int main(const int argc, const char** argv) {
    std::vector<std::string> instructions;

    //get_code(argc, argv, instructions);
    split(instructions, "a: num = 10");

    process_code(instructions, {
        "+-",
        "*/"
    });

    for (const auto& instruction : instructions) {
        std::cout << instruction;
    }

    execute_code();
}
