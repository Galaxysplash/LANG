#include <string>
#include <vector>

#include <summary/program.h>

int main(const int argc, const char** argv) {
    std::vector<std::string_view> instructions;

    get_code(argc, argv, instructions);


}
