#include "instruction.h"

instruction::instruction() {}

instruction::instruction(const std::initializer_list<std::string_view> &&ini_list_move) {
    for (unsigned char i = 0; auto& list_part: ini_list_move) {
        _code_buffer[i] = list_part;
        ++i;
    }
}

bool instruction::operator==(const instruction & other) const {
    return is_equal(other);
}

bool instruction::operator==(const instruction &&other) const {
    return is_equal(other);
}

std::string instruction::operator[](const int index) const {
    if (index < _code_buffer.size()) {
        return _code_buffer[index];
    }

    return "";
}

std::vector<std::string>& instruction::get() {
    return _code_buffer;
}

const std::vector<std::string>& instruction::get() const {
    return _code_buffer;
}

instruction::operator std::vector<std::string>&() {
    return _code_buffer;
}

void instruction::push_back(const std::string &str) {
    _code_buffer.push_back(str);
}

void instruction::emplace_back(const std::string &str) {
    _code_buffer.emplace_back(str);
}

void instruction::clear() {
    _code_buffer.clear();
}

bool instruction::is_equal(const instruction & other) const {
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
