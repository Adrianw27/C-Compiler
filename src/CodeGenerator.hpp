// Takes ast and produces machine code - def
#ifndef CODEGENERATOR_HPP
#define CODEGENERATOR_HPP

#include "AST.hpp"
#include <iostream>

class CodeGenerator {
public:
    explicit CodeGenerator(Ast* root);
    void generate();

private:
    Ast* root_;
    void genStmt(Ast* node);
    void genExpr(Ast* node);
};

#endif // CODEGEN_HPP
