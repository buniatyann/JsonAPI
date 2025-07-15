#ifndef JSON_STRING_HPP
#define JSON_STRING_HPP

#include "json_value.hpp"
#include <string>
#include <sstream>

class json_string : public json_value {
public:
    json_string(const std::string& value);
    json_string(const json_string& other);
    json_string(json_string&& other) noexcept;
    json_string& operator=(const json_string& other);
    json_string& operator=(json_string&& other) noexcept;
    json_string& operator=(std::unique_ptr<json_value>&& value) override;

    json_type type() const override { 
        return json_type::string; 
    }

    std::string dump(int indent = -1, int current_indent = 0) const override;
    std::unique_ptr<json_value> clone() const override;

    std::string get_value() const { 
        return value_; 
    }

    // Casting functions
    json_null& as_null() override {
        throw std::runtime_error("Cannot cast json_string to json_null");
    }
    const json_null& as_null() const override {
        throw std::runtime_error("Cannot cast json_string to json_null");
    }
    json_boolean& as_boolean() override {
        throw std::runtime_error("Cannot cast json_string to json_boolean");
    }
    const json_boolean& as_boolean() const override {
        throw std::runtime_error("Cannot cast json_string to json_boolean");
    }
    json_number& as_number() override {
        throw std::runtime_error("Cannot cast json_string to json_number");
    }
    const json_number& as_number() const override {
        throw std::runtime_error("Cannot cast json_string to json_number");
    }
    json_string& as_string() override {
        return *this;
    }
    const json_string& as_string() const override {
        return *this;
    }
    json_array& as_array() override {
        throw std::runtime_error("Cannot cast json_string to json_array");
    }
    const json_array& as_array() const override {
        throw std::runtime_error("Cannot cast json_string to json_array");
    }
    json_object& as_object() override {
        throw std::runtime_error("Cannot cast json_string to json_object");
    }
    const json_object& as_object() const override {
        throw std::runtime_error("Cannot cast json_string to json_object");
    }

private:
    std::string value_;
};
#endif // JSON_STRING_HPP