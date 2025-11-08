// // Takes ast and produces machine code - imp
#include "CodeGenerator.hpp"

CodeGenerator::CodeGenerator(Ast* root) : root_(root) {}

void CodeGenerator::generate() {
    std::cout << ".globl main\n";
    std::cout << "main:\n";
    std::cout << "    push rbp\n";
    std::cout << "    mov rbp, rsp\n";
    std::cout << "    sub rsp, 16\n";

    // Assume variable x at [rbp-4]
    std::cout << "    mov DWORD PTR [rbp-4], 0\n";

    if (root_->kind == AstKind::Seq) {
        for (auto &stmt : root_->stmts) {
            genStmt(stmt.get());
        }
    }

    std::cout << "    mov eax, 0\n";
    std::cout << "    leave\n";
    std::cout << "    ret\n";
}

void CodeGenerator::genStmt(Ast* node) {
    if (node->kind == AstKind::Assign) {
        genExpr(node->left.get());
        std::cout << "    mov DWORD PTR [rbp-4], eax\n";
    } else if (node->kind == AstKind::ReturnStmt) {
        genExpr(node->left.get());
        std::cout << "    leave\n";
        std::cout << "    ret\n";
    }
}

void CodeGenerator::genExpr(Ast* node) {
    if (node->kind == AstKind::IntLiteral) {
        std::cout << "    mov eax, " << node->int_value << "\n";
    } else if (node->kind == AstKind::VarX) {
        std::cout << "    mov eax, DWORD PTR [rbp-4]\n";
    } else if (node->kind == AstKind::BinOp) {
        genExpr(node->left.get());
        std::cout << "    push rax\n";
        genExpr(node->right.get());
        std::cout << "    pop rcx\n";
        if (node->op == '+') {
            std::cout << "    add eax, ecx\n";
        } else {
            std::cout << "    sub ecx, eax\n";
            std::cout << "    mov eax, ecx\n";
        }
    }
}
