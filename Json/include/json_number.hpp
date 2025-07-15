#ifndef JSON_NUMBER_HPP
#define JSON_NUMBER_HPP

#include "json_value.hpp"
#include <sstream>
#include <iomanip>
#include <stdexcept>

class json_number : public json_value {
public:
    json_number(double value);
    json_number(const json_number& other);
    json_number(json_number&& other) noexcept;
    json_number& operator=(const json_number& other);
    json_number& operator=(json_number&& other) noexcept;
    json_number& operator=(std::unique_ptr<json_value>&& value) override;

    json_type type() const override { 
        return json_type::number; 
    }

    std::string dump(int indent = -1, int current_indent = 0) const override;
    std::unique_ptr<json_value> clone() const override;

    double get_value() const { 
        return value_; 
    }

    // Casting functions
    json_null& as_null() override {
        throw std::runtime_error("Cannot cast json_number to json_null");
    }
    const json_null& as_null() const override {
        throw std::runtime_error("Cannot cast json_number to json_null");
    }
    json_boolean& as_boolean() override {
        throw std::runtime_error("Cannot cast json_number to json_boolean");
    }
    const json_boolean& as_boolean() const override {
        throw std::runtime_error("Cannot cast json_number to json_boolean");
    }
    json_number& as_number() override {
        return *this;
    }
    const json_number& as_number() const override {
        return *this;
    }
    json_string& as_string() override {
        throw std::runtime_error("Cannot cast json_number to json_string");
    }
    const json_string& as_string() const override {
        throw std::runtime_error("Cannot cast json_number to json_string");
    }
    json_array& as_array() override {
        throw std::runtime_error("Cannot cast json_number to json_array");
    }
    const json_array& as_array() const override {
        throw std::runtime_error("Cannot cast json_number to json_array");
    }
    json_object& as_object() override {
        throw std::runtime_error("Cannot cast json_number to json_object");
    }
    const json_object& as_object() const override {
        throw std::runtime_error("Cannot cast json_number to json_object");
    }

private:
    double value_;
};


#endif // JSON_NUMBER_HPP