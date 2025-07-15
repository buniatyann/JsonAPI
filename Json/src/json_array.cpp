#include "json_array.hpp"
#include <sstream>

json_array::json_array() = default;

json_array::json_array(const array& values) {
    for (const auto& val : values) {
        add_value(val->clone());
    }
}

json_array::json_array(const json_array& other) {
    for (const auto& val : other.values_) {
        add_value(val->clone());
    }
}

json_array::json_array(json_array&& other) noexcept : values_(std::move(other.values_)) {}

json_array& json_array::operator=(const json_array& other) {
    if (this != &other) {
        values_.clear();
        for (const auto& val : other.values_) {
            add_value(val->clone());
        }
    }
    
    return *this;
}

json_array& json_array::operator=(json_array&& other) noexcept {
    if (this != &other) {
        values_ = std::move(other.values_);
    }
    
    return *this;
}

json_array& json_array::operator=(std::unique_ptr<json_value>&& value) {
    if (!value || value->type() != json_type::array) {
        throw std::runtime_error("Cannot assign non-array value to json_array");
    }
    
    values_.clear();
    for (const auto& val : dynamic_cast<json_array&>(*value).values_) {
        add_value(val->clone());
    }
    
    return *this;
}

std::string json_array::dump(int indent, int current_indent) const {
    std::ostringstream oss;
    if (indent >= 0) {
        oss << std::string(current_indent, ' ');
    }
    
    oss << "[";
    if (indent >= 0 && !values_.empty()) {
        oss << "\n";
    }
    
    for (size_t i = 0; i < values_.size(); ++i) {
        if (indent >= 0) {
            oss << std::string(current_indent + indent, ' ');
        }
    
        oss << values_[i]->dump(indent, indent >= 0 ? current_indent + indent : 0);
        if (i < values_.size() - 1) {
            oss << ",";
            if (indent >= 0) {
                oss << "\n";
            }
        }
    }
    
    if (indent >= 0 && !values_.empty()) {
        oss << "\n" << std::string(current_indent, ' ');
    }
    
    oss << "]";
    if (indent >= 0) {
        oss << "\n";
    }
    
    return oss.str();
}

std::unique_ptr<json_value> json_array::clone() const {
    return std::make_unique<json_array>(values_);
}

const json_array::array& json_array::get_values() const {
    return values_;
}

void json_array::add_value(std::unique_ptr<json_value> value) {
    values_.push_back(std::move(value));
}

json_array::json_array_proxy json_array::operator[](size_t index) {
    if (index >= values_.size()) {
        values_.resize(index + 1, std::make_unique<json_null>());
    }
    
    return json_array_proxy(*this, index);
}

const json_value& json_array::operator[](size_t index) const {
    if (index >= values_.size()) {
        throw std::out_of_range("Index out of range: " + std::to_string(index));
    }
    
    return *values_[index];
}

void json_array::set_element(size_t index, std::unique_ptr<json_value> value) {
    if (index >= values_.size()) {
        values_.resize(index + 1, std::make_unique<json_null>());
    }
    
    values_[index] = std::move(value);
}