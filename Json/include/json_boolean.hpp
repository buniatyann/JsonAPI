#ifndef JSON_BOOL_HPP
#define JSON_BOOL_HPP

#include "json_value.hpp"
#include <stdexcept>

class json_boolean : public json_value {
public:
    json_boolean(bool value);
    json_boolean(const json_boolean& other);
    json_boolean(json_boolean&& other) noexcept;
    json_boolean& operator=(const json_boolean& other);
    json_boolean& operator=(json_boolean&& other) noexcept;
    json_boolean& operator=(std::unique_ptr<json_value>&& value) override;

    json_type type() const override { 
        return json_type::boolean; 
    }

    std::string dump(int indent = -1, int current_indent = 0) const override;
    std::unique_ptr<json_value> clone() const override;

    bool get_value() const { 
        return value_; 
    }

    // Casting functions
    json_null& as_null() override {
        throw std::runtime_error("Cannot cast json_boolean to json_null");
    }
    const json_null& as_null() const override {
        throw std::runtime_error("Cannot cast json_boolean to json_null");
    }
    json_boolean& as_boolean() override {
        return *this;
    }
    const json_boolean& as_boolean() const override {
        return *this;
    }
    json_number& as_number() override {
        throw std::runtime_error("Cannot cast json_boolean to json_number");
    }
    const json_number& as_number() const override {
        throw std::runtime_error("Cannot cast json_boolean to json_number");
    }
    json_string& as_string() override {
        throw std::runtime_error("Cannot cast json_boolean to json_string");
    }
    const json_string& as_string() const override {
        throw std::runtime_error("Cannot cast json_boolean to json_string");
    }
    json_array& as_array() override {
        throw std::runtime_error("Cannot cast json_boolean to json_array");
    }
    const json_array& as_array() const override {
        throw std::runtime_error("Cannot cast json_boolean to json_array");
    }
    json_object& as_object() override {
        throw std::runtime_error("Cannot cast json_boolean to json_object");
    }
    const json_object& as_object() const override {
        throw std::runtime_error("Cannot cast json_boolean to json_object");
    }

private:
    bool value_;
};

#endif // JSON_BOOL_HPP