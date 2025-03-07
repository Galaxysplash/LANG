#include "classes/code.h"
#include "jit/jit.h"

int main(const int argc, const char **argv) {
    code code_buffer{};

    jit::run(argc, argv, code_buffer);
}