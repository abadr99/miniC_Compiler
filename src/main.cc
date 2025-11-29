#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "utils/compiler_options.h"
#include "frontend/ast_builder.h"

#include "antlr4-runtime.h"
#include "antlr4-runtime.h"
#include ".antlr/MiniCLexer.h"
#include ".antlr/MiniCParser.h"

int main (int argc, char** argv) {
    minic::utils::CompilerOptions options;
    options.ParseCommandLine(argc, argv);

    std::ifstream inputFile(options.GetInputFile());
    if (!inputFile.is_open()) {
        std::cerr << "Cannot open file\n";
        return 1;
    }

    antlr4::ANTLRInputStream input(inputFile);
    MiniCLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    MiniCParser parser(&tokens);

    MiniCParser::ProgramContext* tree = parser.program();

    std::cout << "Parse tree:\n" << tree->toStringTree(&parser) << std::endl;
    
    // ----- FRONTEND STAGE -----
    // 1] Build AST
    minic::frontend::ASTBuilder ast_builder;
    minic::frontend::AST ast = ast_builder.BuildAST(tree);

    return 0;
}