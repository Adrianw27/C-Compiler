// TokenKind enumeration definition

#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

enum class TokenKind {
    EOF_TOKEN,
    INT_LITERAL,
    IDENT,
    RETURN,
    INT,
    MAIN,
    LBRACE,
    RBRACE,
    LPAREN,
    RPAREN,
    SEMI,
    PLUS,
    MINUS,
    ASSIGN
};

struct Token {
    TokenKind kind;
    std::string lexeme;
    int int_value;
    int line;
    int column; 

    Token(TokenKind k = TokenKind::EOF_TOKEN,
          std::string lex = "",
          int val = 0,
          int ln = 1,
          int col = 1)
      : kind(k),
        lexeme(std::move(lex)),
        int_value(val),
        line(ln),
        column(col)
    {}
};

#endif