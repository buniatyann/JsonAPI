#ifndef JSON_ARRAY_HPP
#define JSON_ARRAY_HPP

#include "json_value.hpp"
#include <vector>

class json_object;

class json_array {
public:
    using array = std::vector<json_value>;
    using iterator = array::iterator;
    using const_iterator = array::const_iterator;

    class json_array_proxy {
    public:
        json_array_proxy(json_array& arr, size_t index);

        json_array_proxy& operator=(const std::string& value);
        json_array_proxy& operator=(const char* value);
        json_array_proxy& operator=(double value);
        json_array_proxy& operator=(int value);
        json_array_proxy& operator=(bool value);
        json_array_proxy& operator=(std::nullptr_t);
        json_array_proxy& operator=(const json_value& value);
        json_array_proxy& operator=(json_value&& value);

        operator json_value&();
        operator const json_value&() const;

        operator std::string() const;
        operator double() const;
        operator int() const;
        operator bool() const;

        json_value& as_value();
        const json_value& as_value() const;

    private:
        json_array& arr_;
        size_t index_;
    };

    json_array();
    json_array(const array& values);
    json_array(std::initializer_list<json_value> values);
    json_array(const json_array& other);
    json_array(json_array&& other) noexcept;
    json_array& operator=(const json_array& other);
    json_array& operator=(json_array&& other) noexcept;

    std::string dump(int indent = -1, int current_indent = 0) const;

    const array& get_values() const;
    void add_value(const json_value& value);
    void add_value(json_value&& value);
    json_array_proxy operator[](size_t index);
    const json_value& operator[](size_t index) const;
    void set_element(size_t index, const json_value& value);
    void set_element(size_t index, json_value&& value);

    size_t size() const;
    bool empty() const;
    void clear();
    void push_back(const json_value& value);
    void push_back(json_value&& value);

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

    bool operator==(const json_array& other) const;
    bool operator!=(const json_array& other) const;

private:
    array values_;
};

#endif // JSON_ARRAY_HPP
