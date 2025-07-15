#include "../include/parser.hpp"

parser::parser(const std::string& input) : lexer_(input) {
    next_token();
}

std::unique_ptr<json_value> parser::parse() {
    auto result = parse_value();
    if (current_token_.type != lexer::token_type::end) {
        throw std::runtime_error("Unexpected token after JSON value");
    }
    return result;
}

void parser::next_token() {
    current_token_ = lexer_.next_token();
}

std::unique_ptr<json_value> parser::parse_value() {
    switch (current_token_.type) {
        case lexer::token_type::l_brace: 
            return parse_object();
        case lexer::token_type::l_bracket: 
            return parse_array();
        case lexer::token_type::string: 
            return parse_string();
        case lexer::token_type::number: 
            return parse_number();
        case lexer::token_type::true_val:
        case lexer::token_type::false_val: 
            return parse_boolean();
        case lexer::token_type::null: 
            return parse_null();
        default: 
            throw std::runtime_error("Invalid JSON value");
    }
}

std::unique_ptr<json_value> parser::parse_object() {
    if (current_token_.type != lexer::token_type::l_brace) {
        throw std::runtime_error("Expected '{'");
    }

    next_token();
    json_object::object obj;
    if (current_token_.type != lexer::token_type::r_brace) {
        while (true) {
            if (current_token_.type != lexer::token_type::string) {
                throw std::runtime_error("Expected string key");
            }
            std::string key = current_token_.value;
            next_token();
            if (current_token_.type != lexer::token_type::colon) {
                throw std::runtime_error("Expected ':'");
            }
            
            next_token();
            auto value = parse_value();
            switch (value->type()) {
                case json_type::null:
                    obj[key] = dynamic_cast<json_null&>(*value);
                    break;
                case json_type::boolean:
                    obj[key] = dynamic_cast<json_boolean&>(*value);
                    break;
                case json_type::number:
                    obj[key] = dynamic_cast<json_number&>(*value);
                    break;
                case json_type::string:
                    obj[key] = dynamic_cast<json_string&>(*value);
                    break;
                case json_type::array:
                    obj[key] = dynamic_cast<json_array&>(*value);
                    break;
                case json_type::object:
                    obj[key] = dynamic_cast<json_object&>(*value);
                    break;
            }
            if (current_token_.type == lexer::token_type::r_brace) {
                break;
            }
            
            if (current_token_.type != lexer::token_type::comma) {
                throw std::runtime_error("Expected ',' or '}'");
            }
            
            next_token();
        }
    }
    
    if (current_token_.type != lexer::token_type::r_brace) {
        throw std::runtime_error("Expected '}'");
    }
    
    next_token();
    return std::make_unique<json_object>(obj);
}

std::unique_ptr<json_value> parser::parse_array() {
    if (current_token_.type != lexer::token_type::l_bracket) {
        throw std::runtime_error("Expected '['");
    }
    
    next_token();
    auto arr = std::make_unique<json_array>();
    if (current_token_.type != lexer::token_type::r_bracket) {
        while (true) {
            arr->add_value(parse_value());
            if (current_token_.type == lexer::token_type::r_bracket) {
                break;
            }
            
            if (current_token_.type != lexer::token_type::comma) {
                throw std::runtime_error("Expected ',' or ']'");
            }
            
            next_token();
        }
    }
    
    if (current_token_.type != lexer::token_type::r_bracket) {
        throw std::runtime_error("Expected ']'");
    }
    
    next_token();
    return arr;
}

std::unique_ptr<json_value> parser::parse_string() {
    if (current_token_.type != lexer::token_type::string) {
        throw std::runtime_error("Expected string");
    }
    
    auto result = std::make_unique<json_string>(current_token_.value);
    next_token();
    
    return result;
}

std::unique_ptr<json_value> parser::parse_number() {
    if (current_token_.type != lexer::token_type::number) {
        throw std::runtime_error("Expected number");
    }
    try {
        auto result = std::make_unique<json_number>(std::stod(current_token_.value));
        next_token();
        return result;
    } catch (...) {
        throw std::runtime_error("Invalid number format: " + current_token_.value);
    }
}

std::unique_ptr<json_value> parser::parse_boolean() {
    if (current_token_.type == lexer::token_type::true_val) {
        next_token();
        return std::make_unique<json_boolean>(true);
    }
    
    if (current_token_.type == lexer::token_type::false_val) {
        next_token();
        return std::make_unique<json_boolean>(false);
    }
    
    throw std::runtime_error("Expected boolean");
}

std::unique_ptr<json_value> parser::parse_null() {
    if (current_token_.type != lexer::token_type::null) {
        throw std::runtime_error("Expected null");
    }
    
    next_token();
    return std::make_unique<json_null>();
}