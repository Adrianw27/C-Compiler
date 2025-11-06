// Source code reader
#include "Lexer.hpp"
#include <cctype>
#include <iostream>

Lexer::Lexer(std::string src)
  : src_(std::move(src)),
    pos_(0)
{
}

void Lexer::skipWhitespace() {
    while (pos_ < src_.size() && std::isspace(src_[pos_])) {
        pos_++;
    }
}

char Lexer::peekChar() const {
    if (pos_ < src_.size()) return src_[pos_];
    return '\0';
}

char Lexer::getChar() {
    if (pos_ < src_.size()) return src_[pos_++];
    return '\0';
}

Token Lexer::readNumber() {
    int val = 0;
    while (std::isdigit(peekChar())) {
        val = val * 10 + (getChar() - '0');
    }
    return Token(TokenKind::INT_LITERAL, "", val);
}

Token Lexer::readIdentOrKeyword() {
    size_t start = pos_;
    while (std::isalnum(peekChar())) {
        getChar();
    }
    std::string ident = src_.substr(start, pos_ - start);
    if (ident == "int") {
        return Token(TokenKind::INT, ident, 0);
    } else if (ident == "return") {
        return Token(TokenKind::RETURN, ident, 0);
    } else if (ident == "main") {
        return Token(TokenKind::MAIN, ident, 0);
    } else {
        return Token(TokenKind::IDENT, ident, 0);
    }
}

Token Lexer::nextToken() {
    skipWhitespace();
    char c = peekChar();
    if (c == '\0') {
        return Token(TokenKind::EOF_TOKEN, "", 0);
    }
    if (std::isdigit(c)) {
        return readNumber();
    }
    if (std::isalpha(c)) {
        return readIdentOrKeyword();
    }
    switch (c) {
        case '{': getChar(); return Token(TokenKind::LBRACE, "{", 0);
        case '}': getChar(); return Token(TokenKind::RBRACE, "}", 0);
        case '(': getChar(); return Token(TokenKind::LPAREN, "(", 0);
        case ')': getChar(); return Token(TokenKind::RPAREN, ")", 0);
        case ';': getChar(); return Token(TokenKind::SEMI, ";", 0);
        case '+': getChar(); return Token(TokenKind::PLUS, "+", 0);
        case '-': getChar(); return Token(TokenKind::MINUS, "-", 0);
        case '=': getChar(); return Token(TokenKind::ASSIGN, "=", 0);
        default:
            std::cerr << "Unexpected character: " << c << "\n";
            std::exit(1);
    }
}
