#include "../include/json.hpp"
#include "../include/parser/parser.hpp"
#include "../include/types/json_array.hpp"
#include "../include/types/json_object.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

json::json() : json_data_(nullptr) {}

json::json(const json& other) : json_data_(other.json_data_) {}

json::json(json&& other) noexcept : json_data_(std::move(other.json_data_)) {}

json& json::operator=(const json& other) {
    if (this != &other) {
        json_data_ = other.json_data_;
    }

    return *this;
}

json& json::operator=(json&& other) noexcept {
    if (this != &other) {
        json_data_ = std::move(other.json_data_);
    }
    
    return *this;
}

json json::parse(const std::string& json_string) {
    json result;
    parser p(json_string);
    result.json_data_ = p.parse();
    
    return result;
}

json json::object() {
    json result;
    result.json_data_ = json_value::make_object();
    
    return result;
}

json json::array() {
    json result;
    result.json_data_ = json_value::make_array();
    
    return result;
}

json::json(const std::string& file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + file_path);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    file.close();

    try {
        parser p(content);
        json_data_ = p.parse();
    } catch (const std::exception& e) {
        throw std::runtime_error("Failed to parse JSON file: " + std::string(e.what()));
    }
}

json_value& json::get_json() {
    return json_data_;
}

const json_value& json::get_json() const {
    return json_data_;
}

std::string json::get_context(int indent) const {
    return json_data_.dump(indent);
}

void json::write_file(const std::string& file_path, int indent) const {
    std::ofstream file(file_path);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for writing: " + file_path);
    }

    file << json_data_.dump(indent);
    file.close();
}
