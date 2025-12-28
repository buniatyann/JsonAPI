#ifndef JSON_BOOL_HPP
#define JSON_BOOL_HPP

#include <string>

class json_boolean {
public:
    json_boolean(bool value = false);
    json_boolean(const json_boolean& other);
    json_boolean(json_boolean&& other) noexcept;
    json_boolean& operator=(const json_boolean& other);
    json_boolean& operator=(json_boolean&& other) noexcept;

    std::string dump(int indent = -1, int current_indent = 0) const;

    bool get_value() const;

    bool operator==(const json_boolean& other) const;
    bool operator!=(const json_boolean& other) const;

private:
    bool value_;
};

#endif // JSON_BOOL_HPP
