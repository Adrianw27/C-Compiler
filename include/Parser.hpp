// Takes token stream from lexer and builds ast - definition

#ifndef PARSER_HPP
#define PARSER_HPP

#include "AST.hpp"
#include "Lexer.hpp"
#include <memory>

class Parser {
public:
    explicit Parser(Lexer &lexer);
    std::unique_ptr<Ast> parseProgram();

private:
    Lexer &lexer_;
    Token curTok_;

    void advance();
    bool expect(TokenKind kind, const char* errMsg);
    std::unique_ptr<Ast> parsePrimary();
    std::unique_ptr<Ast> parseExpression();
    std::unique_ptr<Ast> parseStatement();
    std::unique_ptr<Ast> parseAssignment();
};

#endif

