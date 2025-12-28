#ifndef JSON_NULL_HPP
#define JSON_NULL_HPP

#include <string>

class json_null {
public:
    json_null() = default;
    json_null(const json_null& other) = default;
    json_null(json_null&& other) noexcept = default;
    json_null& operator=(const json_null& other) = default;
    json_null& operator=(json_null&& other) noexcept = default;

    std::string dump(int indent = -1, int current_indent = 0) const;

    bool operator==(const json_null& other) const;
    bool operator!=(const json_null& other) const;
};

#endif // JSON_NULL_HPP
