#include "../../include/parser/parser.hpp"
#include "../../include/types/json_null.hpp"
#include "../../include/types/json_boolean.hpp"
#include "../../include/types/json_number.hpp"
#include "../../include/types/json_string.hpp"
#include "../../include/types/json_array.hpp"
#include "../../include/types/json_object.hpp"
#include <stdexcept>

parser::parser(const std::string& input) : lexer_(input) {
    next_token();
}

json_value parser::parse() {
    auto result = parse_value();
    if (current_token_.type != lexer::token_type::end) {
        throw std::runtime_error("Unexpected token after JSON value");
    }
    
    return result;
}

void parser::next_token() {
    current_token_ = lexer_.next_token();
}

json_value parser::parse_value() {
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

json_value parser::parse_object() {
    if (current_token_.type != lexer::token_type::l_brace) {
        throw std::runtime_error("Expected '{'");
    }

    next_token();
    json_value result = json_value::make_object();
    json_object& obj = result.as_object();
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
            obj[key] = parse_value();
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
    return result;
}

json_value parser::parse_array() {
    if (current_token_.type != lexer::token_type::l_bracket) {
        throw std::runtime_error("Expected '['");
    }

    next_token();
    json_value result = json_value::make_array();
    json_array& arr = result.as_array();
    if (current_token_.type != lexer::token_type::r_bracket) {
        while (true) {
            arr.add_value(parse_value());
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
    return result;
}

json_value parser::parse_string() {
    if (current_token_.type != lexer::token_type::string) {
        throw std::runtime_error("Expected string");
    }

    json_value result(current_token_.value);
    next_token();

    return result;
}

json_value parser::parse_number() {
    if (current_token_.type != lexer::token_type::number) {
        throw std::runtime_error("Expected number");
    }
    try {
        json_value result(std::stod(current_token_.value));
        next_token();
        return result;
    } catch (...) {
        throw std::runtime_error("Invalid number format: " + current_token_.value);
    }
}

json_value parser::parse_boolean() {
    if (current_token_.type == lexer::token_type::true_val) {
        next_token();
        return json_value(true);
    }

    if (current_token_.type == lexer::token_type::false_val) {
        next_token();
        return json_value(false);
    }

    throw std::runtime_error("Expected boolean");
}

json_value parser::parse_null() {
    if (current_token_.type != lexer::token_type::null) {
        throw std::runtime_error("Expected null");
    }

    next_token();
    return json_value(nullptr);
}
