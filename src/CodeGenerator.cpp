// // Takes ast and produces machine code - imp
#include "CodeGenerator.hpp"

CodeGenerator::CodeGenerator(Ast* root)
  : root_(root)
{}

void CodeGenerator::comment(const std::string &s) {
    std::cout << "    # " << s << "\n";
}

void CodeGenerator::generate() {
    std::cout << "    .globl main\n";
    std::cout << "main:\n";
    std::cout << "    push rbp\n";
    std::cout << "    mov rbp, rsp\n";
    std::cout << "    sub rsp, 32\n";  // allocate for variables

    comment("initialize variables");
    std::cout << "    mov DWORD PTR [rbp-4], 0    # var x\n";

    // statements
    if (root_->kind == AstKind::Seq) {
        for (auto &stmt : root_->stmts) {
            generateStmt(stmt.get());
        }
    }

    comment("return default 0");
    std::cout << "    mov eax, 0\n";
    std::cout << "    leave\n";
    std::cout << "    ret\n";
}

void CodeGenerator::generateStmt(Ast* stmt) {
    switch (stmt->kind) {
    case AstKind::Assign:
        comment("assignment statement");
        generateExpr(stmt->left.get());
        std::cout << "    mov DWORD PTR [rbp-4], eax\n";
        break;
    case AstKind::ReturnStmt:
        comment("return statement");
        generateExpr(stmt->left.get());
        std::cout << "    leave\n";
        std::cout << "    ret\n";
        break;
    default:
        std::cerr << "CodeGenerator error: unsupported stmt kind\n";
        std::exit(1);
    }
}

void CodeGenerator::generateExpr(Ast* expr) {
    switch (expr->kind) {
    case AstKind::IntLiteral:
        std::cout << "    mov eax, " << expr->int_value << "\n";
        break;
    case AstKind::Var:
        std::cout << "    mov eax, DWORD PTR [rbp-4]\n";
        break;
    case AstKind::BinOp:
        comment("binary op " + std::string(1, expr->op));
        generateExpr(expr->left.get());
        std::cout << "    push rax\n";
        generateExpr(expr->right.get());
        std::cout << "    pop rcx\n";
        if (expr->op == '+') {
            std::cout << "    add eax, ecx\n";
        } else {
            std::cout << "    sub ecx, eax\n";
            std::cout << "    mov eax, ecx\n";
        }
        break;
    default:
        std::cerr << "CodeGenerator error: unsupported expr kind\n";
        std::exit(1);
    }
}