#include "../include/json_number.hpp"

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

json_number& json_number::operator=(std::unique_ptr<json_value>&& value) {
    if (!value || value->type() != json_type::number) {
        throw std::runtime_error("Cannot assign non-number value to json_number");
    }
    value_ = dynamic_cast<json_number&>(*value).value_;
    return *this;
}

std::string json_number::dump(int indent, int current_indent) const {
    std::ostringstream oss;
    if (indent >= 0) {
        oss << std::string(current_indent, ' ');
    }
    oss << value_;
    if (indent >= 0) {
        oss << "\n";
    }
    return oss.str();
}

std::unique_ptr<json_value> json_number::clone() const {
    return std::make_unique<json_number>(value_);
}