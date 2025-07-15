#ifndef JSON_API_HPP
#define JSON_API_HPP

#include "parser.hpp"
#include "json_value.hpp"
#include "json_object.hpp"
#include <string>
#include <memory>
#include <stdexcept>

class json {
public:
    json(const std::string& file_path);
    
    json_value& get_json();
    const json_value& get_json() const;
    
    std::string get_context(int indent = -1) const;
    
    void write_file(const std::string& file_path, int indent = 2) const;

private:
    std::unique_ptr<json_value> json_data_;
};

#endif // JSON_API_HPP