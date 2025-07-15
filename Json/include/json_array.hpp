#ifndef JSON_ARRAY_HPP
#define JSON_ARRAY_HPP

#include "json_value.hpp"
#include "json_null.hpp"
#include "json_boolean.hpp"
#include "json_number.hpp"
#include "json_string.hpp"
#include "json_object.hpp"
#include <vector>
#include <stdexcept>

class json_array : public json_value {
public:
    using array = std::vector<std::unique_ptr<json_value>>;

    // Proxy class for operator[] to enable assignment
    class json_array_proxy {
    public:
        json_array_proxy(json_array& arr, size_t index) : arr_(arr), index_(index) {}

        json_array_proxy& operator=(const std::string& value) {
            arr_.set_element(index_, std::make_unique<json_string>(value));
            return *this;
        }

        json_array_proxy& operator=(double value) {
            arr_.set_element(index_, std::make_unique<json_number>(value));
            return *this;
        }

        json_array_proxy& operator=(bool value) {
            arr_.set_element(index_, std::make_unique<json_boolean>(value));
            return *this;
        }

        json_array_proxy& operator=(std::nullptr_t) {
            arr_.set_element(index_, std::make_unique<json_null>());
            return *this;
        }

        json_array_proxy& operator=(std::unique_ptr<json_value>&& value) {
            arr_.set_element(index_, std::move(value));
            return *this;
        }

        operator json_value&() {
            return arr_[index_];
        }

        operator const json_value&() const {
            return arr_[index_];
        }

    private:
        json_array& arr_;
        size_t index_;
    };

    json_array();
    json_array(const array& values);
    json_array(const json_array& other);
    json_array(json_array&& other) noexcept;
    json_array& operator=(const json_array& other);
    json_array& operator=(json_array&& other) noexcept;
    json_array& operator=(std::unique_ptr<json_value>&& value) override;

    json_type type() const override { 
        return json_type::array; 
    }

    std::string dump(int indent = -1, int current_indent = 0) const override;
    std::unique_ptr<json_value> clone() const override;

    const array& get_values() const;
    void add_value(std::unique_ptr<json_value> value);
    json_array_proxy operator[](size_t index);
    const json_value& operator[](size_t index) const;
    void set_element(size_t index, std::unique_ptr<json_value> value);

    // Casting functions
    json_null& as_null() override {
        throw std::runtime_error("Cannot cast json_array to json_null");
    }
    const json_null& as_null() const override {
        throw std::runtime_error("Cannot cast json_array to json_null");
    }
    json_boolean& as_boolean() override {
        throw std::runtime_error("Cannot cast json_array to json_boolean");
    }
    const json_boolean& as_boolean() const override {
        throw std::runtime_error("Cannot cast json_array to json_boolean");
    }
    json_number& as_number() override {
        throw std::runtime_error("Cannot cast json_array to json_number");
    }
    const json_number& as_number() const override {
        throw std::runtime_error("Cannot cast json_array to json_number");
    }
    json_string& as_string() override {
        throw std::runtime_error("Cannot cast json_array to json_string");
    }
    const json_string& as_string() const override {
        throw std::runtime_error("Cannot cast json_array to json_string");
    }
    json_array& as_array() override {
        return *this;
    }
    const json_array& as_array() const override {
        return *this;
    }
    json_object& as_object() override {
        throw std::runtime_error("Cannot cast json_array to json_object");
    }
    const json_object& as_object() const override {
        throw std::runtime_error("Cannot cast json_array to json_object");
    }

private:
    array values_;
};

#endif // JSON_ARRAY_HPP