#include "classes/code.h"
#include "jiter/jiter.h"

int main(const int argc, const char **argv) {
    code code_buffer{};

    jiter::run(argc, argv, code_buffer);
}