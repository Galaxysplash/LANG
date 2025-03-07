#pragma once

#include <functional>

struct __run_struct {
    explicit __run_struct(const std::function<void()> && func_move);
};


#define RUN __run_struct r{[](){

#define END_RUN }};
