#include "framework/code.h"
#include "summary/program.h"

int main(const int argc, const char **argv) {
    code code_buffer{};

    app(argc, argv, code_buffer);
}