#include "../../include/types/json_boolean.hpp"

json_boolean::json_boolean(bool value) : value_(value) {}

json_boolean::json_boolean(const json_boolean& other) : value_(other.value_) {}

json_boolean::json_boolean(json_boolean&& other) noexcept : value_(other.value_) {
    other.value_ = false;
}

json_boolean& json_boolean::operator=(const json_boolean& other) {
    if (this != &other) {
        value_ = other.value_;
    }

    return *this;
}

json_boolean& json_boolean::operator=(json_boolean&& other) noexcept {
    if (this != &other) {
        value_ = other.value_;
        other.value_ = false;
    }
    
    return *this;
}

std::string json_boolean::dump(int indent, int current_indent) const {
    std::ignore = indent;
    std::ignore = current_indent;
    
    return value_ ? "true" : "false";
}

bool json_boolean::get_value() const {
    return value_;
}

bool json_boolean::operator==(const json_boolean& other) const {
    return value_ == other.value_;
}

bool json_boolean::operator!=(const json_boolean& other) const {
    return !(*this == other);
}
