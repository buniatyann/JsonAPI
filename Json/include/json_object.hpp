#ifndef JSON_OBJECT_HPP
#define JSON_OBJECT_HPP

#include "json_value.hpp"
#include "json_null.hpp"
#include "json_boolean.hpp"
#include "json_number.hpp"
#include "json_string.hpp"
#include "json_array.hpp"
#include <unordered_map>
#include <variant>
#include <stdexcept>

#include "json_value.hpp"
#include "json_null.hpp"
#include "json_boolean.hpp"
#include "json_number.hpp"
#include "json_string.hpp"
#include "json_array.hpp"
#include <unordered_map>
#include <variant>
#include <stdexcept>

class json_object : public json_value {
public:
    using variant_t = std::variant<json_null, json_boolean, json_number, json_string, json_array, json_object>;
    using object = std::unordered_map<std::string, variant_t>;

    // Proxy class for operator[] to enable assignment
    class json_object_proxy {
    public:
        json_object_proxy(json_object& obj, const std::string& key) : obj_(obj), key_(key) {}

        json_object_proxy& operator=(const std::string& value) {
            obj_.values_[key_] = json_string(value);
            return *this;
        }

        json_object_proxy& operator=(double value) {
            obj_.values_[key_] = json_number(value);
            return *this;
        }

        json_object_proxy& operator=(bool value) {
            obj_.values_[key_] = json_boolean(value);
            return *this;
        }

        json_object_proxy& operator=(std::nullptr_t) {
            obj_.values_[key_] = json_null();
            return *this;
        }

        json_object_proxy& operator=(std::unique_ptr<json_value>&& value) {
            obj_.set_value(key_, std::move(value));
            return *this;
        }

        operator json_value&() {
            return obj_[key_];
        }

        operator const json_value&() const {
            return obj_[key_];
        }

    private:
        json_object& obj_;
        std::string key_;
    };

    json_object();
    json_object(const object& values);
    json_object(const json_object& other);
    json_object(json_object&& other) noexcept;
    json_object& operator=(const json_object& other);
    json_object& operator=(json_object&& other) noexcept;
    json_object& operator=(std::unique_ptr<json_value>&& value) override;

    json_type type() const override { 
        return json_type::object; 
    }

    std::string dump(int indent = -1, int current_indent = 0) const override;
    std::unique_ptr<json_value> clone() const override;

    const object& get_values() const;
    void set_value(const std::string& key, std::unique_ptr<json_value> value);
    bool has_key(const std::string& key) const;
    void remove_key(const std::string& key);
    json_object_proxy operator[](const std::string& key);
    const json_value& operator[](const std::string& key) const;

    // Casting functions
    json_null& as_null() override {
        throw std::runtime_error("Cannot cast json_object to json_null");
    }
    const json_null& as_null() const override {
        throw std::runtime_error("Cannot cast json_object to json_null");
    }
    json_boolean& as_boolean() override {
        throw std::runtime_error("Cannot cast json_object to json_boolean");
    }
    const json_boolean& as_boolean() const override {
        throw std::runtime_error("Cannot cast json_object to json_boolean");
    }
    json_number& as_number() override {
        throw std::runtime_error("Cannot cast json_object to json_number");
    }
    const json_number& as_number() const override {
        throw std::runtime_error("Cannot cast json_object to json_number");
    }
    json_string& as_string() override {
        throw std::runtime_error("Cannot cast json_object to json_string");
    }
    const json_string& as_string() const override {
        throw std::runtime_error("Cannot cast json_object to json_string");
    }
    json_array& as_array() override {
        throw std::runtime_error("Cannot cast json_object to json_array");
    }
    const json_array& as_array() const override {
        throw std::runtime_error("Cannot cast json_object to json_array");
    }
    json_object& as_object() override {
        return *this;
    }
    const json_object& as_object() const override {
        return *this;
    }

private:
    object values_;
};


#endif // JSON_OBJECT_HPP