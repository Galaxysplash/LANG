#pragma once

#include <vector>
#include <string_view>
#include <functional>

namespace kit {
    void read(
        int argc,
        const char** argv,
        std::string& ret
    );

    void split(
        std::vector<std::string>& ret,
        const std::string_view& txt
    );
}
