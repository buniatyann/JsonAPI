#include "../../include/types/json_array.hpp"
#include "../../include/types/json_null.hpp"
#include "../../include/types/json_boolean.hpp"
#include "../../include/types/json_number.hpp"
#include "../../include/types/json_string.hpp"
#include "../../include/types/json_object.hpp"
#include <sstream>
#include <stdexcept>

// json_array_proxy implementations
json_array::json_array_proxy::json_array_proxy(json_array& arr, size_t index)
    : arr_(arr), index_(index) {}

json_array::json_array_proxy& json_array::json_array_proxy::operator=(const std::string& value) {
    arr_.set_element(index_, json_value(value));
    return *this;
}

json_array::json_array_proxy& json_array::json_array_proxy::operator=(const char* value) {
    arr_.set_element(index_, json_value(value));
    return *this;
}

json_array::json_array_proxy& json_array::json_array_proxy::operator=(double value) {
    arr_.set_element(index_, json_value(value));
    return *this;
}

json_array::json_array_proxy& json_array::json_array_proxy::operator=(int value) {
    arr_.set_element(index_, json_value(value));
    return *this;
}

json_array::json_array_proxy& json_array::json_array_proxy::operator=(bool value) {
    arr_.set_element(index_, json_value(value));
    return *this;
}

json_array::json_array_proxy& json_array::json_array_proxy::operator=(std::nullptr_t) {
    arr_.set_element(index_, json_value(nullptr));
    return *this;
}

json_array::json_array_proxy& json_array::json_array_proxy::operator=(const json_value& value) {
    arr_.set_element(index_, value);
    return *this;
}

json_array::json_array_proxy& json_array::json_array_proxy::operator=(json_value&& value) {
    arr_.set_element(index_, std::move(value));
    return *this;
}

json_array::json_array_proxy::operator json_value&() {
    return arr_.values_[index_];
}

json_array::json_array_proxy::operator const json_value&() const {
    return arr_.values_[index_];
}

json_array::json_array_proxy::operator std::string() const {
    return arr_.values_[index_].as_string().get_value();
}

json_array::json_array_proxy::operator double() const {
    return arr_.values_[index_].as_number().get_value();
}

json_array::json_array_proxy::operator int() const {
    return static_cast<int>(arr_.values_[index_].as_number().get_value());
}

json_array::json_array_proxy::operator bool() const {
    return arr_.values_[index_].as_boolean().get_value();
}

json_value& json_array::json_array_proxy::as_value() {
    return arr_.values_[index_];
}

const json_value& json_array::json_array_proxy::as_value() const {
    return arr_.values_[index_];
}

// json_array implementations
json_array::json_array() = default;

json_array::json_array(const array& values) : values_(values) {}

json_array::json_array(std::initializer_list<json_value> values) : values_(values) {}

json_array::json_array(const json_array& other) : values_(other.values_) {}

json_array::json_array(json_array&& other) noexcept : values_(std::move(other.values_)) {}

json_array& json_array::operator=(const json_array& other) {
    if (this != &other) {
        values_ = other.values_;
    }

    return *this;
}

json_array& json_array::operator=(json_array&& other) noexcept {
    if (this != &other) {
        values_ = std::move(other.values_);
    }
    
    return *this;
}

std::string json_array::dump(int indent, int current_indent) const {
    std::ostringstream oss;
    oss << "[";

    if (indent >= 0 && !values_.empty()) {
        oss << "\n";
    }

    for (size_t i = 0; i < values_.size(); ++i) {
        if (indent >= 0) {
            oss << std::string(current_indent + indent, ' ');
        }

        oss << values_[i].dump(indent, current_indent + indent);
        if (i < values_.size() - 1) {
            oss << ",";
        }

        if (indent >= 0) {
            oss << "\n";
        }
    }

    if (indent >= 0 && !values_.empty()) {
        oss << std::string(current_indent, ' ');
    }

    oss << "]";
    return oss.str();
}

const json_array::array& json_array::get_values() const {
    return values_;
}

void json_array::add_value(const json_value& value) {
    values_.push_back(value);
}

void json_array::add_value(json_value&& value) {
    values_.push_back(std::move(value));
}

json_array::json_array_proxy json_array::operator[](size_t index) {
    while (index >= values_.size()) {
        values_.push_back(json_value(nullptr));
    }

    return json_array_proxy(*this, index);
}

const json_value& json_array::operator[](size_t index) const {
    if (index >= values_.size()) {
        throw std::out_of_range("Index out of range: " + std::to_string(index));
    }

    return values_[index];
}

void json_array::set_element(size_t index, const json_value& value) {
    while (index >= values_.size()) {
        values_.push_back(json_value(nullptr));
    }
    values_[index] = value;
}

void json_array::set_element(size_t index, json_value&& value) {
    while (index >= values_.size()) {
        values_.push_back(json_value(nullptr));
    }

    values_[index] = std::move(value);
}

size_t json_array::size() const {
    return values_.size();
}

bool json_array::empty() const {
    return values_.empty();
}

void json_array::clear() {
    values_.clear();
}

void json_array::push_back(const json_value& value) {
    values_.push_back(value);
}

void json_array::push_back(json_value&& value) {
    values_.push_back(std::move(value));
}

json_array::iterator json_array::begin() {
    return values_.begin();
}

json_array::iterator json_array::end() {
    return values_.end();
}

json_array::const_iterator json_array::begin() const {
    return values_.begin();
}

json_array::const_iterator json_array::end() const {
    return values_.end();
}

json_array::const_iterator json_array::cbegin() const {
    return values_.cbegin();
}

json_array::const_iterator json_array::cend() const {
    return values_.cend();
}

bool json_array::operator==(const json_array& other) const {
    if (values_.size() != other.values_.size()) {
        return false;
    }
    
    for (size_t i = 0; i < values_.size(); ++i) {
        if (values_[i] != other.values_[i]) {
            return false;
        }
    }

    return true;
}

bool json_array::operator!=(const json_array& other) const {
    return !(*this == other);
}
