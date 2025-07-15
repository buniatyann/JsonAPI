#ifndef JSON_VALUE_HPP
#define JSON_VALUE_HPP

#include <string>
#include <memory>

class json_value;
class json_null;
class json_boolean;
class json_number;
class json_string;
class json_array;
class json_object;

enum class json_type {
    null,
    boolean,
    number,
    string,
    array,
    object
};

class json_value {
public:
    virtual ~json_value() = default;
    virtual json_type type() const = 0;
    virtual std::string dump(int indent = -1, int current_indent = 0) const = 0;
    virtual std::unique_ptr<json_value> clone() const = 0;
    virtual json_value& operator=(std::unique_ptr<json_value>&& value) = 0;

    bool is_null() const { return type() == json_type::null; }
    bool is_boolean() const { return type() == json_type::boolean; }
    bool is_number() const { return type() == json_type::number; }
    bool is_string() const { return type() == json_type::string; }
    bool is_array() const { return type() == json_type::array; }
    bool is_object() const { return type() == json_type::object; }

    // Pure virtual casting functions
    virtual json_null& as_null() = 0;
    virtual const json_null& as_null() const = 0;
    virtual json_boolean& as_boolean() = 0;
    virtual const json_boolean& as_boolean() const = 0;
    virtual json_number& as_number() = 0;
    virtual const json_number& as_number() const = 0;
    virtual json_string& as_string() = 0;
    virtual const json_string& as_string() const = 0;
    virtual json_array& as_array() = 0;
    virtual const json_array& as_array() const = 0;
    virtual json_object& as_object() = 0;
    virtual const json_object& as_object() const = 0;
};

#endif // JSON_VALUE_HPP