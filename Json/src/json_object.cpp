#include "../include/json_object.hpp"
#include <sstream>

json_object::json_object() = default;

json_object::json_object(const object& values) {
    for (const auto& [key, val] : values) {
        std::visit([&](const auto& value) { 
            values_[key] = value; // Direct assignment since val is already the correct type
        }, val);
    }
}

json_object::json_object(const json_object& other) {
    for (const auto& [key, val] : other.values_) {
        std::visit([&](const auto& value) { 
            values_[key] = value; // Direct assignment for copy constructor
        }, val);
    }
}

json_object::json_object(json_object&& other) noexcept : values_(std::move(other.values_)) {}

json_object& json_object::operator=(const json_object& other) {
    if (this != &other) {
        values_.clear();
        for (const auto& [key, val] : other.values_) {
            std::visit([&](const auto& value) { 
                values_[key] = value; // Direct assignment for copy assignment
            }, val);
        }
    }
    
    return *this;
}

json_object& json_object::operator=(json_object&& other) noexcept {
    if (this != &other) {
        values_ = std::move(other.values_);
    }
    
    return *this;
}

json_object& json_object::operator=(std::unique_ptr<json_value>&& value) {
    if (!value || value->type() != json_type::object) {
        throw std::runtime_error("Cannot assign non-object value to json_object");
    }
    
    values_.clear();
    for (const auto& [key, val] : dynamic_cast<json_object&>(*value).values_) {
        std::visit([&](const auto& v) { 
            values_[key] = v; // Direct assignment
        }, val);
    }
    
    return *this;
}

std::string json_object::dump(int indent, int current_indent) const {
    std::ostringstream oss;
    if (indent >= 0) {
        oss << std::string(current_indent, ' ');
    }
    
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
    
        std::visit([&](const auto& val) {
            oss << val.dump(indent, indent >= 0 ? current_indent + indent : 0);
        }, value);
        if (i++ < values_.size() - 1) {
            oss << ",";
            if (indent >= 0) {
                oss << "\n";
            }
        }
    }
    
    if (indent >= 0 && !values_.empty()) {
        oss << "\n" << std::string(current_indent, ' ');
    }
    
    oss << "}";
    if (indent >= 0) {
        oss << "\n";
    }
    
    return oss.str();
}

std::unique_ptr<json_value> json_object::clone() const {
    return std::make_unique<json_object>(values_);
}

const json_object::object& json_object::get_values() const {
    return values_;
}

void json_object::set_value(const std::string& key, std::unique_ptr<json_value> value) {
    if (!value) {
        values_[key] = json_null();
        return;
    }
    switch (value->type()) {
        case json_type::null:
            values_[key] = dynamic_cast<json_null&>(*value);
            break;
        case json_type::boolean:
            values_[key] = dynamic_cast<json_boolean&>(*value);
            break;
        case json_type::number:
            values_[key] = dynamic_cast<json_number&>(*value);
            break;
        case json_type::string:
            values_[key] = dynamic_cast<json_string&>(*value);
            break;
        case json_type::array:
            values_[key] = dynamic_cast<json_array&>(*value);
            break;
        case json_type::object:
            values_[key] = dynamic_cast<json_object&>(*value);
            break;
    }
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
    
    return std::visit([](const auto& val) -> const json_value& { return val; }, it->second);
}