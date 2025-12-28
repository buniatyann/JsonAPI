#ifndef JSON_API_HPP
#define JSON_API_HPP

#include "types/json_value.hpp"
#include "types/json_null.hpp"
#include "types/json_boolean.hpp"
#include "types/json_number.hpp"
#include "types/json_string.hpp"
#include "types/json_array.hpp"
#include "types/json_object.hpp"
#include <string>

class json {
public:
    json();
    json(const std::string& file_path);
    json(const json& other);
    json(json&& other) noexcept;
    json& operator=(const json& other);
    json& operator=(json&& other) noexcept;

    static json parse(const std::string& json_string);
    static json object();
    static json array();

    json_value& get_json();
    const json_value& get_json() const;

    std::string get_context(int indent = -1) const;
    void write_file(const std::string& file_path, int indent = 2) const;

private:
    json_value json_data_;
};

#endif // JSON_API_HPP
