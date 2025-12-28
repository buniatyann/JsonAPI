#ifndef JSON_STRING_HPP
#define JSON_STRING_HPP

#include <string>

class json_string {
public:
    json_string(const std::string& value = "");
    json_string(std::string&& value);
    json_string(const char* value);
    json_string(const json_string& other);
    json_string(json_string&& other) noexcept;
    json_string& operator=(const json_string& other);
    json_string& operator=(json_string&& other) noexcept;

    std::string dump(int indent = -1, int current_indent = 0) const;

    std::string get_value() const;

    bool operator==(const json_string& other) const;
    bool operator!=(const json_string& other) const;

private:
    std::string value_;
};

#endif // JSON_STRING_HPP
