#include "code.h"

code::code(const std::initializer_list<std::string> &&ini_list_move) : _code_buffer(ini_list_move) {}

bool code::operator==(const code & other) const {
    return is_equal(other);
}

bool code::operator==(const code &&other) const {
    return is_equal(other);
}

void code::emplace_back(const std::string& str) {
    _code_buffer.emplace_back(str);
}

void code::push_back(const std::string& str) {
    _code_buffer.push_back(str);
}

void code::clear() {
    _code_buffer.clear();
}

bool code::is_equal(const code &other) const {
    for (unsigned char i = 0; const std::string & str : _code_buffer) {
        if (i > other._code_buffer.size()) {
            return false;
        }

        if (str != other._code_buffer[i]) {
            return false;
        }
        ++i;
    }

    return true;
}
