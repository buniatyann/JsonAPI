#ifndef JSON_VALUE_HPP
#define JSON_VALUE_HPP

#include <string>
#include <memory>
#include <stdexcept>

enum class json_type {
    null,
    boolean,
    number,
    string,
    array,
    object
};

class json_null;
class json_boolean;
class json_number;
class json_string;
class json_array;
class json_object;

class json_value {
public:
    json_value();
    json_value(std::nullptr_t);
    json_value(bool value);
    json_value(int value);
    json_value(double value);
    json_value(const char* value);
    json_value(const std::string& value);
    json_value(std::string&& value);

    json_value(const json_value& other);
    json_value(json_value&& other) noexcept;
    json_value& operator=(const json_value& other);
    json_value& operator=(json_value&& other) noexcept;

    ~json_value();

    json_type type() const;
    std::string dump(int indent = -1, int current_indent = 0) const;
    json_value clone() const;

    bool operator==(const json_value& other) const;
    bool operator!=(const json_value& other) const;

    bool is_null() const;
    bool is_boolean() const;
    bool is_number() const;
    bool is_string() const;
    bool is_array() const;
    bool is_object() const;

    json_null& as_null();
    const json_null& as_null() const;
    json_boolean& as_boolean();
    const json_boolean& as_boolean() const;
    json_number& as_number();
    const json_number& as_number() const;
    json_string& as_string();
    const json_string& as_string() const;
    json_array& as_array();
    const json_array& as_array() const;
    json_object& as_object();
    const json_object& as_object() const;

    static json_value make_array();
    static json_value make_object();

private:
    struct impl;
    std::unique_ptr<impl> pimpl_;
};

#endif // JSON_VALUE_HPP
