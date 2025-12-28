#include "../../include/types/json_number.hpp"
#include <sstream>
#include <cmath>

json_number::json_number(double value) : value_(value) {}

json_number::json_number(const json_number& other) : value_(other.value_) {}

json_number::json_number(json_number&& other) noexcept : value_(other.value_) {
    other.value_ = 0.0;
}

json_number& json_number::operator=(const json_number& other) {
    if (this != &other) {
        value_ = other.value_;
    }

    return *this;
}

json_number& json_number::operator=(json_number&& other) noexcept {
    if (this != &other) {
        value_ = other.value_;
        other.value_ = 0.0;
    }
    
    return *this;
}

std::string json_number::dump(int indent, int current_indent) const {
    std::ignore = indent;
    std::ignore = current_indent;
    std::ostringstream oss;
    if (std::floor(value_) == value_ && std::abs(value_) < 1e15) {
        oss << static_cast<long long>(value_);
    } 
    else {
        oss << value_;
    }
    
    return oss.str();
}

double json_number::get_value() const {
    return value_;
}

bool json_number::operator==(const json_number& other) const {
    return value_ == other.value_;
}

bool json_number::operator!=(const json_number& other) const {
    return !(*this == other);
}
