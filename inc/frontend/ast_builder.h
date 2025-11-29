#ifndef INC_FRONTEND_AST_BUILDER_H
#define INC_FRONTEND_AST_BUILDER_H

#include "antlr4-runtime.h"
#include ".antlr/MiniCLexer.h"
#include ".antlr/MiniCParser.h"
#include <vector>
#include <string>

namespace minic {
namespace frontend {

class ASTNode {
 public:
  ASTNode(const std::string& value);
  void AddChild(ASTNode* child);
  const std::string& GetValue() const;
  const std::vector<ASTNode*>& GetChildren() const;
 private:
  std::string value_;
  std::vector<ASTNode*> children_;
};

class ExpressionNode : public ASTNode {
 public:
  ExpressionNode(const std::string& value);
};

class StatementNode : public ASTNode {
 public:
  StatementNode(const std::string& value);
};

class FunctionNode : public ASTNode {
 public:
  FunctionNode(const std::string& name);
  void AddParameter(const std::string& param);
  const std::vector<std::string>& GetParameters() const;
 private:
  std::vector<std::string> parameters_;
};

class VariableNode : public ASTNode {
 public:
  VariableNode(const std::string& name, const std::string& type);
  const std::string& GetType() const;
 private:
  std::string type_;
};

class LiteralNode : public ASTNode {
 public:
  LiteralNode(const std::string& value);
};

class BinaryOpNode : public ASTNode {
 public:
  BinaryOpNode(const std::string& op);
  void SetLeft(ASTNode* left);
  void SetRight(ASTNode* right);
  ASTNode* GetLeft() const;
  ASTNode* GetRight() const;
 private:
  ASTNode* left_;
  ASTNode* right_;
};

class UnaryOpNode : public ASTNode {
 public:
  UnaryOpNode(const std::string& op);
  void SetOperand(ASTNode* operand);
  ASTNode* GetOperand() const;
 private:
  ASTNode* operand_;
};

class IfNode : public ASTNode {
 public:
  IfNode();
  void SetCondition(ASTNode* condition);
  void SetThenBranch(ASTNode* then_branch);
  void SetElseBranch(ASTNode* else_branch);
  ASTNode* GetCondition() const;
  ASTNode* GetThenBranch() const;
  ASTNode* GetElseBranch() const;
 private:
  ASTNode* condition_;
  ASTNode* then_branch_;
  ASTNode* else_branch_;
};

class WhileNode : public ASTNode {
 public:
  WhileNode();
  void SetCondition(ASTNode* condition);
  void SetBody(ASTNode* body);
  ASTNode* GetCondition() const;
  ASTNode* GetBody() const;
 private:
  ASTNode* condition_;
  ASTNode* body_;
};

class ReturnNode : public ASTNode {
 public:
  ReturnNode();
  void SetReturnValue(ASTNode* return_value);
  ASTNode* GetReturnValue() const;
 private:
  ASTNode* return_value_;
};

class AST {
 public:
  AST();
  void SetRoot(ASTNode* root);
  ASTNode* GetRoot() const;
 private:
  ASTNode* root_;
};

class ASTBuilder {
 public:
  ASTBuilder();
  AST BuildAST(MiniCParser::ProgramContext* parse_tree);
  void PrintAST() const;
 private:
};

}  // namespace frontend
}  // namespace minic
#endif  // INC_FRONTEND_AST_BUILDER_H