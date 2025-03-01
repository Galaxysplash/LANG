#pragma once

#include <vector>
#include <string_view>
#include <functional>

namespace kit {
    void split(
        std::vector<std::string>& ret,
        const std::string_view& txt
    );

    void scan(
        const std::vector<std::string>& instructions,
        const std::function<void()>&&
    );
}
