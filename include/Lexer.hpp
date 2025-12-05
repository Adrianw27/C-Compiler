// Source code reader - defintion
#ifndef LEXER_HPP
#define LEXER_HPP

#include "Token.hpp"
#include <string>

class Lexer {
public:
    explicit Lexer(std::string src);
    Token nextToken();
    Token peekToken();

private:
    std::string src_;
    size_t pos_ = 0;
    void skipWhitespace();
    char peekChar() const;
    char getChar();
    Token readNumber();
    Token readIdentOrKeyword();
};

#endif
