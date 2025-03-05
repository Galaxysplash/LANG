#pragma once

#include <string>
#include <vector>

struct code {
    code(const std::initializer_list<std::string>&& ini_list_move);

    bool operator==(const code & other) const;
    bool operator==(const code && other) const;

    void emplace_back(const std::string& str);
    void push_back(const std::string& str);

    void clear();

private:
    std::pmr::vector<std::string> _code_buffer{};

    [[nodiscard]] bool is_equal(const code & other) const;

public:
    auto begin() { return _code_buffer.begin(); }
    auto end() { return _code_buffer.end(); }
    [[nodiscard]] auto begin() const { return _code_buffer.begin(); }
    [[nodiscard]] auto end() const { return _code_buffer.end(); }
    auto front() { return _code_buffer.front(); }
    auto back() { return _code_buffer.back(); }
};



