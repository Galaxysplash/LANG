#include "framework/code.h"
#include "summary/program.h"

int main(const int argc, const char **argv) {
    code code_buffer{};

    program::start(argc, argv, code_buffer);
}