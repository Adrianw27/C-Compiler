// Abstract syntax type definition
#ifndef AST_HPP
#define AST_HPP

#include <memory>
#include <string>
#include <vector>

enum class AstKind {
    IntLiteral,
    Var,
    BinOp,
    Assign,
    ReturnStmt,
    Seq
};

struct Ast {
    AstKind kind;

    // IntLiteral
    int int_value = 0;

    // Var / Assign
    std::string var_name;

    // BinOp
    char op = 0;
    std::unique_ptr<Ast> left;
    std::unique_ptr<Ast> right;

    // Sequence of statements
    std::vector<std::unique_ptr<Ast>> stmts;

    Ast(AstKind k) : kind(k) {}
};

#endif