#pragma once

#include <exception>
#include <string_view>

class custom_err final : std::exception {
public:
    explicit custom_err(const std::string_view&& msg);
    [[nodiscard]] const char* what() const noexcept override;

private:
    std::string_view _msg;
};


