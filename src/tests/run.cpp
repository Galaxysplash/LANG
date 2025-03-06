#include "run.h"

__run_struct::__run_struct(const std::function<void()> &&func_move) {
    func_move();
}
