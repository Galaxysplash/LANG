#include <algorithm>

#include "kit.hpp"

#include <cstdio>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

int main(const int argc, const char** argv) {
    std::string txt;
    std::vector<std::string> instructions;

    kit::read(argc, argv, txt);
    
    kit::split(instructions, txt);

    for (const std::string& instruction: instructions) {
        printf("%s", instruction.c_str());
    }
}
