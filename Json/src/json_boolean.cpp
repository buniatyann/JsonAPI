#include "../include/json_boolean.hpp"

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

json_boolean& json_boolean::operator=(std::unique_ptr<json_value>&& value) {
    if (!value || value->type() != json_type::boolean) {
        throw std::runtime_error("Cannot assign non-boolean value to json_boolean");
    }
    value_ = dynamic_cast<json_boolean&>(*value).value_;
    return *this;
}

std::string json_boolean::dump(int indent, int current_indent) const {
    std::string result = indent >= 0 ? std::string(current_indent, ' ') + (value_ ? "true" : "false") : (value_ ? "true" : "false");
    if (indent >= 0) {
        result += "\n";
    }
    return result;
}

std::unique_ptr<json_value> json_boolean::clone() const {
    return std::make_unique<json_boolean>(value_);
}