#include "../../include/types/json_string.hpp"
#include <sstream>

json_string::json_string(const std::string& value) : value_(value) {}

json_string::json_string(std::string&& value) : value_(std::move(value)) {}

json_string::json_string(const char* value) : value_(value) {}

json_string::json_string(const json_string& other) : value_(other.value_) {}

json_string::json_string(json_string&& other) noexcept : value_(std::move(other.value_)) {}

json_string& json_string::operator=(const json_string& other) {
    if (this != &other) {
        value_ = other.value_;
    }

    return *this;
}

json_string& json_string::operator=(json_string&& other) noexcept {
    if (this != &other) {
        value_ = std::move(other.value_);
    }
    
    return *this;
}

std::string json_string::dump(int indent, int current_indent) const {
    std::ignore = indent;
    std::ignore = current_indent;
    std::ostringstream oss;
    oss << "\"";
    for (char c : value_) {
        switch (c) {
            case '"': oss << "\\\""; break;
            case '\\': oss << "\\\\"; break;
            case '\b': oss << "\\b"; break;
            case '\f': oss << "\\f"; break;
            case '\n': oss << "\\n"; break;
            case '\r': oss << "\\r"; break;
            case '\t': oss << "\\t"; break;
            default: oss << c; break;
        }
    }
    
    oss << "\"";
    return oss.str();
}

std::string json_string::get_value() const {
    return value_;
}

bool json_string::operator==(const json_string& other) const {
    return value_ == other.value_;
}

bool json_string::operator!=(const json_string& other) const {
    return !(*this == other);
}
