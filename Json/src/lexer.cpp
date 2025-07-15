#include "../include/lexer.hpp"

lexer::lexer(const std::string& input) : input_(input), pos_(0) {}

lexer::token lexer::next_token() {
    skip_whitespace();
    if (pos_ >= input_.size()) return {token_type::end, ""};

    char c = consume();
    switch (c) {
        case '{': 
            return {token_type::l_brace, "{"};
        case '}': 
            return {token_type::r_brace, "}"};
        case '[': 
            return {token_type::l_bracket, "["};
        case ']': 
            return {token_type::r_bracket, "]"};
        case ':': 
            return {token_type::colon, ":"};
        case ',': 
            return {token_type::comma, ","};
        case '"': 
            return lex_string();
        case '-': case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            --pos_; return lex_number();
        default:
            if (std::isalpha(c)) {
                --pos_; 
                return lex_keyword();
            }
            
            throw std::runtime_error("Invalid character '" + std::string(1, c) + "' at position " + std::to_string(pos_));
    }
}

char lexer::peek() const {
    return pos_ < input_.size() ? input_[pos_] : '\0';
}

char lexer::consume() {
    return pos_ < input_.size() ? input_[pos_++] : '\0';
}

void lexer::skip_whitespace() {
    while (pos_ < input_.size() && std::isspace(input_[pos_])) {
        ++pos_;
    }
}

lexer::token lexer::lex_string() {
    std::string s;
    while (pos_ < input_.size() && input_[pos_] != '"') {
        char c = consume();
        if (c == '\\') {
            if (pos_ >= input_.size()) throw std::runtime_error("Incomplete escape sequence at position " + std::to_string(pos_));
            c = consume();
            switch (c) {
                case '"': 
                    s += '"'; 
                    break;
                case '\\': 
                    s += '\\'; 
                    break;
                case '/': 
                    s += '/'; 
                    break;
                case 'b': 
                    s += '\b'; 
                    break;
                case 'f': 
                    s += '\f';
                    break;
                case 'n': 
                    s += '\n';
                    break;
                case 'r': 
                    s += '\r'; 
                    break;
                case 't': 
                    s += '\t'; 
                    break;
                default: 
                    throw std::runtime_error("Invalid escape sequence '\\" + std::string(1, c) + "' at position " + std::to_string(pos_ - 1));
            }
        } 
        else {
            s += c;
        }
    }
    
    if (pos_ >= input_.size() || input_[pos_] != '"') {
        throw std::runtime_error("Unterminated string at position " + std::to_string(pos_));
    }
    
    consume(); // Consume closing quote
    return {token_type::string, s};
}

lexer::token lexer::lex_number() {
    std::string num_str;
    if (peek() == '-'){ 
        num_str += consume();
    }
    
    while (pos_ < input_.size() && std::isdigit(input_[pos_])) {
        num_str += consume();
    }
    
    if (pos_ < input_.size() && input_[pos_] == '.') {
        num_str += consume();
        while (pos_ < input_.size() && std::isdigit(input_[pos_])) {
            num_str += consume();
        }
    }
    
    if (pos_ < input_.size() && (input_[pos_] == 'e' || input_[pos_] == 'E')) {
        num_str += consume();
        if (pos_ < input_.size() && (input_[pos_] == '+' || input_[pos_] == '-')) {
            num_str += consume();
        }
    
        while (pos_ < input_.size() && std::isdigit(input_[pos_])) {
            num_str += consume();
        }
    }
    
    return {token_type::number, num_str};
}

lexer::token lexer::lex_keyword() {
    std::string keyword;
    while (pos_ < input_.size() && std::isalpha(input_[pos_])) {
        keyword += consume();
    }
    
    if (keyword == "true"){ 
        return {token_type::true_val, keyword};
    }
    
    if (keyword == "false"){ 
        return {token_type::false_val, keyword};
    }
    
    if (keyword == "null"){
        return {token_type::null, keyword};
    }
    
    throw std::runtime_error("Invalid keyword: " + keyword + " at position " + std::to_string(pos_ - keyword.size()));
}

// lexer::lexer(const std::string& input) : input_(input), pos_(0) {}

// lexer::token lexer::next_token() {
//     skip_whitespace();
//     if (pos_ >= input_.size()) return {token_type::end, ""};

//     char c = consume();
//     switch (c) {
//         case '{': 
//             return {token_type::l_brace, "{"};
//         case '}': 
//             return {token_type::r_brace, "}"};
//         case '[': 
//             return {token_type::l_bracket, "["};
//         case ']': 
//             return {token_type::r_bracket, "]"};
//         case ':': 
//             return {token_type::colon, ":"};
//         case ',': 
//             return {token_type::comma, ","};
//         case '"': 
//             return lex_string();
//         case '-': case '0': case '1': case '2': case '3': case '4':
//         case '5': case '6': case '7': case '8': case '9':
//             --pos_; return lex_number();
//         default:
//             if (std::isalpha(c)) {
//                 --pos_; return lex_keyword();
//             }

//             throw std::runtime_error("Invalid character at position " + std::to_string(pos_));
//     }
// }

// char lexer::peek() const {
//     return pos_ < input_.size() ? input_[pos_] : '\0';
// }

// char lexer::consume() {
//     return pos_ < input_.size() ? input_[pos_++] : '\0';
// }

// void lexer::skip_whitespace() {
//     while (pos_ < input_.size() && std::isspace(input_[pos_])) {
//         ++pos_;
//     }
// }

// lexer::token lexer::lex_string() {
//     std::string s;
//     while (pos_ < input_.size() && input_[pos_] != '"') {
//         char c = consume();
//         if (c == '\\') {
//             if (pos_ >= input_.size()) throw std::runtime_error("Incomplete escape sequence");
//             c = consume();
//             switch (c) {
//                 case '"': s += '"'; break;
//                 case '\\': s += '\\'; break;
//                 case '/': s += '/'; break;
//                 case 'b': s += '\b'; break;
//                 case 'f': s += '\f'; break;
//                 case 'n': s += '\n'; break;
//                 case 'r': s += '\r'; break;
//                 case 't': s += '\t'; break;
//                 default: throw std::runtime_error("Invalid escape sequence");
//             }
//         }
//         else {
//             s += c;
//         }
//     }
    
//     if (pos_ >= input_.size() || input_[pos_] != '"') {
//         throw std::runtime_error("Unterminated string");
//     }
    
//     consume(); 
//     return {token_type::string, s};
// }

// lexer::token lexer::lex_number() {
//     std::string num_str;
//     if (peek() == '-'){ 
//         num_str += consume();
//     }
    
//     while (pos_ < input_.size() && std::isdigit(input_[pos_])) {
//         num_str += consume();
//     }
    
//     if (pos_ < input_.size() && input_[pos_] == '.') {
//         num_str += consume();
//         while (pos_ < input_.size() && std::isdigit(input_[pos_])) {
//             num_str += consume();
//         }
//     }
    
//     if (pos_ < input_.size() && (input_[pos_] == 'e' || input_[pos_] == 'E')) {
//         num_str += consume();
//         if (pos_ < input_.size() && (input_[pos_] == '+' || input_[pos_] == '-')) {
//             num_str += consume();
//         }
    
//         while (pos_ < input_.size() && std::isdigit(input_[pos_])) {
//             num_str += consume();
//         }
//     }
    
//     return {token_type::number, num_str};
// }

// lexer::token lexer::lex_keyword() {
//     std::string keyword;
//     while (pos_ < input_.size() && std::isalpha(input_[pos_])) {
//         keyword += consume();
//     }
    
//     if (keyword == "true"){ 
//         return {token_type::true_val, keyword};
//     }
    
//     if (keyword == "false"){ 
//         return {token_type::false_val, keyword};
//     }
    
//     if (keyword == "null"){ 
//         return {token_type::null, keyword};
//     }
    
//     throw std::runtime_error("Invalid keyword: " + keyword);
// }