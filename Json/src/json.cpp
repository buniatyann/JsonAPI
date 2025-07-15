#include "../include/json.hpp"
// #include "../include/parser.hpp"
// #include "../include/json_number.hpp"
// #include "../include/json_string.hpp"
// #include "../include/json_boolean.hpp"

#include <fstream>
#include <sstream>

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
    if (!json_data_) {
        throw std::runtime_error("No JSON data loaded");
    }
    return *json_data_;
}

const json_value& json::get_json() const {
    if (!json_data_) {
        throw std::runtime_error("No JSON data loaded");
    }
    return *json_data_;
}

std::string json::get_context(int indent) const {
    if (!json_data_) {
        throw std::runtime_error("No JSON data loaded");
    }
    return json_data_->dump(indent);
}

void json::write_file(const std::string& file_path, int indent) const {
    if (!json_data_) {
        throw std::runtime_error("No JSON data loaded");
    }

    std::ofstream file(file_path);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for writing: " + file_path);
    }

    file << json_data_->dump(indent);
    file.close();
}