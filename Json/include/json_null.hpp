#ifndef JSON_NULL_HPP
#define JSON_NULL_HPP

#include "json_value.hpp"
#include <stdexcept>

class json_null : public json_value {
public:
    json_null() = default;
    json_null(const json_null& other) = default;
    json_null(json_null&& other) noexcept = default;
    json_null& operator=(const json_null& other) = default;
    json_null& operator=(json_null&& other) noexcept = default;
    json_null& operator=(std::unique_ptr<json_value>&& value) override;

    json_type type() const override { 
        return json_type::null; 
    }

    std::string dump(int indent = -1, int current_indent = 0) const override;
    std::unique_ptr<json_value> clone() const override;

    // Casting functions
    json_null& as_null() override {
        return *this;
    }
    const json_null& as_null() const override {
        return *this;
    }
    json_boolean& as_boolean() override {
        throw std::runtime_error("Cannot cast json_null to json_boolean");
    }
    const json_boolean& as_boolean() const override {
        throw std::runtime_error("Cannot cast json_null to json_boolean");
    }
    json_number& as_number() override {
        throw std::runtime_error("Cannot cast json_null to json_number");
    }
    const json_number& as_number() const override {
        throw std::runtime_error("Cannot cast json_null to json_number");
    }
    json_string& as_string() override {
        throw std::runtime_error("Cannot cast json_null to json_string");
    }
    const json_string& as_string() const override {
        throw std::runtime_error("Cannot cast json_null to json_string");
    }
    json_array& as_array() override {
        throw std::runtime_error("Cannot cast json_null to json_array");
    }
    const json_array& as_array() const override {
        throw std::runtime_error("Cannot cast json_null to json_array");
    }
    json_object& as_object() override {
        throw std::runtime_error("Cannot cast json_null to json_object");
    }
    const json_object& as_object() const override {
        throw std::runtime_error("Cannot cast json_null to json_object");
    }
};

#endif // JSON_NULL_HPP