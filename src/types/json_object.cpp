#include "../../include/types/json_object.hpp"
#include "../../include/types/json_null.hpp"
#include "../../include/types/json_boolean.hpp"
#include "../../include/types/json_number.hpp"
#include "../../include/types/json_string.hpp"
#include "../../include/types/json_array.hpp"
#include <sstream>
#include <stdexcept>

// json_object_proxy implementations
json_object::json_object_proxy::json_object_proxy(json_object& obj, const std::string& key)
    : obj_(obj), key_(key) {}

json_object::json_object_proxy& json_object::json_object_proxy::operator=(const std::string& value) {
    obj_.values_[key_] = json_value(value);
    return *this;
}

json_object::json_object_proxy& json_object::json_object_proxy::operator=(const char* value) {
    obj_.values_[key_] = json_value(value);
    return *this;
}

json_object::json_object_proxy& json_object::json_object_proxy::operator=(double value) {
    obj_.values_[key_] = json_value(value);
    return *this;
}

json_object::json_object_proxy& json_object::json_object_proxy::operator=(int value) {
    obj_.values_[key_] = json_value(value);
    return *this;
}

json_object::json_object_proxy& json_object::json_object_proxy::operator=(bool value) {
    obj_.values_[key_] = json_value(value);
    return *this;
}

json_object::json_object_proxy& json_object::json_object_proxy::operator=(std::nullptr_t) {
    obj_.values_[key_] = json_value(nullptr);
    return *this;
}

json_object::json_object_proxy& json_object::json_object_proxy::operator=(const json_value& value) {
    obj_.values_[key_] = value;
    return *this;
}

json_object::json_object_proxy& json_object::json_object_proxy::operator=(json_value&& value) {
    obj_.values_[key_] = std::move(value);
    return *this;
}

json_object::json_object_proxy::operator json_value&() {
    return obj_.values_[key_];
}

json_object::json_object_proxy::operator const json_value&() const {
    auto it = obj_.values_.find(key_);
    if (it == obj_.values_.end()) {
        throw std::out_of_range("Key not found: " + key_);
    }
    
    return it->second;
}

json_object::json_object_proxy::operator std::string() const {
    return static_cast<const json_value&>(*this).as_string().get_value();
}

json_object::json_object_proxy::operator double() const {
    return static_cast<const json_value&>(*this).as_number().get_value();
}

json_object::json_object_proxy::operator int() const {
    return static_cast<int>(static_cast<const json_value&>(*this).as_number().get_value());
}

json_object::json_object_proxy::operator bool() const {
    return static_cast<const json_value&>(*this).as_boolean().get_value();
}

json_value& json_object::json_object_proxy::as_value() {
    return obj_.values_[key_];
}

const json_value& json_object::json_object_proxy::as_value() const {
    auto it = obj_.values_.find(key_);
    if (it == obj_.values_.end()) {
        throw std::out_of_range("Key not found: " + key_);
    }
    
    return it->second;
}

json_object::json_object_proxy json_object::json_object_proxy::operator[](const std::string& key) {
    json_value& val = obj_.values_[key_];
    if (!val.is_object()) {
        val = json_value::make_object();
    }
    
    return json_object_proxy(val.as_object(), key);
}

json_object::json_object_proxy json_object::json_object_proxy::operator[](size_t index) {
    std::ignore = index;
    json_value& val = obj_.values_[key_];
    if (!val.is_array()) {
        val = json_value::make_array();
    }

    return json_object_proxy(obj_, key_);
}

// json_object implementations
json_object::json_object() = default;

json_object::json_object(const object& values) : values_(values) {}

json_object::json_object(std::initializer_list<std::pair<std::string, json_value>> values) {
    for (const auto& [key, val] : values) {
        values_[key] = val;
    }
}

json_object::json_object(const json_object& other) : values_(other.values_) {}

json_object::json_object(json_object&& other) noexcept : values_(std::move(other.values_)) {}

json_object& json_object::operator=(const json_object& other) {
    if (this != &other) {
        values_ = other.values_;
    }
    
    return *this;
}

json_object& json_object::operator=(json_object&& other) noexcept {
    if (this != &other) {
        values_ = std::move(other.values_);
    }
    
    return *this;
}

std::string json_object::dump(int indent, int current_indent) const {
    std::ostringstream oss;
    oss << "{";
    if (indent >= 0 && !values_.empty()) {
        oss << "\n";
    }

    size_t i = 0;
    for (const auto& [key, value] : values_) {
        if (indent >= 0) {
            oss << std::string(current_indent + indent, ' ');
        }

        oss << "\"" << key << "\":";
        if (indent >= 0) {
            oss << " ";
        }

        oss << value.dump(indent, current_indent + indent);
        if (i++ < values_.size() - 1) {
            oss << ",";
        }

        if (indent >= 0) {
            oss << "\n";
        }
    }

    if (indent >= 0 && !values_.empty()) {
        oss << std::string(current_indent, ' ');
    }

    oss << "}";
    return oss.str();
}

const json_object::object& json_object::get_values() const {
    return values_;
}

void json_object::set_value(const std::string& key, const json_value& value) {
    values_[key] = value;
}

void json_object::set_value(const std::string& key, json_value&& value) {
    values_[key] = std::move(value);
}

bool json_object::has_key(const std::string& key) const {
    return values_.find(key) != values_.end();
}

void json_object::remove_key(const std::string& key) {
    values_.erase(key);
}

json_object::json_object_proxy json_object::operator[](const std::string& key) {
    return json_object_proxy(*this, key);
}

const json_value& json_object::operator[](const std::string& key) const {
    auto it = values_.find(key);
    if (it == values_.end()) {
        throw std::out_of_range("Key not found: " + key);
    }

    return it->second;
}

size_t json_object::size() const {
    return values_.size();
}

bool json_object::empty() const {
    return values_.empty();
}

void json_object::clear() {
    values_.clear();
}

bool json_object::contains(const std::string& key) const {
    return has_key(key);
}

void json_object::erase(const std::string& key) {
    remove_key(key);
}

json_object::iterator json_object::begin() {
    return values_.begin();
}

json_object::iterator json_object::end() {
    return values_.end();
}

json_object::const_iterator json_object::begin() const {
    return values_.begin();
}

json_object::const_iterator json_object::end() const {
    return values_.end();
}

json_object::const_iterator json_object::cbegin() const {
    return values_.cbegin();
}

json_object::const_iterator json_object::cend() const {
    return values_.cend();
}

bool json_object::operator==(const json_object& other) const {
    if (values_.size() != other.values_.size()) {
        return false;
    }

    for (const auto& [key, val] : values_) {
        auto it = other.values_.find(key);
        if (it == other.values_.end()) {
            return false;
        }

        if (val != it->second) {
            return false;
        }
    }

    return true;
}

bool json_object::operator!=(const json_object& other) const {
    return !(*this == other);
}
