#ifndef JSON_OBJECT_HPP
#define JSON_OBJECT_HPP

#include "json_value.hpp"
#include <unordered_map>

class json_object {
public:
    using object = std::unordered_map<std::string, json_value>;
    using iterator = object::iterator;
    using const_iterator = object::const_iterator;

    class json_object_proxy {
    public:
        json_object_proxy(json_object& obj, const std::string& key);

        json_object_proxy& operator=(const std::string& value);
        json_object_proxy& operator=(const char* value);
        json_object_proxy& operator=(double value);
        json_object_proxy& operator=(int value);
        json_object_proxy& operator=(bool value);
        json_object_proxy& operator=(std::nullptr_t);
        json_object_proxy& operator=(const json_value& value);
        json_object_proxy& operator=(json_value&& value);

        operator json_value&();
        operator const json_value&() const;

        operator std::string() const;
        operator double() const;
        operator int() const;
        operator bool() const;

        json_value& as_value();
        const json_value& as_value() const;

        json_object_proxy operator[](const std::string& key);
        json_object_proxy operator[](size_t index);

    private:
        json_object& obj_;
        std::string key_;
    };

    json_object();
    json_object(const object& values);
    json_object(std::initializer_list<std::pair<std::string, json_value>> values);
    json_object(const json_object& other);
    json_object(json_object&& other) noexcept;
    json_object& operator=(const json_object& other);
    json_object& operator=(json_object&& other) noexcept;

    std::string dump(int indent = -1, int current_indent = 0) const;

    const object& get_values() const;
    void set_value(const std::string& key, const json_value& value);
    void set_value(const std::string& key, json_value&& value);
    bool has_key(const std::string& key) const;
    void remove_key(const std::string& key);
    json_object_proxy operator[](const std::string& key);
    const json_value& operator[](const std::string& key) const;

    size_t size() const;
    bool empty() const;
    void clear();
    bool contains(const std::string& key) const;
    void erase(const std::string& key);

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

    bool operator==(const json_object& other) const;
    bool operator!=(const json_object& other) const;

private:
    object values_;
};

#endif // JSON_OBJECT_HPP
