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

    int int_value = 0;

    std::string var_name;

    char op = 0;
    std::unique_ptr<Ast> left;
    std::unique_ptr<Ast> right;

    std::vector<std::unique_ptr<Ast>> stmts;

    Ast(AstKind k) : kind(k) {}
};

#endif
