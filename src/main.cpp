#include "language/classes/instruction.h"
#include "jiter/jiter.h"

int main(const int argc, const char **argv) {
    instruction code_buffer{};

    jiter::run(argc, argv, code_buffer);
}