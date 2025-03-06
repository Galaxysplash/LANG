#pragma once

#include <string>
#include <vector>

#define __CODE_BUFFER_TYPE_IN_CODE_CLASS std::vector<std::string>

class code {
public:
    code();
    code(const std::initializer_list<std::string_view> && ini_list_move);

    bool operator==(const code & other) const;
    bool operator==(const code && other) const;
    std::string operator[](int index) const;
    std::vector<std::string>& get();
    [[nodiscard]] const __CODE_BUFFER_TYPE_IN_CODE_CLASS & get() const;

    operator __CODE_BUFFER_TYPE_IN_CODE_CLASS &();

    void push_back(const std::string & str);
    void emplace_back(const std::string & str);

    void clear();

private:
     __CODE_BUFFER_TYPE_IN_CODE_CLASS _code_buffer{};

    [[nodiscard]] bool is_equal(const code & other) const;

public:
    auto begin() { return _code_buffer.begin(); }
    auto end() { return _code_buffer.end(); }
    [[nodiscard]] auto begin() const { return _code_buffer.begin(); }
    [[nodiscard]] auto end() const { return _code_buffer.end(); }
    auto front() { return _code_buffer.front(); }
    auto back() { return _code_buffer.back(); }
};



