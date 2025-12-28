#ifndef JSON_NUMBER_HPP
#define JSON_NUMBER_HPP

#include <string>

class json_number {
public:
    json_number(double value = 0.0);
    json_number(const json_number& other);
    json_number(json_number&& other) noexcept;
    json_number& operator=(const json_number& other);
    json_number& operator=(json_number&& other) noexcept;

    std::string dump(int indent = -1, int current_indent = 0) const;

    double get_value() const;

    bool operator==(const json_number& other) const;
    bool operator!=(const json_number& other) const;

private:
    double value_;
};

#endif // JSON_NUMBER_HPP
