#ifndef PARSER_HPP
#define PARSER_HPP

#include "lexer.hpp"
#include "../types/json_value.hpp"

class parser {
public:
    parser(const std::string& input);
    json_value parse();

private:
    lexer lexer_;
    lexer::token current_token_;

    void next_token();
    json_value parse_value();
    json_value parse_object();
    json_value parse_array();
    json_value parse_string();
    json_value parse_number();
    json_value parse_boolean();
    json_value parse_null();
};

#endif // PARSER_HPP
