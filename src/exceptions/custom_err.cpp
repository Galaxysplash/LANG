#include "custom_err.h"


custom_err::custom_err(const std::string_view &&msg) : _msg(msg) {}

const char * custom_err::what() const noexcept {
    return _msg.data();
}

