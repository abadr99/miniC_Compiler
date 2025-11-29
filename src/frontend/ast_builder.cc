#include <vector>
#include <string>

#include "antlr4-runtime.h"
#include "antlr4-runtime.h"
#include ".antlr/MiniCLexer.h"
#include ".antlr/MiniCParser.h"

#include "frontend/ast_builder.h"

using namespace antlr4;
using namespace minic::frontend;

ASTBuilder::ASTBuilder() {}

AST ASTBuilder::BuildAST(MiniCParser::ProgramContext* parse_tree) {
    AST ast;
    ast.AddRoot(new ASTNode("Program"));
    // Traverse the parse tree and build the AST
    
    return ast;
}

