// main.cpp
#include "Lexer.hpp"
#include "Parser.hpp"
#include "CodeGenerator.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <source-file>\n";
        return EXIT_FAILURE;
    }
    std::ifstream in(argv[1]);
    if (!in) {
        std::cerr << "Error: Could not open file: " << argv[1] << "\n";
        return EXIT_FAILURE;
    }
    std::stringstream buffer;
    buffer << in.rdbuf();
    std::string src = buffer.str();

    Lexer lexer(src);
    Parser parser(lexer);
    std::unique_ptr<Ast> ast;
    try {
        ast = parser.parseProgram();
    } catch (const std::exception &ex) {
        std::cerr << "Parsing failed: " << ex.what() << "\n";
        return EXIT_FAILURE;
    }

    CodeGenerator codegen(ast.get());
    codegen.generate();

    return EXIT_SUCCESS;
}