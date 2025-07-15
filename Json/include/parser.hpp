#ifndef PARSER_HPP
#define PARSER_HPP

#include "lexer.hpp"
#include "json_value.hpp"
#include "json.hpp"
#include "json_array.hpp"
#include "json_string.hpp"
#include "json_number.hpp"
#include "json_boolean.hpp"
#include "json_null.hpp"

class parser {
public:
    parser(const std::string& input);
    std::unique_ptr<json_value> parse();

private:
    lexer lexer_;
    lexer::token current_token_;
    
    void next_token();
    std::unique_ptr<json_value> parse_value();
    std::unique_ptr<json_value> parse_object();
    std::unique_ptr<json_value> parse_array();
    std::unique_ptr<json_value> parse_string();
    std::unique_ptr<json_value> parse_number();
    std::unique_ptr<json_value> parse_boolean();
    std::unique_ptr<json_value> parse_null();
};

#endif // PARSER_HPP