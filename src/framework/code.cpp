#include "code.h"

code::code() {}

code::code(const std::initializer_list<std::string_view> &&ini_list_move) {
    for (unsigned char i = 0; auto& list_part: ini_list_move) {
        _code_buffer[i] = list_part;
        ++i;
    }
}

bool code::operator==(const code & other) const {
    return is_equal(other);
}

bool code::operator==(const code &&other) const {
    return is_equal(other);
}

std::string code::operator[](const int index) const {
    return _code_buffer[index];
}

std::vector<std::string>& code::get() {
    return _code_buffer;
}

const std::vector<std::string>& code::get() const {
    return _code_buffer;
}

void code::clear() {
    _code_buffer.clear();
}

bool code::is_equal(const code & other) const {
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
