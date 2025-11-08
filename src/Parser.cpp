// Takes token stream from lexer and builds ast - implementation
#include "Parser.hpp"
#include <iostream>
#include <cstdlib>

Parser::Parser(Lexer &lexer)
  : lexer_(lexer)
{
    advance();
}

void Parser::advance() {
    curTok_ = lexer_.nextToken();
}

bool Parser::expect(TokenKind kind, const char* errMsg) {
    if (curTok_.kind != kind) {
        std::cerr << "Parse error: " << errMsg
                  << " at token '" << curTok_.lexeme
                  << "'\n";
        std::exit(1);
    }
    return true;
}

std::unique_ptr<Ast> Parser::parsePrimary() {
    if (curTok_.kind == TokenKind::INT_LITERAL) {
        int val = curTok_.int_value;
        advance();
        auto node = std::make_unique<Ast>(AstKind::IntLiteral);
        node->int_value = val;
        return node;
    }
    if (curTok_.kind == TokenKind::IDENT) {
        std::string name = curTok_.lexeme;
        advance();
        auto node = std::make_unique<Ast>(AstKind::Var);
        node->var_name = name;
        return node;
    }
    if (curTok_.kind == TokenKind::LPAREN) {
        advance();
        auto expr = parseExpression();
        expect(TokenKind::RPAREN, "Expected ')'");
        advance();
        return expr;
    }
    std::cerr << "Unexpected token in primary: '"
              << curTok_.lexeme << "'\n";
    std::exit(1);
}

std::unique_ptr<Ast> Parser::parseExpression() {
    auto lhs = parsePrimary();
    while (curTok_.kind == TokenKind::PLUS ||
           curTok_.kind == TokenKind::MINUS) {
        char op = (curTok_.kind == TokenKind::PLUS ? '+' : '-');
        advance();
        auto rhs = parsePrimary();
        auto node = std::make_unique<Ast>(AstKind::BinOp);
        node->op = op;
        node->left = std::move(lhs);
        node->right = std::move(rhs);
        lhs = std::move(node);
    }
    return lhs;
}

std::unique_ptr<Ast> Parser::parseAssignment() {
    expect(TokenKind::IDENT, "Expected variable name in assignment");
    std::string name = curTok_.lexeme;
    advance();
    expect(TokenKind::ASSIGN, "Expected '=' after variable");
    advance();
    auto expr = parseExpression();
    expect(TokenKind::SEMI, "Expected ';' after assignment");
    advance();
    auto node = std::make_unique<Ast>(AstKind::Assign);
    node->var_name = name;
    node->left = std::move(expr);
    return node;
}

std::unique_ptr<Ast> Parser::parseStatement() {
    if (curTok_.kind == TokenKind::IDENT) {
        return parseAssignment();
    }
    if (curTok_.kind == TokenKind::RETURN) {
        advance();
        auto expr = parseExpression();
        expect(TokenKind::SEMI, "Expected ';' after return");
        advance();
        auto node = std::make_unique<Ast>(AstKind::ReturnStmt);
        node->left = std::move(expr);
        return node;
    }
    std::cerr << "Unexpected statement token: '"
              << curTok_.lexeme << "'\n";
    std::exit(1);
}

std::unique_ptr<Ast> Parser::parseProgram() {
    expect(TokenKind::INT, "Expected 'int' at program start");
    advance();
    expect(TokenKind::MAIN, "Expected 'main'");
    advance();
    expect(TokenKind::LPAREN, "Expected '(' after main");
    advance();
    expect(TokenKind::RPAREN, "Expected ')'");
    advance();
    expect(TokenKind::LBRACE, "Expected '{'");
    advance();

    auto seqNode = std::make_unique<Ast>(AstKind::Seq);
    while (curTok_.kind != TokenKind::RBRACE) {
        seqNode->stmts.push_back(parseStatement());
    }
    advance();
    expect(TokenKind::EOF_TOKEN, "Expected end of file");
    return seqNode;
}