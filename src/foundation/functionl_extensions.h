#pragma once

#include <vector>
#include <string>
#include <functional>

template <typename T>
void multi_filter(
    const std::vector<std::string>& instructions,
    std::vector<T>&& filter,
    const std::function<void(const std::vector<T>&&)>&& func
);
