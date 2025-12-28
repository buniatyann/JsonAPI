#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <stdexcept>
#include <cctype>

class lexer {
public:
    enum class token_type {
        l_brace, r_brace, l_bracket, r_bracket, colon, comma,
        string, number, true_val, false_val, null, end
    };

    struct token {
        token_type type;
        std::string value;
    };

    lexer(const std::string& input);
    token next_token();

private:
    const std::string& input_;
    size_t pos_;
    
    char peek() const;
    char consume();
    void skip_whitespace();
    token lex_string();
    token lex_number();
    token lex_keyword();
};
#endif // LEXER_HPP